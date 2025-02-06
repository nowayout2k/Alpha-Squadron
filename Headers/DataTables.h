// Copyright (c) 2025 No Way Out LLC All rights reserved.

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
#include "Particle.h"
#include <string>
#include <functional>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
class Aircraft;

struct AircraftData
{
	AircraftType Type;
	float Health;
	float Speed;
	float DespawnDistance;
	Direction EnterDirection;
	Direction ExitDirection;
	TextureId TextureId;
	sf::IntRect TextureLoadArea;
	sf::IntRect SpriteTextureRegion;
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
	float MaxSpeed{};
};

struct ParticleData
{
	Particle::Type Type{};
	sf::Color Color;
	sf::Time Lifetime;
};

struct GameData
{
	std::unordered_map<AircraftType, AircraftData> AircraftData;
	std::unordered_map<PickupType, PickupData> PickupData;
	std::unordered_map<ProjectileType, ProjectileData> ProjectileData;
	std::unordered_map<Particle::Type, ParticleData> ParticleData;
};

GameData LoadData(const std::string& filename);

#endif //DATATABLES_H_
