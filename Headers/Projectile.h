//
// Created by Johnnie Otis on 6/8/24.
//

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameSprite.h"
#include "CommandQueue.h"
#include "ProjectileType.h"

class Projectile : public GameSprite
{
 public:
	explicit Projectile(NodeType type, ProjectileType projectileType, sf::Vector2f targetDirection, sf::Vector2f launchDirection);
	void update(float deltaTime, CommandQueue& commands) override;
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override;
	void guideTowards(sf::Vector2f position);
	bool isGuided() const;
	unsigned int getNodeType() const override { return GameSprite::getNodeType() | static_cast<unsigned int>(m_type); }
	float getMaxSpeed() const;
	int getDamage() const;
 private:
	sf::Vector2f m_targetDirection;
	sf::Vector2f m_launchDirection;
	ProjectileType m_projectileType;
	NodeType m_type;
	bool m_isLaunching;
	float m_timeSinceLaunch;
};

#endif //PROJECTILE_H_
