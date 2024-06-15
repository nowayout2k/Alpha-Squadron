//
// Created by Johnnie Otis on 6/8/24.
//

#ifndef ALPHA_SQUADRON_HEADER_PROJECTILE_H_
#define ALPHA_SQUADRON_HEADER_PROJECTILE_H_

#include "GameSprite.h"

class Projectile : public GameSprite
{
 public:
	explicit Projectile(Entity* owner, sf::Vector2f spawnPos, sf::Vector2f velocity);
	void update(float deltaTime) override;
	void collision(const Entity* other) override;
	void render(sf::RenderWindow& renderWindow, sf::RenderStates states);
	const Entity* getOwner() const { return m_owner;};
 private:
	Entity* m_owner;
	sf::Vector2f m_velocity;
};

#endif //ALPHA_SQUADRON_HEADER_PROJECTILE_H_
