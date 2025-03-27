// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../../Headers/Engine/Label.h"
#include "../../Headers/Game/ResourceManager.h"
#include "../../Headers/Engine/Utility.h"

namespace Engine
{
	Label::Label(const std::string& text)
		: m_text(text, AlphaSquadron::ResourceManager::loadResource(FontId::Arnold), 16)
	{
	}

	bool Label::isSelectable() const
	{
		return false;
	}

	void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(m_text, states);
	}

	void Label::setText(const unsigned int size, const std::string& text)
	{
		m_text.setCharacterSize(size);
		m_text.setString(text);
		Utility::centerOrigin(m_text);
	}

	void Label::handleEvent(const sf::Event&)
	{
		// Label does not handle events.
	}
}
