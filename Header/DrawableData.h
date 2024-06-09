//
// Created by Johnnie Otis on 6/8/24.
//

#ifndef ALPHA_SQUADRON_HEADER_DRAWABLEDATA_H_
#define ALPHA_SQUADRON_HEADER_DRAWABLEDATA_H_
#include <SFML/Graphics/Drawable.hpp>
struct DrawableData
{
	DrawableData(sf::Drawable* drawable, bool usesTransformState)
	{
		this->drawable = drawable;
		this->usesTransformState = usesTransformState;
	}

	sf::Drawable* drawable;
	bool usesTransformState;
};
#endif //ALPHA_SQUADRON_HEADER_DRAWABLEDATA_H_
