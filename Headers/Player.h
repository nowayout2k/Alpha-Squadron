// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef PLAYER_H_
#define PLAYER_H_

#include "CommandQueue.h"
#include "Aircraft.h"
#include "World.h"


struct AircraftMover
{
	AircraftMover(float vx, float vy) : m_velocity(vx, vy){}
	explicit AircraftMover(const sf::Vector2f& mVelocity) : m_velocity(mVelocity)
	{
	}
	void operator() (Aircraft& aircraft, float dt) const
	{
		aircraft.accelerate(sf::Vector2f(m_velocity.x < 0 ? -World::getScrollSpeed() + (m_velocity.x * aircraft.getMaxSpeed()) : m_velocity.x * aircraft.getMaxSpeed(), m_velocity.y * aircraft.getMaxSpeed()));
	}
 private:
	sf::Vector2f m_velocity;
};

class Player
{
 public:
	enum ActionType
	{
		AccelerateNegX,
		AcceleratePosX,
		AccelerateNegY,
		AcceleratePosY,
		Fire,
		LaunchMissile,
		ActionCount
	};

	enum MissionStatus
	{
		None,
		Success,
		Failure
	};

	Player();
	void assignKey(ActionType actionType, sf::Keyboard::Key key);

	sf::Keyboard::Key getAssignedKey(ActionType actionType) const;

	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);
	MissionStatus getMissionStatus() { return m_missionStatus; }
	void setMissionStatus(MissionStatus missionStatus) { m_missionStatus = missionStatus; }
 private:
	static bool isRealtimeAction(ActionType actionType);
 private:
	std::map<sf::Keyboard::Key, ActionType> m_keyBinding;
	std::map<ActionType, Command> m_actionBinding;

	static std::vector<ActionType> m_realTimeActionTypes;
	MissionStatus m_missionStatus;
};

#endif //PLAYER_H_
