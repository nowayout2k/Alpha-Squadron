// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/Container.h"
#include "../Headers/Debug.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

GUI::Container::Container() : m_children(), m_selectedChild(-1)
{
}

void GUI::Container::pack(Component::Ptr component)
{
	m_children.push_back(component);
	if (!hasSelection() && component->isSelectable())
		select(m_children.size() - 1);
}

void GUI::Container::handleEvent(const sf::Event& event)
{
	if (hasSelection() && m_children[m_selectedChild]->isActive())
	{
		m_children[m_selectedChild]->handleEvent(event);
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
		{
			selectPrevious();
		}
		else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
		{
			selectNext();
		}
		else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
		{
			if (hasSelection())
				m_children[m_selectedChild]->activate();
		}
	}
}

bool GUI::Container::isSelectable() const
{
	return false;
}

void GUI::Container::select(int index)
{
	if (m_children[index]->isSelectable())
	{
		if (hasSelection())
			m_children[m_selectedChild]->deselect();
		m_children[index]->select();
		m_selectedChild = index;
	}
}
void GUI::Container::selectNext()
{
	if (!hasSelection())
		return;

	int next = m_selectedChild;
	do
		next = (next + 1) % m_children.size();
	while (!m_children[next]->isSelectable());
	// Select that component
	select(next);
}

bool GUI::Container::hasSelection() const
{
	return m_selectedChild >= 0;
}

void GUI::Container::selectPrevious()
{
	if (!hasSelection())
		return;

	int prev = m_selectedChild;
	do
		prev = (prev + m_children.size() - 1) % m_children.size();
	while (!m_children[prev]->isSelectable());

	select(prev);
}

void GUI::Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for(const GUI::Component::Ptr& child : m_children)
		target.draw(*child, states);
}
