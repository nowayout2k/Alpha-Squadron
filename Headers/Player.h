// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Network/TcpSocket.hpp>
#include "CommandQueue.h"
#include "Aircraft.h"
#include "World.h"
#include "KeyBinding.h"

class Player
{
 public:
	enum MissionStatus
	{
		None,
		Success,
		Failure
	};

	typedef LocalPlayerAction::ActionType ActionType;
	Player(sf::TcpSocket* socket, sf::Int32 identifier, const KeyBinding* binding);
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);
	MissionStatus getMissionStatus() { return m_missionStatus; }
	void setMissionStatus(MissionStatus missionStatus) { m_missionStatus = missionStatus; }
	bool isLocal() const;
	void disableAllRealtimeActions();
	void handleRealtimeNetworkInput(CommandQueue& commands);
	void handleNetworkEvent(ActionType action, CommandQueue& commands);
	void handleNetworkRealtimeChange(ActionType action, bool actionEnabled);
 private:
	static bool isRealtimeAction(ActionType actionType);
 private:
	const KeyBinding* m_keyBinding;
	std::map<ActionType, Command> m_actionBinding;

	static std::vector<ActionType> m_realTimeActionTypes;
	MissionStatus m_missionStatus;
	int m_identifier;
	sf::TcpSocket* m_socket;
	std::map<ActionType, bool> m_actionProxies;

};

#endif //PLAYER_H_
