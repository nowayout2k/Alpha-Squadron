// Copyright (c) 2025 No Way Out LLC All rights reserved.
#include "../Headers/GameState.h"

bool GameState::update(sf::Time deltaTime)
{
	m_world.update(deltaTime);
	if(!m_world.isPlayerAlive() && !m_world.isPlayerAircraftExploding())
	{
		getContext().player->setMissionStatus(Player::MissionStatus::Failure);
		requestStackPush(StateId::GameOver);
	}
	else if(m_world.hasPlayerReachedEnd())
	{
		getContext().player->setMissionStatus(Player::MissionStatus::Success);
		requestStackPush(StateId::GameOver);
	}

	CommandQueue& commands = m_world.getCommandQueue();
	getContext().player->handleRealtimeInput(commands);

	return true;
}

void GameState::render(sf::RenderStates& states)
{
	m_world.render(*getContext().window, states);
}
bool GameState::handleEvent(const sf::Event& event)
{
	CommandQueue& commands = m_world.getCommandQueue();
	getContext().player->handleEvent(event, commands);
	return true;
}
