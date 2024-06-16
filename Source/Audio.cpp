//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/Audio.h"
#include "../Header/Debug.h"
#include <SFML/Audio.hpp>


sf::Sound Audio::m_sound;
sf::Music Audio::m_music;
sf::SoundBuffer* Audio::m_buffer;

void Audio::playSound(SoundFxId soundEffectType, float volume)
{
	m_buffer = ResourceCache::getSoundBuffer(soundEffectType);
	if (!m_buffer)
		return;

	m_sound.setBuffer(*m_buffer);
	m_sound.setVolume(volume);
	m_sound.play();
}

void Audio::playMusic(MusicId musicType, float volume)
{
	std::string pathToFile;
	switch (musicType)
	{
	case MusicId::UNSquadronLevel1:
		pathToFile = "../Assets/Music/UN Squadron Level 1.mp3";
		break;
	case MusicId::UNSquadronMenu:
		pathToFile = "../Assets/Music/UN Squadron Menu.mp3";
		break;
	default:
		Debug::logError(std::logic_error("Music Id is unknown!"));
		return;
	}

	if (!m_music.openFromFile(pathToFile))
		return;

	m_music.setLoop(true);
	m_music.setVolume(volume);
	m_music.play();
}
