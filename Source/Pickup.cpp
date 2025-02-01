//
// Created by Johnnie Otis on 1/29/25.
//

#include "../Headers/Pickup.h"
#include "../Headers/Audio.h"
#include "../Headers/World.h"

Pickup::Pickup(PickupType type) : m_type(type),
									GameSprite(true,
										TextureId::EnemiesSpriteSheet, true,
										sf::IntRect(192, 213, 7, 7),
										sf::IntRect(), false)
{
	setScale(4.0f, 4.0f);
	setPickupColor();
}

void Pickup::setPickupColor()
{
	switch (m_type)
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
	Audio::playSound(SoundFxId::Collect, 10);
	World::GameData.PickupData[m_type].Action(player);
}

void Pickup::render(sf::RenderTarget& renderTarget, sf::RenderStates states) const
{
	GameSprite::render(renderTarget, states);
}

void Pickup::update(float deltaTime, CommandQueue& commands)
{
	GameSprite::update(deltaTime, commands);
}
