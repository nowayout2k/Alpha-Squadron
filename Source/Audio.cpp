//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/Audio.h"
#include "../Header/Debug.h"
#include <SFML/Audio.hpp>
#include "../Header/ResourceManager.h"

std::vector<sf::Sound> Audio::m_sounds;
sf::Music Audio::m_music;

#define POOL_MAX_SIZE 10

void Audio::playSound(SoundFxId soundFxId, float volume)
{
	sf::SoundBuffer* buffer = ResourceManager::loadResource(soundFxId);
	if (!buffer)
		return;

	m_sounds.push_back(sf::Sound());
	sf::Sound& sound = m_sounds.back();
	sound.setBuffer(*buffer);
	sound.setVolume(volume);
	sound.play();

	if(m_sounds.size() > POOL_MAX_SIZE)
	{
		for (auto itr = m_sounds.begin(); itr != m_sounds.end();)
		{
			if(itr->getStatus() == sf::Sound::Status::Stopped)
				itr = m_sounds.erase(itr);
			else
				++itr;
		}
	}
}


void Audio::playMusic(MusicId musicId, float volume)
{
	std::string pathToFile = getMusicPath(musicId);
	if (!m_music.openFromFile(pathToFile))
		return;

	m_music.setLoop(true);
	m_music.setVolume(volume);
	m_music.play();
}

void Audio::stopMusic()
{
	m_music.stop();
}

std::string Audio::getMusicPath(MusicId musicId)
{
	switch (musicId)
	{
	case MusicId::UNSquadronLevel1:
		return "../Assets/Music/UN Squadron Level 1.mp3";
	case MusicId::UNSquadronMenu:
		return "../Assets/Music/UN Squadron Menu.mp3";
	default:
		Debug::logError(std::logic_error("Music Id is unknown!"));
		return nullptr;
	}
}
