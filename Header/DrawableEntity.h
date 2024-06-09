//
// Created by Johnnie Otis on 6/8/24.
//

#ifndef ALPHA_SQUADRON_HEADER_DRAWABLEENTITY_H_
#define ALPHA_SQUADRON_HEADER_DRAWABLEENTITY_H_
#include "Entity.h"
#include "DrawableData.h"

class DrawableEntity : public Entity, public sf::Transformable, public sf::Drawable
{
 protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		for (const auto& drawableData : m_drawablesData)
		{
			if(isActive())
			{
				sf::Drawable* drawable = drawableData.drawable;
				if(drawableData.usesTransformState)
				{
					states.transform *= getTransform();
				}

				target.draw(*drawable, states.transform);
			}
		}
	};
	void addDrawable(sf::Drawable* drawable, bool usesTransformState)
	{
		m_drawablesData.push_back(DrawableData(drawable, usesTransformState));
	}

 private:
	std::vector<DrawableData> m_drawablesData;
};

#endif //ALPHA_SQUADRON_HEADER_DRAWABLEENTITY_H_
