//
// Created by Johnnie Otis on 5/26/24.
//

#ifndef SFML_CORE_HEADER_GRAPHICS_H_
#define SFML_CORE_HEADER_GRAPHICS_H_

#include <SFML/Graphics/RenderWindow.hpp>
class Graphics
{
public:
	sf::RenderWindow& CreateWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);
	static sf::RenderWindow& GetCurrentWindow() { return currentWindow; }

 private:
	static sf::RenderWindow currentWindow;

	/*Drawable Object Functions:

		sf::Drawable::setColor: Sets the color of the drawable object.
	sf::Drawable::setPosition: Sets the position of the drawable object.
	sf::Drawable::setRotation: Sets the rotation of the drawable object.
	sf::Drawable::setScale: Sets the scale of the drawable object.

	Texture Functions:

		sf::Texture::loadFromFile: Loads a texture from a file.
	sf::Texture::create: Creates a new empty texture.
	sf::Texture::setSmooth: Sets whether the texture should be smoothed (for resizing).

	Sprite Functions:

		sf::Sprite::setTexture: Sets the texture of the sprite.
	sf::Sprite::setTextureRect: Sets the texture rectangle of the sprite.
	sf::Sprite::setColor: Sets the color of the sprite.

	Shape Functions:

		sf::Shape::setFillColor: Sets the fill color of the shape.
	sf::Shape::setOutlineColor: Sets the outline color of the shape.
	sf::Shape::setOutlineThickness: Sets the thickness of the shape's outline.

	Text Functions:

		sf::Text::setString: Sets the string of the text.
	sf::Text::setFont: Sets the font of the text.
	sf::Text::setCharacterSize: Sets the character size of the text.*/


};


#endif //SFML_CORE_HEADER_GRAPHICS_H_
