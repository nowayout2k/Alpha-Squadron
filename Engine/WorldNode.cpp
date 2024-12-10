//
// Created by Johnnie Otis on 6/30/24.
//
#include "WorldNode.h"
#include "Debug.h"
#include "Command.h"

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

void WorldNode::updateHierarchy(float deltaTime, CommandQueue& commands)
{
	if(!isActive())
		return;

	update(deltaTime, commands);
	for (const SmartNode& child : m_children)
	{
		if(child == nullptr)
		{
			Debug::logWarning("Child node is null!");
			continue;
		}
		child->updateHierarchy(deltaTime, commands);
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
		Debug::logError("Child is not present so it cannot be detached.");
	SmartNode result = std::move(*found);
	result->m_parent = nullptr;
	m_children.erase(found);
	return result;
}

void WorldNode::loadHierarchyResources()
{
	loadResources();
	for (const SmartNode& child : m_children)
	{
		child->loadHierarchyResources();
	}
}

void WorldNode::onCommand(const Command& command, float deltaTime)
{
	if ((command.nodeType & getNodeType()) && (command.target == this || command.target == nullptr))
		command.action(*this, deltaTime);
	for(auto& child : m_children)
		child->onCommand(command, deltaTime);
}
