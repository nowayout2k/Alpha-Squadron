// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <vector>
#include "Component.h"
#include "Audio.h"

namespace GUI
{
	class Container : public Component
	{
	 public:
		typedef std::shared_ptr<Container> Ptr;
		explicit Container(Audio* audio) : m_children(), m_selectedChild(-1), m_audio(*audio) {}
		void pack(Component::Ptr component);
		void handleEvent(const sf::Event& event) override;
		bool hasSelection() const;
		bool isSelectable() const override;
		void select(int index);
		void selectNext();
		void selectPrevious();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	 private:
		int m_selectedChild;
		std::vector<Component::Ptr> m_children;
		Audio& m_audio;
	};
}
#endif //CONTAINER_H_
