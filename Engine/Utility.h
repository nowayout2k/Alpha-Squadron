//
// Created by Johnnie on 5/27/2024.
//

#ifndef UTILITY_H_
#define UTILITY_H_
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "../Game/AircraftType.h"
#include "../Game/TextureId.h"
#include "Entity.h"
#include "Debug.h"
#include "Direction.h"
#include "../Game/PickupType.h"
#include "../Game/ProjectileType.h"

#ifndef M_PI
#define M_PI 3.14159265359
#endif

class Utility
{
public:
#pragma region Time Functions
	static void beginStopwatch(std::string message)
	{
		m_clock.restart();
		sf::Time elapsed = m_clock.getElapsedTime();
	}

	static void endStopwatch(std::string message)
	{
		sf::Time elapsed = m_clock.getElapsedTime();
	}
#pragma endregion // Time Functions

#pragma region Math Functions
	template <typename T>
	static void centerOrigin(T& object)
	{
		static_assert(std::is_base_of<sf::Drawable, T>::value, "Object must be drawable");
		sf::FloatRect bounds = object.getLocalBounds();
		object.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}

	static float magnitude(float x, float y)
	{
		return std::sqrt(x * x + y * y);
	}

	static float magnitude(sf::Vector2f v)
	{
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

	static sf::Vector2f unitVector(sf::Vector2f v)
	{
		float mag = magnitude(v);
		if (mag == 0)
			return sf::Vector2f(0, 0);
		return v/mag;
	}

	static float getDistance(const sf::Vector2f& a, const sf::Vector2f& b)
	{
		return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
	}

	static float getDistance(const Entity& a, const Entity& b)
	{
		return std::sqrt(std::pow(b.getPosition().x - a.getPosition().x, 2) + std::pow(b.getPosition().y - a.getPosition().y, 2));
	}

	static float dotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
	{
		return vec1.x * vec2.x + vec1.y * vec2.y;
	}

	static float lerp(float a, float b, float t)
	{
		t = std::clamp(t, 0.0f, 1.0f);
		return a + (b - a) * t;
	}

	static constexpr float toRadian(float degree)
	{
		return degree * (M_PI / 180.f);
	}

	static constexpr float toDegree(float angle)
	{
		return angle * (180.f / M_PI);
	}
#pragma endregion // Math Functions

#pragma region StringTo Functions

	static std::string toLower(const std::string& str) {
		std::string result = str;
		std::transform(result.begin(), result.end(), result.begin(),
			[](unsigned char c) { return std::tolower(c); });
		return result;
	}

	static Direction stringToDirection(const std::string& s)
	{
		auto lowerStr = Utility::toLower(s);
		if(lowerStr == "north")
		{
			return Direction::North;
		}
		else if(lowerStr == "south")
		{
			return Direction::South;
		}
		else if(lowerStr == "east")
		{
			return Direction::East;
		}
		else if(lowerStr == "west")
		{
			return Direction::West;
		}
		else
		{
			Debug::logWarning("Could not convert string " + s + " to a direction.");
			return Direction::DirectionCount;
		}
	}

	static TextureId stringToTextureId(const std::string& s)
	{
		auto type = Utility::toLower(s);

		if(type == "smoggy_sky")
		{
			return TextureId::SmoggySky;
		}
		else if(type == "black")
		{
			return TextureId::Black;
		}
		else if(type == "decayed_buildings_1")
		{
			return TextureId::DecayedBuildings1;
		}
		else if(type == "decayed_buildings_2")
		{
			return TextureId::DecayedBuildings2;
		}
		else if(type == "decayed_buildings_3")
		{
			return TextureId::DecayedBuildings3;
		}
		else if(type == "aircraft_sprite_sheet")
		{
			return TextureId::AircraftSpriteSheet;
		}
		else if(type == "enemies_sprite_sheet")
		{
			return TextureId::EnemiesSpriteSheet;
		}
		else if(type == "coin")
		{
			return TextureId::Coin;
		}
		else if(type == "blue_button_idle")
		{
			return TextureId::BlueButtonIdle;
		}
		else if(type == "blue_button_clicked")
		{
			return TextureId::BlueButtonClicked;
		}
		else if(type == "magenta_button_idle")
		{
			return TextureId::MagentaButtonIdle;
		}
		else if(type == "magenta_button_clicked")
		{
			return TextureId::MagentaButtonClicked;
		}
		else
		{
			return TextureId::TextureIdCount;
		}


	}

	static AircraftType stringToAircraftType(const std::string& s)
	{
		auto type = Utility::toLower(s);

		if(type == "tomcat")
		{
			return AircraftType::Tomcat;
		}
		else if(type == "chopper")
		{
			return AircraftType::Chopper;
		}
		else
		{
			return AircraftType::AircraftTypeCount;
		}
	}

	static PickupType stringToPickupType(const std::string& s)
	{
		auto type = Utility::toLower(s);
		if(type == "missile_refill")
		{
			return PickupType::MissileRefill;
		}
		else if(type == "health_refill")
		{
			return PickupType::HealthRefill;
		}
		else if(type == "fire_spread")
		{
			return PickupType::FireSpread;
		}
		else
		{
			return PickupType::PickupCount;
		}
	}

	static ProjectileType stringToProjectileType(const std::string& s)
	{
		auto type = Utility::toLower(s);
		if(type == "bullet")
		{
			return ProjectileType::Bullet;
		}
		else if(type == "missile")
		{
			return ProjectileType::Missile;
		}
		else
		{
			return ProjectileType::TypeCount;
		}
	}

#pragma endregion // StringTo Functions

#pragma region TypeTo Functions
	static std::string pickupTypeToString(PickupType type)
	{
		switch(type)
		{
		case PickupType::FireRate:
			return "fire_rate";
		case PickupType::FireSpread:
			return "fire_spread";
		case PickupType::HealthRefill:
			return "health_refill";
		case PickupType::MissileRefill:
			return "missile_refill";
		default:
			return "none";
		}
	}

	static std::string projectileTypeToString(ProjectileType type)
	{
		switch(type)
		{
		case ProjectileType::Bullet:
			return "bullet";
		case ProjectileType::Missile:
			return "missile";
		default:
			return "none";
		}
	}

	static std::string aircraftTypeToString(AircraftType type)
	{
		switch(type)
		{
		case AircraftType::Chopper:
			return "chopper";
		case AircraftType::Tomcat:
			return "tomcat";
		case AircraftType::AircraftTypeCount:
			return "count";
		default:
			return "none";
		}
	}

	static std::string nodeTypeToString(NodeType type)
	{
		switch(type)
		{
		case NodeType::None:
			return "none";
		case NodeType::WorldNode:
			return "worldNode";
		case NodeType::Entity:
			return "entity";
		case NodeType::Sprite:
			return "sprite";
		case NodeType::Text:
			return "text";
		case NodeType::Aircraft:
			return "aircraft";
		case NodeType::Player:
			return "player";
		case NodeType::Ally:
			return "ally";
		case NodeType::Enemy:
			return "enemy";
		case NodeType::Projectile:
			return "projectile";
		default:
			return "none";
		}
	}
#pragma endregion // TypeTo Functions

#pragma region Input Functions
	static std::string keyToString(sf::Keyboard::Key key)
	{
		switch (key)
		{
			case sf::Keyboard::A: return "A";
			case sf::Keyboard::B: return "B";
			case sf::Keyboard::C: return "C";
			case sf::Keyboard::D: return "D";
			case sf::Keyboard::E: return "E";
			case sf::Keyboard::F: return "F";
			case sf::Keyboard::G: return "G";
			case sf::Keyboard::H: return "H";
			case sf::Keyboard::I: return "I";
			case sf::Keyboard::J: return "J";
			case sf::Keyboard::K: return "K";
			case sf::Keyboard::L: return "L";
			case sf::Keyboard::M: return "M";
			case sf::Keyboard::N: return "N";
			case sf::Keyboard::O: return "O";
			case sf::Keyboard::P: return "P";
			case sf::Keyboard::Q: return "Q";
			case sf::Keyboard::R: return "R";
			case sf::Keyboard::S: return "S";
			case sf::Keyboard::T: return "T";
			case sf::Keyboard::U: return "U";
			case sf::Keyboard::V: return "V";
			case sf::Keyboard::W: return "W";
			case sf::Keyboard::X: return "X";
			case sf::Keyboard::Y: return "Y";
			case sf::Keyboard::Z: return "Z";
			case sf::Keyboard::Num0: return "Num0";
			case sf::Keyboard::Num1: return "Num1";
			case sf::Keyboard::Num2: return "Num2";
			case sf::Keyboard::Num3: return "Num3";
			case sf::Keyboard::Num4: return "Num4";
			case sf::Keyboard::Num5: return "Num5";
			case sf::Keyboard::Num6: return "Num6";
			case sf::Keyboard::Num7: return "Num7";
			case sf::Keyboard::Num8: return "Num8";
			case sf::Keyboard::Num9: return "Num9";
			case sf::Keyboard::Escape: return "Escape";
			case sf::Keyboard::LControl: return "LControl";
			case sf::Keyboard::LShift: return "LShift";
			case sf::Keyboard::LAlt: return "LAlt";
			case sf::Keyboard::LSystem: return "LSystem";
			case sf::Keyboard::RControl: return "RControl";
			case sf::Keyboard::RShift: return "RShift";
			case sf::Keyboard::RAlt: return "RAlt";
			case sf::Keyboard::RSystem: return "RSystem";
			case sf::Keyboard::Menu: return "Menu";
			case sf::Keyboard::LBracket: return "LBracket";
			case sf::Keyboard::RBracket: return "RBracket";
			case sf::Keyboard::Semicolon: return "Semicolon";
			case sf::Keyboard::Comma: return "Comma";
			case sf::Keyboard::Period: return "Period";
			case sf::Keyboard::Quote: return "Quote";
			case sf::Keyboard::Slash: return "Slash";
			case sf::Keyboard::Backslash: return "Backslash";
			case sf::Keyboard::Tilde: return "Tilde";
			case sf::Keyboard::Equal: return "Equal";
			case sf::Keyboard::Hyphen: return "Hyphen";
			case sf::Keyboard::Space: return "Space";
			case sf::Keyboard::Enter: return "Enter";
			case sf::Keyboard::Backspace: return "Backspace";
			case sf::Keyboard::Tab: return "Tab";
			case sf::Keyboard::PageUp: return "PageUp";
			case sf::Keyboard::PageDown: return "PageDown";
			case sf::Keyboard::End: return "End";
			case sf::Keyboard::Home: return "Home";
			case sf::Keyboard::Insert: return "Insert";
			case sf::Keyboard::Delete: return "Delete";
			case sf::Keyboard::Add: return "Add";
			case sf::Keyboard::Subtract: return "Subtract";
			case sf::Keyboard::Multiply: return "Multiply";
			case sf::Keyboard::Divide: return "Divide";
			case sf::Keyboard::Left: return "Left";
			case sf::Keyboard::Right: return "Right";
			case sf::Keyboard::Up: return "Up";
			case sf::Keyboard::Down: return "Down";
			case sf::Keyboard::Numpad0: return "Numpad0";
			case sf::Keyboard::Numpad1: return "Numpad1";
			case sf::Keyboard::Numpad2: return "Numpad2";
			case sf::Keyboard::Numpad3: return "Numpad3";
			case sf::Keyboard::Numpad4: return "Numpad4";
			case sf::Keyboard::Numpad5: return "Numpad5";
			case sf::Keyboard::Numpad6: return "Numpad6";
			case sf::Keyboard::Numpad7: return "Numpad7";
			case sf::Keyboard::Numpad8: return "Numpad8";
			case sf::Keyboard::Numpad9: return "Numpad9";
			case sf::Keyboard::F1: return "F1";
			case sf::Keyboard::F2: return "F2";
			case sf::Keyboard::F3: return "F3";
			case sf::Keyboard::F4: return "F4";
			case sf::Keyboard::F5: return "F5";
			case sf::Keyboard::F6: return "F6";
			case sf::Keyboard::F7: return "F7";
			case sf::Keyboard::F8: return "F8";
			case sf::Keyboard::F9: return "F9";
			case sf::Keyboard::F10: return "F10";
			case sf::Keyboard::F11: return "F11";
			case sf::Keyboard::F12: return "F12";
			case sf::Keyboard::Pause: return "Pause";
			default: return "Unknown";
		}
	}
#pragma endregion // Input Functions

 private:
    static sf::Clock m_clock;
};
#endif //UTILITY_H_
