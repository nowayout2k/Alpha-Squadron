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
	m_buffer = DataCache::getSoundBuffer(soundEffectType);
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
	case MusicType::UNSquadronLevel1:
		pathToFile = "../Assets/Music/UN Squadron Level 1.mp3";
		break;
	case MusicType::UNSquadronMenu:
		pathToFile = "../Assets/Music/UN Squadron Menu.mp3";
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
