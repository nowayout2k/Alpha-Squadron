#include "../Headers/DataTables.h"
#include "../Headers/AircraftType.h"
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"
#include "../Headers/Aircraft.h"

// Sets the action for a pickup based on its type.
void SetPickupAction(PickupData& data)
{
	switch (data.Type)
	{
	case PickupType::FireSpread:
		data.Action = [data](Aircraft& a) { a.changeFireSpread(static_cast<int>(data.Value)); };
		break;
	case PickupType::HealthRefill:
		data.Action = [data](Aircraft& a) { a.changeHealth(data.Value); };
		break;
	case PickupType::MissileRefill:
		data.Action = [data](Aircraft& a) { a.changeMissileCount(static_cast<int>(data.Value)); };
		break;
	case PickupType::FireRate:
		data.Action = [data](Aircraft& a) { a.changeFireRate(static_cast<int>(data.Value)); };
		break;
	default:
		break;
	}
}

GameData LoadData(const std::string& filename)
{
	try
	{
		std::ifstream file(filename);
		if (!file.is_open())
		{
			throw std::runtime_error("Could not open JSON file: " + filename);
		}

		nlohmann::json j;
		file >> j;

		GameData gameData;

		for (const auto& item : j["aircraft"])
		{
			AircraftData aircraftData;
			aircraftData.Type = Utility::stringToAircraftType(item["type"]);
			if (aircraftData.Type == AircraftType::AircraftTypeCount)
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
				aircraftData.AiRoutines.emplace_back(aiRoutine["angle"], aiRoutine["distance"]);
			}

			int sLeft = item["spriteTextureRegion"]["left"];
			int sTop = item["spriteTextureRegion"]["top"];
			int sWidth = item["spriteTextureRegion"]["width"];
			int sHeight = item["spriteTextureRegion"]["height"];
			aircraftData.SpriteTextureRegion = sf::IntRect(sLeft, sTop, sWidth, sHeight);

			int lLeft = item["textureLoadArea"]["left"];
			int lTop = item["textureLoadArea"]["top"];
			int lWidth = item["textureLoadArea"]["width"];
			int lHeight = item["textureLoadArea"]["height"];
			aircraftData.TextureLoadArea = sf::IntRect(lLeft, lTop, lWidth, lHeight);

			gameData.AircraftData[aircraftData.Type] = aircraftData;
		}

		for (const auto& item : j["pickup"])
		{
			PickupData pickupData{};
			pickupData.Type = Utility::stringToPickupType(item["type"]);
			pickupData.Value = item["value"];
			pickupData.TextureId = Utility::stringToTextureId(item["textureId"]);

			int left = item["textureLoadArea"]["left"];
			int top = item["textureLoadArea"]["top"];
			int width = item["textureLoadArea"]["width"];
			int height = item["textureLoadArea"]["height"];
			pickupData.TextureLoadArea = sf::IntRect(left, top, width, height);

			SetPickupAction(pickupData);
			gameData.PickupData[pickupData.Type] = pickupData;
		}

		for (const auto& item : j["projectile"])
		{
			ProjectileData projectileData{};
			projectileData.Type = Utility::stringToProjectileType(item["type"]);
			projectileData.MaxSpeed = item["maxSpeed"];
			projectileData.TextureId = Utility::stringToTextureId(item["textureId"]);

			int left = item["textureLoadArea"]["left"];
			int top = item["textureLoadArea"]["top"];
			int width = item["textureLoadArea"]["width"];
			int height = item["textureLoadArea"]["height"];
			projectileData.TextureLoadArea = sf::IntRect(left, top, width, height);

			gameData.ProjectileData[projectileData.Type] = projectileData;
		}

		for (const auto& item : j["particle"])
		{
			ParticleData particleData{};
			particleData.Type = Utility::stringToParticleType(item["type"]);
			particleData.Color = Utility::hexToColor(item["color"]);
			particleData.Lifetime = sf::seconds(item["lifetime"]);
			gameData.ParticleData[particleData.Type] = particleData;
		}

		return gameData;
	}
	catch (std::exception& e)
	{
		Debug::logError(e.what());
		return {};
	}
}
