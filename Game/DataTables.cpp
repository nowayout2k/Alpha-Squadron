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
#include "Direction.h"

std::vector<AircraftData> LoadAircraftData(const std::string& filename)
{
	std::vector<AircraftData> data(static_cast<int>(AircraftType::Count));

	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Could not open JSON file: " + filename);
	}

	nlohmann::json j;
	file >> j;

	for (const auto& item : j["aircraft"])
	{
		AircraftData aircraft;
		aircraft.type = Utility::stringToAircraftType(item["type"]);
		if(aircraft.type == AircraftType::Count)
		{
			Debug::logError("Index is greater than length of array! Could not parse " + filename);
			return data;
		}

		aircraft.health = item["health"];
		aircraft.speed = item["maxSpeed"];
		aircraft.textureId = Utility::stringToTextureID(item["textureId"]);
		for (auto direction : item["directions"])
		{
			aircraft.directions.push_back(Direction( direction["angle"], direction["distance"]));
		}

		auto left = item["textureLoadArea"]["left"];
		auto top = item["textureLoadArea"]["top"];
		auto width = item["textureLoadArea"]["width"];
		auto height = item["textureLoadArea"]["height"];

		aircraft.textureLoadArea = sf::IntRect(left, top, width, height);

		auto i = static_cast<int>(aircraft.type);
		Debug::log("Added Data Aircraft Type: " + Utility::aircraftTypeToString(aircraft.type) + " at index: " + std::to_string(i));

		data[i] = aircraft;
	}

	return data;
}