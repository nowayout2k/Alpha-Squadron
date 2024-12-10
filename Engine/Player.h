//
// Created by Johnnie Otis on 8/12/24.
//

#ifndef PLAYER_H_
#define PLAYER_H_

#include "CommandQueue.h"
#include "../Game/Aircraft.h"



struct AircraftMover
{
	AircraftMover(float vx, float vy) : m_velocity(vx, vy){}
	void operator() (Aircraft& aircraft, float dt) const
	{
		aircraft.accelerate(m_velocity * aircraft.getMaxSpeed());
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
	Player();
	void assignKey(ActionType actionType, sf::Keyboard::Key key);

	sf::Keyboard::Key getAssignedKey(ActionType actionType) const;

	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);
 private:
	static bool isRealtimeAction(ActionType actionType);
 private:
	std::map<sf::Keyboard::Key, ActionType> m_keyBinding;
	std::map<ActionType, Command> m_actionBinding;

	static std::vector<ActionType> m_realTimeActionTypes;
};

#endif //PLAYER_H_
