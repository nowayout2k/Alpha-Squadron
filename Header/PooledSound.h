//
// Created by Johnnie Otis on 6/16/24.
//

#ifndef POOLEDSOUND_H_
#define POOLEDSOUND_H_

#include <SFML/Audio/Sound.hpp>

struct PooledSound
{
	sf::Sound sound;
	bool isAvailable = false;
};

#endif //POOLEDSOUND_H_
