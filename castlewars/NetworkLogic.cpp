#include "NetworkLogic.h"
#include "cocos2d.h"

static const ExitGames::Common::JString appId = L"c1b3bbcb-7f82-4d3b-b464-748d890e784a"; // set your app id here
static const ExitGames::Common::JString appVersion = L"1.0";

static const bool autoLobbbyStats = true;
static const bool useDefaultRegion = false;

static const ExitGames::Common::JString PLAYER_NAME =
#if defined _EG_MARMALADE_PLATFORM
#	if defined I3D_ARCH_X86
#		if defined _EG_MS_COMPILER
L"Marmalade X86 Windows";
#		else
L"Marmalade X86 OS X";
#		endif
#	elif defined I3D_ARCH_ARM
L"Marmalade ARM";
#	elif defined I3D_ARCH_MIPS
L"Marmalade MIPS";
#	else
L"unknown Marmalade platform";
#	endif
#elif defined _EG_WINDOWS_PLATFORM
L"Windows";
#elif defined _EG_IPHONE_PLATFORM
L"iOS";
#elif defined _EG_IMAC_PLATFORM
L"OS X";
#elif defined _EG_ANDROID_PLATFORM
L"Android";
#elif defined _EG_BLACKBERRY_PLATFORM
L"Blackberry";
#elif defined _EG_PS3_PLATFORM
L"PS3";
#elif defined _EG_LINUX_PLATFORM
L"Linux";
#else
L"unknown platform";
#endif

ExitGames::Common::JString& NetworkLogicListener::toString(ExitGames::Common::JString& retStr, bool /*withTypes*/) const
{
    return retStr;
}

State StateAccessor::getState(void) const
{
    return mState;
}

void StateAccessor::setState(State newState)
{
    mState = newState;
    for(unsigned int i=0; i<mStateUpdateListeners.getSize(); i++)
        mStateUpdateListeners[i]->stateUpdate(newState);
}

void StateAccessor::registerForStateUpdates(NetworkLogicListener* listener)
{
    mStateUpdateListeners.addElement(listener);
}

Input NetworkLogic::getLastInput(void) const
{
    return mLastInput;
}

void NetworkLogic::setLastInput(Input newInput)
{
    mLastInput = newInput;
}

State NetworkLogic::getState(void) const
{
    return mStateAccessor.getState();
}

// functions
NetworkLogic::NetworkLogic(const ExitGames::LoadBalancing::AuthenticationValues& authenticationValues)
#ifdef _EG_MS_COMPILER
#	pragma warning(push)
#	pragma warning(disable:4355)
#endif
: mLoadBalancingClient(*this, appId, appVersion, PLAYER_NAME+GETTIMEMS(), false, authenticationValues, autoLobbbyStats, useDefaultRegion)
, mLastInput(INPUT_NON)
//, mpOutputListener(listener)
, mLastActorNr(0)
#ifdef _EG_MS_COMPILER
#	pragma warning(pop)
#endif
{
    mStateAccessor.setState(STATE_INITIALIZED);
    mLoadBalancingClient.setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS)); // that instance of LoadBalancingClient and its implementation details
    mLogger.setListener(*this);
    mLogger.setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS)); // this class
    ExitGames::Common::Base::setListener(this);
    ExitGames::Common::Base::setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS)); // all classes that inherit from Base
}

void NetworkLogic::registerForStateUpdates(NetworkLogicListener* listener)
{
    mStateAccessor.registerForStateUpdates(listener);
}

bool NetworkLogic::connect(void)
{
    CCLOG("connecting to Photon");
    //mpOutputListener->writeLine(ExitGames::Common::JString(L"connecting to Photon"));
    if (!mLoadBalancingClient.connect()) return false;
    mStateAccessor.setState(STATE_CONNECTING);
    return true;
}

void NetworkLogic::disconnect(void)
{
    mLoadBalancingClient.disconnect();
}

bool NetworkLogic::opCreateRoom(void)
{
    // if last digits are always nearly the same, this is because of the timer calling this function being triggered every x ms with x being a factor of 10
    ExitGames::Common::JString tmp;
    if (!mLoadBalancingClient.opCreateRoom(tmp=GETTIMEMS(), true, true, 2, ExitGames::Common::Hashtable(), ExitGames::Common::JVector<ExitGames::Common::JString>(), ExitGames::Common::JString(), 1, INT_MAX/2, 10000)) return false;
    mStateAccessor.setState(STATE_JOINING);
    CCLOG("creating room ...");
    //mpOutputListener->writeLine(ExitGames::Common::JString(L"creating room ") + tmp + L"...");
    return true;
}

bool NetworkLogic::opJoinRandomRoom(void)
{
    return mLoadBalancingClient.opJoinRandomRoom();
}

void NetworkLogic::run(void)
{
    State state = mStateAccessor.getState();
    if(mLastInput == INPUT_EXIT && state != STATE_DISCONNECTING && state != STATE_DISCONNECTED)
    {
        disconnect();
        mStateAccessor.setState(STATE_DISCONNECTING);
        CCLOG("terminating application");
        //mpOutputListener->writeLine(L"terminating application");
    }
    else
    {
        switch(state)
        {
            case STATE_INITIALIZED:
                connect();
                mStateAccessor.setState(STATE_CONNECTING);
                CCLOG("connecting");
                //mpOutputListener->writeLine("connecting");
                break;
            case STATE_CONNECTING:
                break; // wait for callback
            case STATE_CONNECTED:
                
                switch(mLastInput)
            {
                case INPUT_1: // create Game
                    CCLOG("\n=========================");
                    //mpOutputListener->writeLine(L"\n=========================");
                    opCreateRoom();
                    break;
                case INPUT_2: // join Game
                    CCLOG("\n=========================");
                    //mpOutputListener->writeLine(L"\n=========================");
                    // remove false to enable rejoin
                    if(false && mLastJoinedRoom.length())
                    {
                        CCLOG("%s %ls %s %d %s", "rejoining ", mLastJoinedRoom.cstr(), " with actorNr = ", mLastActorNr , "...");
                        //mpOutputListener->writeLine(ExitGames::Common::JString(L"rejoining ") + mLastJoinedRoom + " with actorNr = " + mLastActorNr + "...");
                        mLoadBalancingClient.opJoinRoom(mLastJoinedRoom, true, mLastActorNr);
                    }
                    else
                    {
                        CCLOG("joining random room...");
                        //mpOutputListener->writeLine(ExitGames::Common::JString(L"joining random room..."));
                        opJoinRandomRoom();
                    }
                    mStateAccessor.setState(STATE_JOINING);
                    break;
                default: // no or illegal input -> stay waiting for legal input
                    break;
            }
                break;
            case STATE_JOINING:
                break; // wait for callback
            case STATE_JOINED:
                sendEvent();
                switch(mLastInput)
            {
                case INPUT_1: // leave Game
                    mLoadBalancingClient.opLeaveRoom();
                    CCLOG("");
                    CCLOG("leaving room");
                    //mpOutputListener->writeLine(L"");
                    //mpOutputListener->writeLine(L"leaving room");
                    mStateAccessor.setState(STATE_LEAVING);
                    break;
                case INPUT_2: // leave Game
                    mLoadBalancingClient.opLeaveRoom(true);
                    CCLOG("");
                    CCLOG("leaving room (will come back)");
                    //mpOutputListener->writeLine(L"");
                    //mpOutputListener->writeLine(L"leaving room (will come back)");
                    mStateAccessor.setState(STATE_LEAVING);
                    break;
                default: // no or illegal input -> stay waiting for legal input
                    break;
            }
                break;
            case STATE_LEAVING:
                break; // wait for callback
            case STATE_LEFT:
                mStateAccessor.setState(STATE_CONNECTED);
                break;
            case STATE_DISCONNECTING:
                break; // wait for callback
            default:
                break;
        }
    }
    mLastInput = INPUT_NON;
    mLoadBalancingClient.service();
}

void NetworkLogic::sendEvent(void)
{
    static int64 count = 0;
    mLoadBalancingClient.opRaiseEvent(false, ++count, 0);
    //mpOutputListener->write(ExitGames::Common::JString(L"s") + count + L" ");
}

// protocol implementations

void NetworkLogic::debugReturn(ExitGames::Common::DebugLevel::DebugLevel /*debugLevel*/, const ExitGames::Common::JString& string)
{
    //mpOutputListener->debugReturn(string);
}

void NetworkLogic::connectionErrorReturn(int errorCode)
{
    EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"code: %d", errorCode);
    CCLOG("%s %d", "received connection error ", errorCode);
    //mpOutputListener->writeLine(ExitGames::Common::JString(L"received connection error ") + errorCode);
    mStateAccessor.setState(STATE_DISCONNECTED);
}

void NetworkLogic::clientErrorReturn(int errorCode)
{
    EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"code: %d", errorCode);
    CCLOG("%s %d %s","received error ", errorCode , " from client");
    //mpOutputListener->writeLine(ExitGames::Common::JString(L"received error ") + errorCode + L" from client");
}

void NetworkLogic::warningReturn(int warningCode)
{
    EGLOG(ExitGames::Common::DebugLevel::WARNINGS, L"code: %d", warningCode);
    CCLOG("%s %d %s","received warning ", warningCode , " from client");
    //mpOutputListener->writeLine(ExitGames::Common::JString(L"received warning ") + warningCode + L" from client");
}

void NetworkLogic::serverErrorReturn(int errorCode)
{
    EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"code: %d", errorCode);
    CCLOG("%s %d %s","received error ", errorCode , " from server");
    //mpOutputListener->writeLine(ExitGames::Common::JString(L"received error ") + errorCode + " from server");
}

void NetworkLogic::joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& /*playernrs*/, const ExitGames::LoadBalancing::Player& player)
{
    EGLOG(ExitGames::Common::DebugLevel::INFO, L"%ls joined the game", player.getName().cstr());
    CCLOG("");
    //mpOutputListener->writeLine(L"");
    auto ttttt = player.getName();
    CCLOG("%s %d %s %ls %s","player ", playerNr, " ", ttttt.cstr() , " has joined the game");
    if (playerNr != this->playerNr) {
        CCLOG("New opponent !");
        this->lastEvent = EVENT_OPP_JOINED;
    }
}

void NetworkLogic::leaveRoomEventAction(int playerNr, bool isInactive)
{
    EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
    CCLOG("");
    CCLOG("%s %d %s", "player ", playerNr, " has left the game");
    this->lastEvent = EVENT_OPP_LEFT;
}

void NetworkLogic::disconnectEventAction(int playerNr)
{
    EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
    CCLOG("");
    CCLOG("%s %d %s", "player ", playerNr, " has disconnected");
    this->lastEvent = EVENT_OPP_LEFT;
}

void NetworkLogic::customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent)
{
    if (playerNr == this->playerNr) {
        CCLOG("Ignoring message from myself");
        return;
    }
    
    ExitGames::Common::Hashtable* event;
    
    switch (eventCode) {
        case 1: // Card played infos
            CCLOG("play infos received !");
            event = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable*>(eventContent).getDataCopy();
            
            this->pushResultToQueue(event);

            this->lastEvent = EVENT_NEW_MSG;
            
            break;
        case 2: // start second signal
            CCLOG("Received START_FIRST event");
            this->lastEvent = EVENT_START_FIRST;
            break;
        case 3: // start second signal
            CCLOG("Received START_SECOND event");
            this->lastEvent = EVENT_START_SECOND;
            break;
        default:
            break;
            
    }
}

void    NetworkLogic::pushResultToQueue(ExitGames::Common::Hashtable *content) {
    SRes::playResults   results;
    
    results.cardID = static_cast<SRes::ResID>(ExitGames::Common::ValueObject<int>(content->getValue(1)).getDataCopy());
    results.success = true;
    results.extraTurn = ExitGames::Common::ValueObject<bool>(content->getValue(2)).getDataCopy();
    results.pGemMod = ExitGames::Common::ValueObject<int>(content->getValue(3)).getDataCopy();
    results.pMagMod = ExitGames::Common::ValueObject<int>(content->getValue(4)).getDataCopy();
    results.pCastleMod = ExitGames::Common::ValueObject<int>(content->getValue(5)).getDataCopy();
    results.pWallMod = ExitGames::Common::ValueObject<int>(content->getValue(6)).getDataCopy();
    results.oppGemMod = ExitGames::Common::ValueObject<int>(content->getValue(7)).getDataCopy();
    results.oppMagMod = ExitGames::Common::ValueObject<int>(content->getValue(8)).getDataCopy();
    results.oppCastleMod = ExitGames::Common::ValueObject<int>(content->getValue(9)).getDataCopy();
    results.oppWallMod = ExitGames::Common::ValueObject<int>(content->getValue(10)).getDataCopy();
    
    CCLOG("Received : %d %d %d %d %d %d %d %d %d %d",
          results.cardID,
          results.extraTurn,
          results.pGemMod,
          results.pMagMod,
          results.pCastleMod,
          results.pWallMod,
          results.oppGemMod,
          results.oppMagMod,
          results.oppCastleMod,
          results.oppWallMod);
    
    this->eventQueue.push(results);
}

SRes::playResults   NetworkLogic::getResultFromQueue() {
    SRes::playResults r;
    
    CCLOG("Getting result from queue ...");
    r.success = false;
    if (!this->eventQueue.empty()) {
        r = this->eventQueue.front();
        this->eventQueue.pop();
    }
    this->lastEvent = EVENT_NOTHING;
    return r;
}

void NetworkLogic::connectReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
    EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
    if(errorCode)
    {
        EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
        mStateAccessor.setState(STATE_DISCONNECTING);
        return;
    }
    CCLOG("connected");
    //mpOutputListener->writeLine(L"connected");
    mStateAccessor.setState(STATE_CONNECTED);
}

void NetworkLogic::disconnectReturn(void)
{
    EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
    CCLOG("disconnected");
    //mpOutputListener->writeLine(L"disconnected");
    mStateAccessor.setState(STATE_DISCONNECTED);
}

void NetworkLogic::createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
    EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
    if(errorCode)
    {
        EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
        CCLOG("%s %ls", "opCreateRoom() failed: ", errorString.cstr());
        //mpOutputListener->writeLine(L"opCreateRoom() failed: " + errorString);
        mStateAccessor.setState(STATE_CONNECTED);
        return;
    }
    mLastJoinedRoom = mLoadBalancingClient.getCurrentlyJoinedRoom().getName();
    mLastActorNr = localPlayerNr;
    
    EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);
    auto tttt = mLoadBalancingClient.getCurrentlyJoinedRoom().getName();
    CCLOG("%s %ls %s" , "... room ", tttt.cstr(), " has been created");
    CCLOG("regularly sending dummy events now");
    //mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been created");
    //mpOutputListener->writeLine(L"regularly sending dummy events now");
    mStateAccessor.setState(STATE_JOINED);
    
    // ルーム内で割り当てられたプレイヤー番号を取得する
    CCLOG("player nr = %d", localPlayerNr);
    playerNr = localPlayerNr;
}

void NetworkLogic::joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
    EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
    if(errorCode)
    {
        mLastJoinedRoom = "";
        mLastActorNr = 0;
        EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
        CCLOG("%s %ls", "opJoinRoom() failed: ", errorString.cstr());
        //mpOutputListener->writeLine(L"opJoinRoom() failed: " + errorString);
        mStateAccessor.setState(STATE_CONNECTED);
        return;
    }
    EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);
    auto tttt = mLoadBalancingClient.getCurrentlyJoinedRoom().getName();
    CCLOG("%s %ls %s" , "... room ", tttt.cstr(), " has been successfully joined");
    CCLOG("regularly sending dummy events now");
    //mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been successfully joined");
    //mpOutputListener->writeLine(L"regularly sending dummy events now");
    mStateAccessor.setState(STATE_JOINED);
    
    // ルーム内で割り当てられたプレイヤー番号を取得する
    CCLOG("player nr = %d", localPlayerNr);
    playerNr = localPlayerNr;
}

void NetworkLogic::joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
    EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
    if(errorCode)
    {
        EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
        CCLOG("%s %ls", "opJoinRandomRoom() failed: ", errorString.cstr());
        //mpOutputListener->writeLine(L"opJoinRandomRoom() failed: " + errorString);
        mStateAccessor.setState(STATE_CONNECTED);
        return;
    }
    
    mLastJoinedRoom = mLoadBalancingClient.getCurrentlyJoinedRoom().getName();
    mLastActorNr = localPlayerNr;
    
    EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);
    auto tttt = mLoadBalancingClient.getCurrentlyJoinedRoom().getName();
    CCLOG("%s %ls %s" , "... room ", tttt.cstr(), " has been successfully joined");
    CCLOG("regularly sending dummy events now");
    //mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been successfully joined");
    //mpOutputListener->writeLine(L"regularly sending dummy events now");
    mStateAccessor.setState(STATE_JOINED);
    
    // ルーム内で割り当てられたプレイヤー番号を取得する
    CCLOG("player nr = %d", localPlayerNr);
    playerNr = localPlayerNr;
}

void NetworkLogic::leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
    EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
    if(errorCode)
    {
        EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
        CCLOG("%s %ls", "opLeaveRoom() failed: ", errorString.cstr());
        //mpOutputListener->writeLine(L"opLeaveRoom() failed: " + errorString);
        mStateAccessor.setState(STATE_DISCONNECTING);
        return;
    }
    mStateAccessor.setState(STATE_LEFT);
    CCLOG("room has been successfully left");
    //mpOutputListener->writeLine(L"room has been successfully left");
}

void NetworkLogic::joinLobbyReturn(void)
{
    EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
    CCLOG("joined lobby");
    //mpOutputListener->writeLine(L"joined lobby");
}

void NetworkLogic::leaveLobbyReturn(void)
{
    EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
    CCLOG("left lobby");
    //mpOutputListener->writeLine(L"left lobby");
}

/*
 void NetworkLogic::onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStats>& lobbyStats)
 {
 EGLOG(ExitGames::Common::DebugLevel::INFO, L"onLobbyStatsUpdate: %ls", lobbyStats.toString().cstr());
 auto tttt = lobbyStats.toString();
 CCLOG("%s %ls", "LobbyStats: ", tttt.cstr());
 //mpOutputListener->writeLine(L"LobbyStats: " + lobbyStats.toString());
 }
 
 void NetworkLogic::onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStats>& lobbyStats)
 {
 EGLOG(ExitGames::Common::DebugLevel::INFO, L"onLobbyStatsUpdate: %ls", lobbyStats.toString().cstr());
 CCLOG("%s %ls", "LobbyStats: ", lobbyStats.toString().cstr());
 //mpOutputListener->writeLine(L"LobbyStats: " + lobbyStats.toString());
 }
 */
void NetworkLogic::onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegions, const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegionServers)
{
    EGLOG(ExitGames::Common::DebugLevel::INFO, L"onAvailableRegions: %ls", availableRegions.toString().cstr(), availableRegionServers.toString().cstr());
    CCLOG("%s %ls %s %ls", "onAvailableRegions: ", availableRegions.toString().cstr(), "/", availableRegionServers.toString().cstr());
    //mpOutputListener->writeLine(L"onAvailableRegions: " + availableRegions.toString() + L" / " + availableRegionServers.toString());
    
    // select first region from list
    CCLOG("%s %ls ", "selecting region: ", availableRegions[0].cstr());
    //mpOutputListener->writeLine(L"selecting region: " + availableRegions[0]);
    mLoadBalancingClient.selectRegion(availableRegions[0]);
}


////////////////////
bool NetworkLogic::isRoomExists(void)
{
    if (mLoadBalancingClient.getRoomList().getIsEmpty()) {
        return false;
    }
    
    return true;
}

void    NetworkLogic::setLastEvent(Event e) {
    this->lastEvent = e;
}

void    NetworkLogic::sendStartSignal(bool first) {
    ExitGames::Common::Hashtable* eventContent = new ExitGames::Common::Hashtable();
    
    eventContent->put<int, bool>(1, first);
}

void NetworkLogic::sendPlayResult(SRes::playResults results) {
    
    ExitGames::Common::Hashtable* eventContent = new ExitGames::Common::Hashtable();

    eventContent->put<int, int>(1, results.cardID);
    eventContent->put<int, bool>(2, results.extraTurn);
    eventContent->put<int, int>(3, results.pGemMod);
    eventContent->put<int, int>(4, results.pMagMod);
    eventContent->put<int, int>(5, results.pCastleMod);
    eventContent->put<int, int>(6, results.pWallMod);
    eventContent->put<int, int>(7, results.oppGemMod);
    eventContent->put<int, int>(8, results.oppMagMod);
    eventContent->put<int, int>(9, results.oppCastleMod);
    eventContent->put<int, int>(10, results.oppWallMod);
    
    CCLOG("Sent : %d %d %d %d %d %d %d %d %d %d",
          results.cardID,
          results.extraTurn,
          results.pGemMod,
          results.pMagMod,
          results.pCastleMod,
          results.pWallMod,
          results.oppGemMod,
          results.oppMagMod,
          results.oppCastleMod,
          results.oppWallMod);
    
    this->sendEvent(1, eventContent);
}

void    NetworkLogic::sendDiscardResult(int gems) {
    ExitGames::Common::Hashtable* eventContent = new ExitGames::Common::Hashtable();
    
    eventContent->put<int, int>(1, 0);
    eventContent->put<int, bool>(2, false);
    eventContent->put<int, int>(3, gems);
    eventContent->put<int, int>(4, 0);
    eventContent->put<int, int>(5, 0);
    eventContent->put<int, int>(6, 0);
    eventContent->put<int, int>(7, 0);
    eventContent->put<int, int>(8, 0);
    eventContent->put<int, int>(9, 0);
    eventContent->put<int, int>(10, 0);
    
    CCLOG("Sent : discard for %d", gems);
    
    this->sendEvent(1, eventContent);
}

void NetworkLogic::sendEvent(nByte code, ExitGames::Common::Hashtable* eventContent)
{
    mLoadBalancingClient.opRaiseEvent(true, eventContent, 1, code);
}