//
// Created by Johnnie Otis on 10/13/24.
//

#include "Label.h"
#include "ResourceManager.h"
#include "Utility.h"

GUI::Label::Label(const std::string& text) : m_text(text, ResourceManager::loadResource(FontId::Gamer), 16)
{
}

bool GUI::Label::isSelectable() const
{
	return false;
}

void GUI::Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_text, states);
}

void GUI::Label::setText(const unsigned int size, const std::string& text)
{
	m_text.setCharacterSize(size);
	m_text.setString(text);
	Utility::centerOrigin(m_text);
}

void GUI::Label::handleEvent(const sf::Event&)
{
}