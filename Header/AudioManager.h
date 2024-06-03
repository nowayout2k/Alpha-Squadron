//
// Created by Johnnie Otis on 5/26/24.
//

#ifndef ALPHA_SQUADRON_HEADER_AUDIOMANAGER_H_
#define ALPHA_SQUADRON_HEADER_AUDIOMANAGER_H_

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "SoundEffectType.h"
#include "MusicType.h"

static class AudioManager
{
 public:
	static void playSound(SoundEffectType soundType, float volume = 100);
	static void playMusic(MusicType musicType, float volume = 100);
 private:
	static sf::Sound m_sound;
	static sf::Music m_music;
	static sf::SoundBuffer m_buffer;
};


#endif //ALPHA_SQUADRON_HEADER_AUDIOMANAGER_H_
