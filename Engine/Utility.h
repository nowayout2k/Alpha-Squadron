//
// Created by Johnnie on 5/27/2024.
//

#ifndef UTILITY_H_
#define UTILITY_H_
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "../Game/AircraftType.h"
#include "../Game/TextureId.h"
#include "Debug.h"

class Utility
{
public:
	static void beginStopwatch(std::string message)
	{
		m_clock.restart();
		sf::Time elapsed = m_clock.getElapsedTime();
	}

	static void endStopwatch(std::string message)
	{
		sf::Time elapsed = m_clock.getElapsedTime();
	}

	static float lerp(float a, float b, float t)
	{
		t = std::clamp(t, 0.0f, 1.0f);
		return a + (b - a) * t;
	}

	template <typename T>
	static void centerOrigin(T& object)
	{
		static_assert(std::is_base_of<sf::Drawable, T>::value, "Object must be drawable");
		sf::FloatRect bounds = object.getLocalBounds();
		object.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}

	static TextureId stringToTextureID(const std::string& str)
	{
		static std::unordered_map<std::string, TextureId> stringToEnumMap = {
			{ "SmoggySky", TextureId::SmoggySky },
			{ "Black", TextureId::Black },
			{ "DecayedBuildings1", TextureId::DecayedBuildings1 },
			{ "DecayedBuildings2", TextureId::DecayedBuildings2 },
			{ "DecayedBuildings3", TextureId::DecayedBuildings3 },
			{ "AircraftSpriteSheet", TextureId::AircraftSpriteSheet },
			{ "EnemiesSpriteSheet", TextureId::EnemiesSpriteSheet },
			{ "Coin", TextureId::Coin },
			{ "BlueButtonIdle", TextureId::BlueButtonIdle },
			{ "BlueButtonClicked", TextureId::BlueButtonClicked },
			{ "MagentaButtonIdle", TextureId::MagentaButtonIdle },
			{ "MagentaButtonClicked", TextureId::MagentaButtonClicked },
		};

		auto it = stringToEnumMap.find(str);
		if (it != stringToEnumMap.end())
		{
			return it->second;
		}
		else
		{
			Debug::logError("Invalid aircraft type: " + str);
			return TextureId::Count;
		}
	}

	static AircraftType stringToAircraftType(const std::string& str)
	{
		static std::unordered_map<std::string, AircraftType> stringToEnumMap = {
			{ "Tomcat", AircraftType::Tomcat },
			{ "Chopper", AircraftType::Chopper }
		};

		auto it = stringToEnumMap.find(str);
		if (it != stringToEnumMap.end())
		{
			return it->second;
		}
		else
		{
			Debug::logError("Invalid aircraft type: " + str);
			return AircraftType::Count;
		}
	}

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

 private:
    static sf::Clock m_clock;
};
#endif //UTILITY_H_
