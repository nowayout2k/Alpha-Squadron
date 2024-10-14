//
// Created by Johnnie on 5/27/2024.
//

#ifndef UTILITY_H_
#define UTILITY_H_
#include <SFML/System/Clock.hpp>
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
		object.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}
private:
    static sf::Clock m_clock;
};
#endif //UTILITY_H_
