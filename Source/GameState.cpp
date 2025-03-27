// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/GameState.h"
#include "../Headers/Audio.h"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, m_world(*context.Window, *context.Audio, false)
	, m_player(nullptr, 1, context.KeysPlayer1)
{
	m_world.addAircraft(1);
	m_player.setMissionStatus(Player::MissionStatus::None);

	// Play game theme
	context.Audio->playMusic(MusicId::GameMusic, 12.f);
}

bool GameState::update(sf::Time deltaTime)
{
	m_world.update(deltaTime);

	if (!m_world.hasPlayerAlive())
	{
		m_player.setMissionStatus(Player::MissionStatus::Failure);
		requestStackPush(StateId::GameOver);
	}
	else if (m_world.hasPlayerReachedEnd())
	{
		m_player.setMissionStatus(Player::MissionStatus::Success);
		requestStackPush(StateId::MissionSuccess);
	}

	CommandQueue& commands = m_world.getCommandQueue();
	m_player.handleRealtimeInput(commands);

	return true;
}

void GameState::render()
{
	m_world.render();
}

bool GameState::handleEvent(const sf::Event& event)
{
	CommandQueue& commands = m_world.getCommandQueue();
	m_player.handleEvent(event, commands);
	return true;
}
