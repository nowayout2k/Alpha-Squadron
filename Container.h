//
// Created by Johnnie Otis on 10/13/24.
//

#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <vector>
#include "Component.h"

namespace GUI
{
	class Container : public Component
	{
	 public:
		typedef std::shared_ptr<Container> Ptr;
		Container();
		void pack(Component::Ptr component);
		void handleEvent(const sf::Event& event);
		bool hasSelection() const;
		bool isSelectable() const;
		void select(int index);
		void selectNext();
		void selectPrevious();
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	 private:
		int m_selectedChild;
		std::vector<Component::Ptr> m_children;
	};
}
#endif //CONTAINER_H_
