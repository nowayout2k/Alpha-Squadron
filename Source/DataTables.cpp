// Copyright (c) 2025 No Way Out LLC All rights reserved.
#include "../Headers/DataTables.h"
#include "../Headers/AircraftType.h"
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"
#include "../Headers/Aircraft.h"

void SetPickupAction(PickupData& data)
{
	switch(data.Type)
	{
	case PickupType::FireSpread:
		data.Action = [data] (Aircraft& a) { a.changeFireSpread((int)data.Value); };
		break;
	case PickupType::HealthRefill:
		data.Action = [data] (Aircraft& a) { a.changeHealth(data.Value); };
		break;
	case PickupType::MissileRefill:
		data.Action = [data] (Aircraft& a) { a.changeMissileCount((int)data.Value); };
		break;
	case PickupType::FireRate:
		data.Action = [data] (Aircraft& a) { a.changeFireRate((int)data.Value); };
		break;
	default:
		break;
	}
}

GameData LoadData(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open JSON file: " + filename);
	}

	nlohmann::json j;
	file >> j;

	GameData gameData;
	for (const auto& item : j["aircraft"])
	{
		AircraftData aircraftData;
		aircraftData.Type = Utility::stringToAircraftType(item["type"]);
		if(aircraftData.Type == AircraftType::AircraftTypeCount)
		{
			Debug::logError("Index is greater than length of array! Could not parse " + filename);
			return gameData;
		}

		aircraftData.Health = item["health"];
		aircraftData.Speed = item["maxSpeed"];
		aircraftData.TextureId = Utility::stringToTextureId(item["textureId"]);
		aircraftData.DespawnDistance = item["aiDespawnDistance"];
		aircraftData.EnterDirection = Utility::stringToDirection(item["aiEnterDirection"]);
		aircraftData.ExitDirection = Utility::stringToDirection(item["aiExitDirection"]);
		for (auto aiRoutine : item["aiRoutine"])
		{
			aircraftData.AiRoutines.emplace_back( aiRoutine["angle"], aiRoutine["distance"]);
		}

		auto left = item["textureLoadArea"]["left"];
		auto top = item["textureLoadArea"]["top"];
		auto width = item["textureLoadArea"]["width"];
		auto height = item["textureLoadArea"]["height"];

		aircraftData.TextureLoadArea = sf::IntRect(left, top, width, height);

		gameData.AircraftData[aircraftData.Type] = aircraftData;
	}

	for (const auto& item : j["pickup"])
	{
		PickupData pickupData{};
		pickupData.Type = Utility::stringToPickupType(item["type"]);
		pickupData.Value = item["value"];
		SetPickupAction(pickupData);
		gameData.PickupData[pickupData.Type] = pickupData;
	}

	for (const auto& item : j["projectile"])
	{
		ProjectileData projectileData{};
		projectileData.Type = Utility::stringToProjectileType(item["type"]);
		projectileData.Value = item["value"];
		gameData.ProjectileData[projectileData.Type] = projectileData;
	}

	return gameData;
}
