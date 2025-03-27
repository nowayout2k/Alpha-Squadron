// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../../Headers/Game/Pickup.h"
#include "../../Headers/Engine/Audio.h"
#include "../../Headers/Engine/World.h"

namespace AlphaSquadron
{
	Pickup::Pickup(PickupType type)
		: m_pickupType(type), m_action(),
		  GameSprite(true, true, sf::IntRect(), sf::IntRect(), false)
	{
		// Set default scale for the pickup.
		setScale(1.0f, 1.0f);
	}

	void Pickup::setPickupColor()
	{
		// Set the pickup's color based on its type.
		switch (m_pickupType)
		{
		case PickupType::FireRate:
			setColor(sf::Color::Black);
			break;
		case PickupType::MissileRefill:
			setColor(sf::Color::Blue);
			break;
		case PickupType::FireSpread:
			setColor(sf::Color::Red);
			break;
		case PickupType::HealthRefill:
			setColor(sf::Color::Green);
			break;
		default:
			setColor(sf::Color::White);
			break;
		}
	}

	void Pickup::apply(Aircraft& player) const
	{
		// Apply the stored action to the player.
		m_action(player);
	}

	void Pickup::render(sf::RenderTarget& renderTarget, sf::RenderStates states) const
	{
		// Delegate rendering to the base GameSprite class.
		GameSprite::render(renderTarget, states);
	}

	void Pickup::update(sf::Time deltaTime, Engine::CommandQueue& commands)
	{
		// Update the pickup's state by calling the base class update.
		GameSprite::update(deltaTime, commands);
	}

	void Pickup::loadResources()
	{
		// Retrieve pickup data from the world game data using the pickup type.
		auto dataPair = World::GameData.PickupData.find(m_pickupType);

		if (dataPair != World::GameData.PickupData.end())
		{
			// Set the action and texture properties based on the game data.
			auto data = dataPair->second;
			m_action = data.Action;
			setTextureId(data.TextureId);
			setTextureLoadArea(data.TextureLoadArea);
		}

		// Load resources defined in the base GameSprite class.
		GameSprite::loadResources();
	}
}