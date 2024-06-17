//
// Created by Johnnie Otis on 5/26/24.
//

#ifndef AUDIO_H_
#define AUDIO_H_

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "../Header/SoundFxId.h"
#include "../Header/MusicId.h"
#include "PooledSound.h"
#include <list>

class Audio
{
 public:
	static void playSound(SoundFxId soundType, float volume = 100);
	static void playMusic(MusicId musicType, float volume = 100);
	static void stopMusic();
	static std::string getMusicPath(MusicId musicId);
 private:
	static std::list<PooledSound> m_sounds;
	static sf::Music m_music;
};


#endif //AUDIO_H_
