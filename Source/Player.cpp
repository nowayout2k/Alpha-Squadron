//
// Created by Johnnie Otis on 8/12/24.
//

#include "../Header/Player.h"

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.category |= (int)NodeType::Player;
		output.action = [] (WorldNode& worldNode, float dt)
		{
		  std::cout << worldNode.getPosition().x << ","
					<< worldNode.getPosition().y << "\n";
		};
		commands.push(output);
	}
	if (event.type == sf::Event::Resized)
	{
		Debug::log("Window resized to " + std::to_string(event.size.width) + "x" + std::to_string(event.size.height));
	}

	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::F)
		Debug::toggleFps();
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	const float playerSpeed = 800.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Command moveLeft;
		moveLeft.category |= (int)NodeType::Player;
		moveLeft.action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
		commands.push(moveLeft);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		Command moveLeft;
		moveLeft.category |= (int)NodeType::Player;
		moveLeft.action = derivedAction<Aircraft>(AircraftMover(playerSpeed, 0.f));
		commands.push(moveLeft);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Command moveLeft;
		moveLeft.category |= (int)NodeType::Player;
		moveLeft.action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
		commands.push(moveLeft);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Command moveLeft;
		moveLeft.category |= (int)NodeType::Player;
		moveLeft.action = derivedAction<Aircraft>(AircraftMover(0.f, playerSpeed));
		commands.push(moveLeft);
	}
}
