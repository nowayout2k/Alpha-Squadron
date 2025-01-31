//
// Created by Johnnie Otis on 10/15/24.
//

#ifndef DATATABLES_H_
#define DATATABLES_H_
#include <SFML/Graphics/Rect.hpp>
#include <unordered_map>
#include <vector>
#include "TextureId.h"
#include "AircraftType.h"
#include "AiRoutine.h"
#include "Direction.h"
#include "PickupType.h"
#include "ProjectileType.h"
#include <string>
#include <functional>
class Aircraft;

struct AircraftData
{
	AircraftType Type;
	int Health;
	float Speed;
	float DespawnDistance;
	Direction EnterDirection;
	Direction ExitDirection;
	TextureId TextureId;
	sf::IntRect TextureLoadArea;
	std::vector<AiRoutine> AiRoutines;
};

struct PickupData
{
	PickupType Type;
	float Value;
	TextureId TextureId;
	sf::IntRect TextureLoadArea;
	std::function<void(Aircraft&)> Action;
};

struct ProjectileData
{
	ProjectileType Type{};
	TextureId TextureId{};
	sf::IntRect TextureLoadArea{};
	float Value{};
};

struct GameData
{
	std::unordered_map<AircraftType, AircraftData> AircraftData;
	std::unordered_map<PickupType, PickupData> PickupData;
	std::unordered_map<ProjectileType, ProjectileData> ProjectileData;
};

GameData LoadData(const std::string& filename);

#endif //DATATABLES_H_
