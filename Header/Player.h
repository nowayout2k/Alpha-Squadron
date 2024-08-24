//
// Created by Johnnie Otis on 8/12/24.
//

#ifndef PLAYER_H_
#define PLAYER_H_

#include "CommandQueue.h"
#include "Aircraft.h"

class Player
{
 public:
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
		AircraftMover(float vx, float vy) : velocity(vx, vy){}
		void operator() (Aircraft& aircraft, float dt) const
		{
			aircraft.accelerate(velocity);
		}
		sf::Vector2f velocity;
	};
};

#endif //PLAYER_H_
