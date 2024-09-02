//
// Created by Johnnie Otis on 6/8/24.
//

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameSprite.h"

class Projectile : public GameSprite
{
 public:
	explicit Projectile(NodeType owner, sf::Vector2f spawnPos, sf::Vector2f velocity);
	void update(float deltaTime) override;
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override;
	void collision(const Entity* other) override;
	const NodeType getOwnerType() const { return m_ownerType;};
 private:
	NodeType m_ownerType;
};

#endif //PROJECTILE_H_
