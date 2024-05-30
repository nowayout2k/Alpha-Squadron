//
// Created by Johnnie Otis on 5/26/24.
//

#ifndef SFML_CORE_HEADER_GRAPHICS_H_
#define SFML_CORE_HEADER_GRAPHICS_H_

#include <SFML/Graphics.hpp>

class Graphics
{
public:
	sf::RenderWindow& CreateWindow(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style);

 private:
	static sf::RenderWindow currentWindow;
	sf::VertexBuffer vertexBuffer;
	sf::VertexArray vertexArray;

};


#endif //SFML_CORE_HEADER_GRAPHICS_H_
