//
// Created by Johnnie Otis on 6/8/24.
//

#ifndef ALPHA_SQUADRON_HEADER_BULLET_H_
#define ALPHA_SQUADRON_HEADER_BULLET_H_

#include "SpriteEntity.h"

class Bullet : public SpriteEntity
{
 public:
	explicit Bullet(Entity* owner, sf::Vector2f spawnPos);
	void update(float deltaTime) override;
	void collision(const Entity* other) override;
	const Entity* getOwner() const { return m_owner;};
 private:
	Entity* m_owner;
};

#endif //ALPHA_SQUADRON_HEADER_BULLET_H_
