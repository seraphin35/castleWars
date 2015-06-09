#ifndef __NETWORK_LOGIC_H
#define __NETWORK_LOGIC_H

#include <array>
#include <queue>

#include "SRes.h"

#include "LoadBalancing-cpp/inc/Client.h"

enum State
{
	STATE_INITIALIZED = 0,
	STATE_CONNECTING,
	STATE_CONNECTED,
	STATE_JOINING,
	STATE_JOINED,
	STATE_LEAVING,
	STATE_LEFT,
	STATE_DISCONNECTING,
	STATE_DISCONNECTED
};

enum Input
{
	INPUT_NON = 0,
	INPUT_1,
	INPUT_2,
	INPUT_EXIT
};

enum Event
{
    EVENT_NOTHING = 0,
    EVENT_NEW_MSG,
    EVENT_OPP_JOINED,
    EVENT_OPP_CONFIRMED,
    EVENT_START_FIRST,
    EVENT_START_SECOND,
    EVENT_OPP_LEFT
};

class NetworkLogicListener : public ExitGames::Common::ToString
{
public:
	using ExitGames::Common::ToString::toString;
	virtual void stateUpdate(State newState) = 0;
	virtual ExitGames::Common::JString& toString(ExitGames::Common::JString& retStr, bool withTypes=false) const;
};

class StateAccessor
{
public:
	State getState(void) const;
	void setState(State newState);
	void registerForStateUpdates(NetworkLogicListener* listener);

private:
	State mState;
	ExitGames::Common::JVector<NetworkLogicListener*> mStateUpdateListeners;
};



class NetworkLogic : private ExitGames::LoadBalancing::Listener
{
public:
	//NetworkLogic(OutputListener* listener, const ExitGames::LoadBalancing::AuthenticationValues& authenticationValues=ExitGames::LoadBalancing::AuthenticationValues());
	NetworkLogic(const ExitGames::LoadBalancing::AuthenticationValues& authenticationValues=ExitGames::LoadBalancing::AuthenticationValues());
	void registerForStateUpdates(NetworkLogicListener* listener);
	void run(void);
	bool connect(void);
	bool opCreateRoom(void);
	bool opJoinRandomRoom(void);
	void disconnect(void);
    void sendPlayResult(SRes::playResults *results);
	void sendEvent(void);

	Input getLastInput(void) const;
	void setLastInput(Input newInput);
	State getState(void) const;
	
	
	// ルームが存在するか否かを返すメソッド
	bool isRoomExists(void);
	// イベントを送信するメソッド
	void sendEvent(nByte code, ExitGames::Common::Hashtable* eventContent);
 
	// 自分のプレイヤー番号
	int playerNr = 0;
    Event lastEvent = EVENT_NOTHING;
    
private:
	// receive and print out debug out here
	virtual void debugReturn(ExitGames::Common::DebugLevel::DebugLevel debugLevel, const ExitGames::Common::JString& string);

	// implement your error-handling here
	virtual void connectionErrorReturn(int errorCode);
	virtual void clientErrorReturn(int errorCode);
	virtual void warningReturn(int warningCode);
	virtual void serverErrorReturn(int errorCode);			

	// events, triggered by certain operations of all players in the same room
	virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);
	virtual void leaveRoomEventAction(int playerNr, bool isInactive);
	virtual void disconnectEventAction(int playerNr);
	virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent);
    
    //virtual void onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStats>& lobbyStats);
    //virtual void onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStats>& lobbyStats);
    virtual void onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegions, const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegionServers);

	// callbacks for operations on PhotonLoadBalancing server
	virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString);
	virtual void disconnectReturn(void);
	virtual void createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinLobbyReturn(void);
	virtual void leaveLobbyReturn(void);

	ExitGames::LoadBalancing::Client mLoadBalancingClient;
	ExitGames::Common::JString mLastJoinedRoom;
	int mLastActorNr;
	ExitGames::Common::Logger mLogger;
	StateAccessor mStateAccessor;
	Input mLastInput;
	
    void    sendStartSignal(bool first);
    void    pushResultToQueue(ExitGames::Common::Hashtable *content);
    std::queue<SRes::playResults>   eventQueue;
};

#endif