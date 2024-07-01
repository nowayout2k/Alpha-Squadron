//
// Created by Johnnie Otis on 6/30/24.
//

#ifndef WORLDNODE_H_
#define WORLDNODE_H_
#include <iostream>
#include <SFML/Graphics.hpp>

class WorldNode : public sf::Transformable, public sf::Drawable
{
	typedef std::unique_ptr<WorldNode> SmartNode;
 public:
	explicit WorldNode() : m_isActive(true) {}
	void attachNode(SmartNode node);
	SmartNode detachNode(const WorldNode& node);
	void setActive(bool isActive) { m_isActive = isActive; }
	bool isActive() const { return m_isActive; };
	virtual void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const { if(!isActive())return; }
 private:
	WorldNode(const WorldNode&) = delete;
	WorldNode& operator=(const WorldNode& other) = delete;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

	bool m_isActive;
	std::vector<SmartNode> m_children;
	WorldNode* m_parent;
};

#endif //WORLDNODE_H_
