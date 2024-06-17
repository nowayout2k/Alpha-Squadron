//
// Created by Johnnie Otis on 5/26/24.
//

#include "../Header/Audio.h"
#include "../Header/Debug.h"
#include <SFML/Audio.hpp>
#include "../Header/ResourceManager.h"

std::list<PooledSound> Audio::m_sounds;
sf::Music Audio::m_music;

#define POOL_MAX_SIZE 10

void Audio::playSound(SoundFxId soundFxId, float volume)
{
	sf::SoundBuffer* buffer = ResourceManager::loadResource(soundFxId);
	if (!buffer)
		return;

	PooledSound* availableSound = nullptr;
	if(m_sounds.size() > POOL_MAX_SIZE)
	{
		for (auto& pooledSound : m_sounds )
		{
			if(pooledSound.sound.getStatus() == sf::Sound::Status::Stopped)
				pooledSound.isAvailable = true;

			if(pooledSound.isAvailable)
				availableSound = &pooledSound;
		}
	}

	if(!availableSound)
	{
		m_sounds.push_back(PooledSound());
		availableSound = &m_sounds.back();
	}

	availableSound->sound.setBuffer(*buffer);
	availableSound->sound.setVolume(volume);
	availableSound->sound.play();
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
