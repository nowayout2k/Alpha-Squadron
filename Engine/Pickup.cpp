//
// Created by Johnnie Otis on 1/29/25.
//

#include "Pickup.h"
#include "Audio.h"
#include "World.h"

Pickup::Pickup(PickupType type) : m_type(type),
									GameSprite(true,
										TextureId::EnemiesSpriteSheet, true,
										sf::IntRect(211, 213, 7, 9))
{
	setScale(4.0f, 4.0f);
	Audio::playSound(SoundFxId::Collect, 10);
}

void Pickup::apply(Aircraft& player) const
{
	World::GameData.PickupData[m_type].Action(player);
}

void Pickup::render(sf::RenderTarget& renderTarget, sf::RenderStates states) const
{
	Debug::log("Pickup pos", getWorldPosition().x, getWorldPosition().y);
	GameSprite::render(renderTarget, states);
}

void Pickup::update(float deltaTime, CommandQueue& commands)
{
	GameSprite::update(deltaTime, commands);
}
