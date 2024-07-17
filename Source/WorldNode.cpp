//
// Created by Johnnie Otis on 6/30/24.
//
#include "../Header/WorldNode.h"
#include "../Header/Debug.h"

void WorldNode::renderState(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	render(target, states);
	for (const SmartNode& child : m_children)
	{
		child->renderState(target, states);
	}
}

sf::Transform WorldNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const WorldNode* node = this; node != nullptr; node = node->m_parent)
		transform = node->getTransform() * transform;

	return transform;
}

sf::Vector2f WorldNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

void WorldNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	draw(target, states);
}

void WorldNode::updateState(float deltaTime)
{
	if(!isActive())
		return;

	update(deltaTime);
	for (const SmartNode& child : m_children)
	{
		child->updateState(deltaTime);
	}
}

void WorldNode::attachNode(WorldNode::SmartNode child)
{
	child->m_parent = this;
	m_children.push_back(std::move(child));
}

WorldNode::SmartNode WorldNode::detachNode(const WorldNode& node)
{
	auto found = std::find_if(m_children.begin(), m_children.end(),
		[&] (SmartNode& p) -> bool { return p.get() == &node; });
	if(found != m_children.end())
		Debug::logError(std::logic_error("Child is not present so it cannot be detached."));
	SmartNode result = std::move(*found);
	result->m_parent = nullptr;
	m_children.erase(found);
	return result;
}

void WorldNode::loadStateResources()
{
	loadResources();
	for (const SmartNode& child : m_children)
	{
		child->loadStateResources();
	}
}
