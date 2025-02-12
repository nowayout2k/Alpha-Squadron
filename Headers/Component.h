// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>

namespace GUI
{
	class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
	 public:
		typedef std::shared_ptr<Component> Ptr;
	 public:
		Component();
		~Component() override;
		bool isSelected() const;
		virtual void select();
		virtual void deselect();
		virtual bool isActive() const;
		virtual void activate();
		virtual void deactivate();
		virtual bool isSelectable() const = 0;
		virtual void handleEvent(const sf::Event& event) = 0;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
	 private:
		bool m_isSelected;
		bool m_isActive;
	};
}

#endif //COMPONENT_H_
