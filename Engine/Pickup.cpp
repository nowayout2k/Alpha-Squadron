//
// Created by Johnnie Otis on 1/29/25.
//

#include "Pickup.h"
#include "Audio.h"

Pickup::Pickup(Pickup::Type type) : m_type(type),
									GameSprite(true,
										TextureId::EnemiesSpriteSheet,
										sf::IntRect(211, 213, 7, 9))
{
	setScale(1.0f, 1.0f);
	Audio::playSound(SoundFxId::Collect, 10);
}

sf::FloatRect Pickup::getBoundingRect() const
{
	return sf::FloatRect();
}

unsigned int Pickup::getCategory() const
{
	return 0;
}

void Pickup::apply(Aircraft& player) const
{

}
