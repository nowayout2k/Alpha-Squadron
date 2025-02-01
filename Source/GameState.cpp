//
// Created by Johnnie Otis on 10/12/24.
//
#include "../Headers/GameState.h"

bool GameState::update(float deltaTime)
{
	m_world.update(deltaTime);
	CommandQueue& commands = m_world.getCommandQueue();
	getContext().input->handleRealtimeInput(commands);
	if(Player::getMissionStatus() != Player::MissionStatus::None)
		requestStackPush(StateId::GameOver);
	return true;
}

void GameState::render(sf::RenderStates& states)
{
	m_world.render(*getContext().window, states);
}
bool GameState::handleEvent(const sf::Event& event)
{
	CommandQueue& commands = m_world.getCommandQueue();
	getContext().input->handleEvent(event, commands);
	return true;
}
