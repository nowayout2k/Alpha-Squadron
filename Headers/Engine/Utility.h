// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file Utility.h
 * @brief Provides a collection of miscellaneous utility functions.
 *
 * The Utility class contains functions for time measurement, math operations,
 * string conversions, and input key handling, along with various helper routines.
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "../Game/AircraftType.h"
#include "../Game/TextureId.h"
#include "Debug.h"
#include "../Game/Direction.h"
#include "../Game/PickupType.h"
#include "../Game/ProjectileType.h"
#include "Particle.h"
#include "WorldNode.h"
#include "../Game/ParticleType.h"
#include <random>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>

namespace Engine
{

#ifndef M_PI
#define M_PI 3.14159265359
#endif

/**
 * @class Utility
 * @brief A collection of static utility functions for various operations.
 *
 * Utility provides functions for stopwatch timing, mathematical calculations,
 * string conversions, and input key to string conversions, among others.
 */
	class Utility
	{
	 public:
#pragma region Misc Functions
		/**
		 * @brief Starts the stopwatch for performance measurement.
		 * @param message Reference to a message string (currently unused).
		 *
		 * This function restarts an internal clock used for timing.
		 */
		static void beginStopwatch(std::string& message)
		{
			m_clock.restart();
			sf::Time elapsed = m_clock.getElapsedTime();
		}

		/**
		 * @brief Ends the stopwatch and logs the elapsed time.
		 * @param message The message to associate with the elapsed time.
		 *
		 * This function retrieves the elapsed time from the internal clock.
		 */
		static void endStopwatch(const std::string& message)
		{
			sf::Time elapsed = m_clock.getElapsedTime();
		}

		/**
		 * @brief Converts a hexadecimal color string to an sf::Color.
		 * @param hexString The color string in the format "#RRGGBB" or "#RRGGBBAA".
		 * @return An sf::Color corresponding to the hex value.
		 *
		 * Throws std::invalid_argument if the hex string format is invalid.
		 */
		static sf::Color hexToColor(const std::string& hexString)
		{
			if (hexString[0] != '#' || (hexString.length() != 9 && hexString.length() != 7))
			{
				throw std::invalid_argument("Invalid hex color format. Use #RRGGBB or #RRGGBBAA.");
			}

			std::string hexValue = hexString.substr(1);

			unsigned int hexNumber;
			std::stringstream ss;
			ss << std::hex << hexValue;
			ss >> hexNumber;

			if (hexString.length() == 7)
			{
				hexNumber = (hexNumber << 8) | 0xFF;
			}

			sf::Uint8 red = (hexNumber >> 24) & 0xFF;
			sf::Uint8 green = (hexNumber >> 16) & 0xFF;
			sf::Uint8 blue = (hexNumber >> 8) & 0xFF;
			sf::Uint8 alpha = hexNumber & 0xFF;

			return { red, green, blue, alpha };
		}
#pragma endregion // Misc Functions

#pragma region Math Functions
		/**
		 * @brief Centers the origin of a transformable object.
		 * @tparam T The type of the object, which must inherit from sf::Transformable.
		 * @param object The object whose origin is to be centered.
		 */
		template<typename T>
		static void centerOrigin(T& object)
		{
			static_assert(std::is_base_of<sf::Transformable, T>::value, "Object must be Transformable");
			sf::FloatRect bounds = object.getLocalBounds();
			object.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
		}

		/**
		 * @brief Calculates the scale factors to achieve a desired size based on view percentages.
		 * @param viewSize The size of the view.
		 * @param textureSize The size of the texture.
		 * @param scalePercentageOfView The desired scale as a percentage of the view size.
		 * @param preserveAspectRatio If true, both scale factors will be equal.
		 * @return A vector containing the scale factors (scaleX, scaleY).
		 */
		static sf::Vector2f calculateScaleFromViewPercentage(sf::Vector2f viewSize,
			sf::Vector2f textureSize,
			sf::Vector2f scalePercentageOfView,
			bool preserveAspectRatio)
		{
			auto desiredSize = sf::Vector2f(viewSize.x * scalePercentageOfView.x, viewSize.y * scalePercentageOfView.y);

			float scaleX = desiredSize.x / textureSize.x;
			float scaleY = desiredSize.y / textureSize.y;

			if (preserveAspectRatio)
			{
				scaleX = scaleY = std::max(scaleX, scaleY);
			}

			return { scaleX, scaleY };
		}

		/**
		 * @brief Computes the magnitude (length) of a 2D vector from its components.
		 * @param x The x-component.
		 * @param y The y-component.
		 * @return The magnitude of the vector.
		 */
		static float magnitude(float x, float y)
		{
			return std::sqrt(x * x + y * y);
		}

		/**
		 * @brief Computes the magnitude (length) of a 2D vector.
		 * @param v The vector.
		 * @return The magnitude of the vector.
		 */
		static float magnitude(sf::Vector2f v)
		{
			return std::sqrt(v.x * v.x + v.y * v.y);
		}

		/**
		 * @brief Normalizes a 2D vector.
		 * @param v The vector to normalize.
		 * @return A unit vector in the same direction as v, or a zero vector if v is zero.
		 */
		static sf::Vector2f unitVector(sf::Vector2f v)
		{
			float mag = magnitude(v);
			if (mag == 0)
				return sf::Vector2f(0, 0);
			return v / mag;
		}

		/**
		 * @brief Computes the Euclidean distance between two points.
		 * @param a The first point.
		 * @param b The second point.
		 * @return The distance between a and b.
		 */
		static float getDistance(const sf::Vector2f& a, const sf::Vector2f& b)
		{
			return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
		}

		/**
		 * @brief Computes the distance between two WorldNodes based on their positions.
		 * @param a The first WorldNode.
		 * @param b The second WorldNode.
		 * @return The distance between the positions of a and b.
		 */
		static float getDistance(const WorldNode& a, const WorldNode& b)
		{
			return std::sqrt(std::pow(b.getPosition().x - a.getPosition().x, 2)
				+ std::pow(b.getPosition().y - a.getPosition().y, 2));
		}

		/**
		 * @brief Computes the dot product of two vectors.
		 * @param vec1 The first vector.
		 * @param vec2 The second vector.
		 * @return The dot product of vec1 and vec2.
		 */
		static float dotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
		{
			return vec1.x * vec2.x + vec1.y * vec2.y;
		}

		/**
		 * @brief Performs linear interpolation between two values.
		 * @param a The start value.
		 * @param b The end value.
		 * @param t The interpolation factor (clamped between 0.0 and 1.0).
		 * @return The interpolated value.
		 */
		static float lerp(float a, float b, float t)
		{
			t = std::clamp(t, 0.0f, 1.0f);
			return a + (b - a) * t;
		}

		/**
		 * @brief Converts degrees to radians.
		 * @param degree The angle in degrees.
		 * @return The angle in radians.
		 */
		static constexpr float toRadian(float degree)
		{
			return degree * (M_PI / 180.f);
		}

		/**
		 * @brief Converts radians to degrees.
		 * @param angle The angle in radians.
		 * @return The angle in degrees.
		 */
		static constexpr float toDegree(float angle)
		{
			return angle * (180.f / M_PI);
		}

		/**
		 * @brief Generates a random number between min and max.
		 * @tparam T The numeric type.
		 * @param min The minimum value.
		 * @param max The maximum value.
		 * @return A random number in the range [min, max].
		 */
		template<typename T>
		static T getRandomNumber(T min, T max)
		{
			static std::random_device rd;
			static std::mt19937 mt(rd());
			std::uniform_int_distribution<int> dist(min, max);
			return dist(mt);
		}
#pragma endregion // Math Functions

#pragma region StringTo Functions

		/**
		 * @brief Converts a string to lowercase.
		 * @param str The input string.
		 * @return A new string with all characters in lowercase.
		 */
		static std::string toLower(const std::string& str)
		{
			std::string result = str;
			std::transform(result.begin(), result.end(), result.begin(),
				[](unsigned char c)
				{ return std::tolower(c); });
			return result;
		}

		/**
		 * @brief Converts a string to a Direction enumeration.
		 * @param s The input string.
		 * @return The corresponding Direction, or DirectionCount if unrecognized.
		 */
		static AlphaSquadron::Direction stringToDirection(const std::string& s)
		{
			auto lowerStr = Utility::toLower(s);
			if (lowerStr == "north")
			{
				return AlphaSquadron::Direction::North;
			}
			else if (lowerStr == "south")
			{
				return AlphaSquadron::Direction::South;
			}
			else if (lowerStr == "east")
			{
				return AlphaSquadron::Direction::East;
			}
			else if (lowerStr == "west")
			{
				return AlphaSquadron::Direction::West;
			}
			else
			{
				Engine::Debug::logWarning("Could not convert string " + s + " to a direction.");
				return AlphaSquadron::Direction::DirectionCount;
			}
		}

		/**
		 * @brief Converts a string to a TextureId.
		 * @param s The input string.
		 * @return The corresponding TextureId, or TextureCount if unrecognized.
		 */
		static AlphaSquadron::TextureId stringToTextureId(const std::string& s)
		{
			auto type = Utility::toLower(s);

			if (type == "forest_bg")
			{
				return AlphaSquadron::TextureId::ForestBg;
			}
			else if (type == "sky_bg")
			{
				return AlphaSquadron::TextureId::SkyBg;
			}
			else if (type == "jungle_bg")
			{
				return AlphaSquadron::TextureId::JungleBg;
			}
			else if (type == "metal_bg")
			{
				return AlphaSquadron::TextureId::MetalBg;
			}
			else if (type == "tall_city_bg")
			{
				return AlphaSquadron::TextureId::TallCityBg;
			}
			else if (type == "night_city_bg")
			{
				return AlphaSquadron::TextureId::NightCityBg;
			}
			else if (type == "decayed_city_bg")
			{
				return AlphaSquadron::TextureId::DecayedCityBg;
			}
			else if (type == "game_sprite_sheet")
			{
				return AlphaSquadron::TextureId::GameSpriteSheet;
			}
			else if (type == "ui_sprite_sheet")
			{
				return AlphaSquadron::TextureId::UiSpriteSheet;
			}
			else
			{
				return AlphaSquadron::TextureId::TextureCount;
			}
		}

		/**
		 * @brief Converts a string to an AircraftType.
		 * @param s The input string.
		 * @return The corresponding AircraftType, or AircraftTypeCount if unrecognized.
		 */
		static AlphaSquadron::AircraftType stringToAircraftType(const std::string& s)
		{
			auto type = Utility::toLower(s);

			if (type == "tomcat")
			{
				return AlphaSquadron::AircraftType::Tomcat;
			}
			else if (type == "chopper")
			{
				return AlphaSquadron::AircraftType::Chopper;
			}
			else
			{
				return AlphaSquadron::AircraftType::AircraftTypeCount;
			}
		}

		/**
		 * @brief Converts a string to a PickupType.
		 * @param s The input string.
		 * @return The corresponding PickupType, or PickupCount if unrecognized.
		 */
		static AlphaSquadron::PickupType stringToPickupType(const std::string& s)
		{
			auto type = Utility::toLower(s);
			if (type == "missile_refill")
			{
				return AlphaSquadron::PickupType::MissileRefill;
			}
			else if (type == "health_refill")
			{
				return AlphaSquadron::PickupType::HealthRefill;
			}
			else if (type == "fire_spread")
			{
				return AlphaSquadron::PickupType::FireSpread;
			}
			else if (type == "fire_rate")
			{
				return AlphaSquadron::PickupType::FireRate;
			}
			else
			{
				return AlphaSquadron::PickupType::PickupCount;
			}
		}

		/**
		 * @brief Converts a string to a ProjectileType.
		 * @param s The input string.
		 * @return The corresponding ProjectileType, or TypeCount if unrecognized.
		 */
		static AlphaSquadron::ProjectileType stringToProjectileType(const std::string& s)
		{
			auto type = Utility::toLower(s);
			if (type == "bullet")
			{
				return AlphaSquadron::ProjectileType::Bullet;
			}
			else if (type == "missile")
			{
				return AlphaSquadron::ProjectileType::Missile;
			}
			else
			{
				return AlphaSquadron::ProjectileType::TypeCount;
			}
		}

		/**
		 * @brief Converts a string to a Particle::Type.
		 * @param s The input string.
		 * @return The corresponding Particle::Type, or ParticleTypeCount if unrecognized.
		 */
		static AlphaSquadron::ParticleType stringToParticleType(const std::string& s)
		{
			auto type = Utility::toLower(s);
			if (type == "smoke")
			{
				return AlphaSquadron::ParticleType::Smoke;
			}
			else if (type == "propellant")
			{
				return AlphaSquadron::ParticleType::Propellant;
			}
			else
			{
				return AlphaSquadron::ParticleType::ParticleTypeCount;
			}
		}

#pragma endregion // StringTo Functions

#pragma region TypeTo Functions
		/**
		 * @brief Converts a PickupType to its string representation.
		 * @param type The PickupType.
		 * @return A string representing the PickupType.
		 */
		static std::string pickupTypeToString(AlphaSquadron::PickupType type)
		{
			switch (type)
			{
			case AlphaSquadron::PickupType::FireRate:
				return "fire_rate";
			case AlphaSquadron::PickupType::FireSpread:
				return "fire_spread";
			case AlphaSquadron::PickupType::HealthRefill:
				return "health_refill";
			case AlphaSquadron::PickupType::MissileRefill:
				return "missile_refill";
			default:
				return "none";
			}
		}

		/**
		 * @brief Converts a ProjectileType to its string representation.
		 * @param type The ProjectileType.
		 * @return A string representing the ProjectileType.
		 */
		static std::string projectileTypeToString(AlphaSquadron::ProjectileType type)
		{
			switch (type)
			{
			case AlphaSquadron::ProjectileType::Bullet:
				return "bullet";
			case AlphaSquadron::ProjectileType::Missile:
				return "missile";
			default:
				return "none";
			}
		}

		/**
		 * @brief Converts an AircraftType to its string representation.
		 * @param type The AircraftType.
		 * @return A string representing the AircraftType.
		 */
		static std::string aircraftTypeToString(AlphaSquadron::AircraftType type)
		{
			switch (type)
			{
			case AlphaSquadron::AircraftType::Chopper:
				return "chopper";
			case AlphaSquadron::AircraftType::Tomcat:
				return "tomcat";
			case AlphaSquadron::AircraftType::AircraftTypeCount:
				return "count";
			default:
				return "none";
			}
		}

		/**
		 * @brief Converts a NodeType to its string representation.
		 * @param type The NodeType.
		 * @return A string representing the NodeType.
		 */
		static std::string nodeTypeToString(AlphaSquadron::NodeType type)
		{
			switch (type)
			{
			case AlphaSquadron::NodeType::None:
				return "none";
			case AlphaSquadron::NodeType::WorldNode:
				return "world_node";
			case AlphaSquadron::NodeType::GameSprite:
				return "game_sprite";
			case AlphaSquadron::NodeType::Text:
				return "text";
			case AlphaSquadron::NodeType::Aircraft:
				return "aircraft";
			case AlphaSquadron::NodeType::Player:
				return "player";
			case AlphaSquadron::NodeType::Enemy:
				return "enemy";
			case AlphaSquadron::NodeType::AlliedProjectile:
				return "allied_projectile";
			case AlphaSquadron::NodeType::EnemyProjectile:
				return "enemy_projectile";
			default:
				return "none";
			}
		}
#pragma endregion // TypeTo Functions

#pragma region Input Functions
		/**
		 * @brief Converts an SFML key code to its string representation.
		 * @param key The sf::Keyboard::Key value.
		 * @return A string representing the key.
		 *
		 * This function uses a switch statement to map each key code to its corresponding string.
		 */
		static std::string keyToString(sf::Keyboard::Key key)
		{
			switch (key)
			{
			case sf::Keyboard::A:
				return "A";
			case sf::Keyboard::B:
				return "B";
			case sf::Keyboard::C:
				return "C";
			case sf::Keyboard::D:
				return "D";
			case sf::Keyboard::E:
				return "E";
			case sf::Keyboard::F:
				return "F";
			case sf::Keyboard::G:
				return "G";
			case sf::Keyboard::H:
				return "H";
			case sf::Keyboard::I:
				return "I";
			case sf::Keyboard::J:
				return "J";
			case sf::Keyboard::K:
				return "K";
			case sf::Keyboard::L:
				return "L";
			case sf::Keyboard::M:
				return "M";
			case sf::Keyboard::N:
				return "N";
			case sf::Keyboard::O:
				return "O";
			case sf::Keyboard::P:
				return "P";
			case sf::Keyboard::Q:
				return "Q";
			case sf::Keyboard::R:
				return "R";
			case sf::Keyboard::S:
				return "S";
			case sf::Keyboard::T:
				return "T";
			case sf::Keyboard::U:
				return "U";
			case sf::Keyboard::V:
				return "V";
			case sf::Keyboard::W:
				return "W";
			case sf::Keyboard::X:
				return "X";
			case sf::Keyboard::Y:
				return "Y";
			case sf::Keyboard::Z:
				return "Z";
			case sf::Keyboard::Num0:
				return "Num0";
			case sf::Keyboard::Num1:
				return "Num1";
			case sf::Keyboard::Num2:
				return "Num2";
			case sf::Keyboard::Num3:
				return "Num3";
			case sf::Keyboard::Num4:
				return "Num4";
			case sf::Keyboard::Num5:
				return "Num5";
			case sf::Keyboard::Num6:
				return "Num6";
			case sf::Keyboard::Num7:
				return "Num7";
			case sf::Keyboard::Num8:
				return "Num8";
			case sf::Keyboard::Num9:
				return "Num9";
			case sf::Keyboard::Escape:
				return "Escape";
			case sf::Keyboard::LControl:
				return "LControl";
			case sf::Keyboard::LShift:
				return "LShift";
			case sf::Keyboard::LAlt:
				return "LAlt";
			case sf::Keyboard::LSystem:
				return "LSystem";
			case sf::Keyboard::RControl:
				return "RControl";
			case sf::Keyboard::RShift:
				return "RShift";
			case sf::Keyboard::RAlt:
				return "RAlt";
			case sf::Keyboard::RSystem:
				return "RSystem";
			case sf::Keyboard::Menu:
				return "Menu";
			case sf::Keyboard::LBracket:
				return "LBracket";
			case sf::Keyboard::RBracket:
				return "RBracket";
			case sf::Keyboard::Semicolon:
				return "Semicolon";
			case sf::Keyboard::Comma:
				return "Comma";
			case sf::Keyboard::Period:
				return "Period";
			case sf::Keyboard::Quote:
				return "Quote";
			case sf::Keyboard::Slash:
				return "Slash";
			case sf::Keyboard::Backslash:
				return "Backslash";
			case sf::Keyboard::Tilde:
				return "Tilde";
			case sf::Keyboard::Equal:
				return "Equal";
			case sf::Keyboard::Hyphen:
				return "Hyphen";
			case sf::Keyboard::Space:
				return "Space";
			case sf::Keyboard::Enter:
				return "Enter";
			case sf::Keyboard::Backspace:
				return "Backspace";
			case sf::Keyboard::Tab:
				return "Tab";
			case sf::Keyboard::PageUp:
				return "PageUp";
			case sf::Keyboard::PageDown:
				return "PageDown";
			case sf::Keyboard::End:
				return "End";
			case sf::Keyboard::Home:
				return "Home";
			case sf::Keyboard::Insert:
				return "Insert";
			case sf::Keyboard::Delete:
				return "Delete";
			case sf::Keyboard::Add:
				return "Add";
			case sf::Keyboard::Subtract:
				return "Subtract";
			case sf::Keyboard::Multiply:
				return "Multiply";
			case sf::Keyboard::Divide:
				return "Divide";
			case sf::Keyboard::Left:
				return "Left";
			case sf::Keyboard::Right:
				return "Right";
			case sf::Keyboard::Up:
				return "Up";
			case sf::Keyboard::Down:
				return "Down";
			case sf::Keyboard::Numpad0:
				return "Numpad0";
			case sf::Keyboard::Numpad1:
				return "Numpad1";
			case sf::Keyboard::Numpad2:
				return "Numpad2";
			case sf::Keyboard::Numpad3:
				return "Numpad3";
			case sf::Keyboard::Numpad4:
				return "Numpad4";
			case sf::Keyboard::Numpad5:
				return "Numpad5";
			case sf::Keyboard::Numpad6:
				return "Numpad6";
			case sf::Keyboard::Numpad7:
				return "Numpad7";
			case sf::Keyboard::Numpad8:
				return "Numpad8";
			case sf::Keyboard::Numpad9:
				return "Numpad9";
			case sf::Keyboard::F1:
				return "F1";
			case sf::Keyboard::F2:
				return "F2";
			case sf::Keyboard::F3:
				return "F3";
			case sf::Keyboard::F4:
				return "F4";
			case sf::Keyboard::F5:
				return "F5";
			case sf::Keyboard::F6:
				return "F6";
			case sf::Keyboard::F7:
				return "F7";
			case sf::Keyboard::F8:
				return "F8";
			case sf::Keyboard::F9:
				return "F9";
			case sf::Keyboard::F10:
				return "F10";
			case sf::Keyboard::F11:
				return "F11";
			case sf::Keyboard::F12:
				return "F12";
			case sf::Keyboard::Pause:
				return "Pause";
			default:
				return "Unknown";
			}
		}
#pragma endregion // Input Functions

	 private:
		static sf::Clock m_clock; ///< Static clock used for timing functions.
	};
}
#endif //UTILITY_H_
