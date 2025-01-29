//
// Created by Johnnie Otis on 1/29/25.
//

#include "Pickup.h"
#include "Audio.h"

Pickup::Pickup(PickupType type) : m_type(type),
									GameSprite(true,
										TextureId::EnemiesSpriteSheet,
										sf::IntRect(211, 213, 7, 9))
{
	setScale(1.0f, 1.0f);
	Audio::playSound(SoundFxId::Collect, 10);
}

unsigned int Pickup::getCategory() const
{
	return 0;
}

void Pickup::apply(Aircraft& player) const
{

}
void Pickup::render(sf::RenderTarget& renderTarget, sf::RenderStates states) const
{
	GameSprite::render(renderTarget, states);
}
