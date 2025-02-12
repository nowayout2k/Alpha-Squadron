// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/Pickup.h"
#include "../Headers/Audio.h"
#include "../Headers/World.h"

Pickup::Pickup(PickupType type) : m_pickupType(type), m_action(),
								  GameSprite(true,
										true,
										sf::IntRect(),
										sf::IntRect(), false)
{
	setScale(1.0f, 1.0f);
}

void Pickup::setPickupColor()
{
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
	m_action(player);
}

void Pickup::render(sf::RenderTarget& renderTarget, sf::RenderStates states) const
{
	GameSprite::render(renderTarget, states);
}

void Pickup::update(sf::Time deltaTime, CommandQueue& commands)
{
	GameSprite::update(deltaTime, commands);
}
void Pickup::loadResources()
{
	auto dataPair = World::GameData.PickupData.find(m_pickupType);

	if (dataPair != World::GameData.PickupData.end())
	{
		auto data = dataPair->second;
		m_action = data.Action;
		setTextureId(data.TextureId);
		setTextureLoadArea(data.TextureLoadArea);
	}
	GameSprite::loadResources();
}
