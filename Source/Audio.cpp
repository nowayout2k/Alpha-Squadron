//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/Audio.h"
#include "../Header/Debug.h"
#include <SFML/Audio.hpp>


sf::Sound Audio::m_sound;
sf::Music Audio::m_music;
sf::SoundBuffer* Audio::m_buffer;

void Audio::playSound(SoundEffectType soundEffectType, float volume)
{
	std::string pathToFile;
	switch (soundEffectType)
	{
	case SoundEffectType::Collect:
		pathToFile = "../Assets/SFX/Collect.wav";
		break;
	case SoundEffectType::Shoot1:
		pathToFile = "../Assets/SFX/shoot1.wav";
		break;
	default:
		Debug::log(Error, "Sound Effect Type is unknown!");
		return;
	}

	m_buffer = DataCache::getSoundBuffer(pathToFile);
	if (!m_buffer)
		return;

	m_sound.setBuffer(*m_buffer);
	m_sound.setVolume(volume);
	m_sound.play();

}
void Audio::playMusic(MusicType musicType, float volume)
{
	std::string pathToFile;
	switch (musicType)
	{
	case MusicType::Level1:
		pathToFile = "../Assets/Music/U.N. Squadron (SNES)_ Mission 1 - Front line base.mp3";
		break;
	default:
		Debug::log(Error, "Music Type is unknown!");
		return;
	}

	if (!m_music.openFromFile(pathToFile))
		return;

	m_music.setLoop(true);
	m_music.setVolume(volume);
	m_music.play();
}
