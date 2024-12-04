//
// Created by Johnnie Otis on 10/15/24.
//

#ifndef DATATABLES_H_
#define DATATABLES_H_
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include "TextureId.h"
#include "AircraftType.h"
#include "Direction.h"

struct AircraftData
{
	AircraftType type;
	int health;
	float speed;
	TextureId textureId;
	sf::IntRect textureLoadArea;
	std::vector<Direction> directions;
};

std::vector<AircraftData> LoadAircraftData(const std::string& filename);

#endif //DATATABLES_H_
