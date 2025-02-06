// Created by Johnnie on 2/5/2025.
//

#ifndef ALPHA_SQUADRON_HEADERS_PARTICLE_H_
#define ALPHA_SQUADRON_HEADERS_PARTICLE_H_

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
struct Particle
{
	enum Type
	{
		None,
		Propellant,
		Smoke,
		ParticleTypeCount
	};

	sf::Vector2f Position;
	sf::Color Color;
	sf::Time Lifetime;
};

#endif //ALPHA_SQUADRON_HEADERS_PARTICLE_H_
