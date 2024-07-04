//
// Created by Johnnie Otis on 6/8/24.
//

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameSprite.h"

class Projectile : public GameSprite
{
 public:
	explicit Projectile(Entity* owner, sf::Vector2f spawnPos, sf::Vector2f velocity);
	void update(float deltaTime) override;
	void collision(const Entity* other) override;
	const Entity* getOwner() const { return m_owner;};
 private:
	Entity* m_owner;
};

#endif //PROJECTILE_H_
