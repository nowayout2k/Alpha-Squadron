//
// Created by Johnnie Otis on 6/8/24.
//

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameSprite.h"
#include "CommandQueue.h"
#include "../Game/ProjectileType.h"

class Projectile : public GameSprite
{
 public:
	explicit Projectile(ProjectileType projectileType, sf::Vector2f targetDirection);
	void update(float deltaTime, CommandQueue& commands) override;
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override;
	void collision(const Entity* other) override;
	void guideTowards(sf::Vector2f position);
	bool isGuided() const;
	unsigned int getNodeType() const override { return GameSprite::getNodeType() | (int)NodeType::Projectile; }
	float getMaxSpeed() const;
	int getDamage() const;
 private:
	sf::Vector2f m_targetDirection;
	ProjectileType m_projectileType;
};

#endif //PROJECTILE_H_
