// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef POOLEDSOUND_H_
#define POOLEDSOUND_H_

#include <SFML/Audio/Sound.hpp>

struct PooledSound
{
	sf::Sound Sound;
	bool IsAvailable = false;
};

#endif //POOLEDSOUND_H_
