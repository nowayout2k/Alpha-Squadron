//
// Created by Johnnie Otis on 8/12/24.
//

#ifndef PLAYER_H_
#define PLAYER_H_

#include "CommandQueue.h"
#include "../Game/Aircraft.h"

class Input
{
 public:
	enum ActionType
	{
		AccelerateNegX,
		AcceleratePosX,
		AccelerateNegY,
		AcceleratePosY,
		ActionCount
	};
	Input();
	void assignKey(ActionType actionType, sf::Keyboard::Key key);

	sf::Keyboard::Key getAssignedKey(ActionType actionType) const;

	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealtimeInput(CommandQueue& commands);

	template <typename GameObject, typename Function>
	std::function<void(WorldNode&, float)> derivedAction(Function fn)
	{
		return [=] (WorldNode& node, float dt)
		{
		  //assert(dynamic_cast<GameObject*>(&node) != nullptr);
		  fn(static_cast<GameObject&>(node), dt);
		};
	}

	struct AircraftMover
	{
		AircraftMover(float vx, float vy) : m_velocity(vx, vy){}
		void operator() (Aircraft& aircraft, float dt) const
		{
			aircraft.accelerate(m_velocity);
		}
		sf::Vector2f m_velocity;
	};
 private:
	static bool isRealtimeAction(ActionType actionType);
 private:
	std::map<sf::Keyboard::Key, ActionType> m_keyBinding;
	std::map<ActionType, Command> m_actionBinding;

	static std::vector<ActionType> m_realTimeActionTypes;
	const float m_playerSpeed = 800.f;
};

#endif //PLAYER_H_
