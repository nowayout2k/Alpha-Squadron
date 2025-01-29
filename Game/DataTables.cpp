//
// Created by Johnnie Otis on 10/15/24.
//
#include "DataTables.h"
#include "AircraftType.h"
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "../Engine/Debug.h"
#include "../Engine/Utility.h"
#include "AiRoutine.h"

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

		gameData.AircraftData[Utility::aircraftTypeToString(aircraftData.Type)] = aircraftData;
	}

	for (const auto& item : j["pickup"])
	{
		PickupData pickupData{};
		pickupData.Type = Utility::stringToPickupType(item["type"]);
		pickupData.Value = item["value"];
		gameData.PickupData[Utility::pickupTypeToString(pickupData.Type)] = pickupData;
	}

	for (const auto& item : j["projectile"])
	{
		ProjectileData projectileData{};
		projectileData.Type = Utility::stringToProjectileType(item["type"]);
		projectileData.Value = item["value"];
		gameData.ProjectileData[Utility::projectileTypeToString(projectileData.Type)] = projectileData;
	}

	return gameData;
}