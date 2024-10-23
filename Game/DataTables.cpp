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
		AircraftType type = Utility::stringToAircraftType(item["type"]);
		if(type == AircraftType::Count)
		{
			Debug::logError("Index is greater than length of array! Could not parse " + filename);
			return data;
		}

		aircraft.health = item["health"];
		aircraft.speed = item["speed"];
		aircraft.texture = Utility::stringToTextureID(item["textureId"]);

		auto left = item["textureRect"]["left"];
		auto top = item["textureRect"]["top"];
		auto width = item["textureRect"]["width"];
		auto height = item["textureRect"]["height"];

		aircraft.textureRect = sf::IntRect(left, top, width, height);

		data[static_cast<int>(type)] = aircraft;
	}

	return data;
}