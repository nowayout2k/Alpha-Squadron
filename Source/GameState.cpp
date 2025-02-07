// Copyright (c) 2025 No Way Out LLC All rights reserved.
#include "../Headers/GameState.h"

bool GameState::update(sf::Time deltaTime)
{
	m_world.update(deltaTime);
	if(!m_world.isPlayerAlive() && !m_world.isPlayerAircraftExploding())
	{
		getContext().Player->setMissionStatus(Player::MissionStatus::Failure);
		requestStackPush(StateId::GameOver);
	}
	else if(m_world.hasPlayerReachedEnd())
	{
		getContext().Player->setMissionStatus(Player::MissionStatus::Success);
		requestStackPush(StateId::GameOver);
	}

	CommandQueue& commands = m_world.getCommandQueue();
	getContext().Player->handleRealtimeInput(commands);

	return true;
}

void GameState::render()
{
	m_world.render();
}

bool GameState::handleEvent(const sf::Event& event)
{
	CommandQueue& commands = m_world.getCommandQueue();
	getContext().Player->handleEvent(event, commands);
	return true;
}
