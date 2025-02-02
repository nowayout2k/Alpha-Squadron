// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef LABEL_H_
#define LABEL_H_
#include <SFML/Graphics/Text.hpp>
#include "Component.h"

namespace GUI
{
	class Label : public Component
	{
	 public:
		typedef std::shared_ptr<Label> Ptr;
		explicit Label(const std::string& text);
		virtual bool isSelectable() const;
		void setText(const unsigned int size, const std::string& text);
		virtual void handleEvent(const sf::Event& event);
	 private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::Text m_text;
	};
}
#endif //LABEL_H_
