// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/Audio.h"
#include "../Headers/Debug.h"
#include <SFML/Audio.hpp>
#include "../Headers/ResourceManager.h"

std::list<PooledSound> Audio::m_sounds;
sf::Music Audio::m_music;

#define POOL_RESIZE_LIMIT 10

void Audio::playSound(SoundFxId soundFxId, float volume)
{
	sf::SoundBuffer& buffer = ResourceManager::loadResource(soundFxId);
	PooledSound* availableSound = nullptr;

	//Set finished sounds to available
	for (auto& pooledSound : m_sounds)
	{
		if(!pooledSound.isAvailable && pooledSound.sound.getStatus() == sf::Sound::Status::Stopped)
		{
			pooledSound.isAvailable = true;
		}
	}

	//find an available sound
	for (auto& pooledSound : m_sounds )
	{
		if(pooledSound.isAvailable)
		{
			availableSound = &pooledSound;
			break;
		}
	}

	//if no sounds are available, add a new sound
	if(!availableSound)
	{
		if(m_sounds.size() > POOL_RESIZE_LIMIT)
		{
			Debug::logWarning("Audio pool limit reached. Cannot play sound!");
			return;
		}
		m_sounds.push_back(PooledSound());
		availableSound = &m_sounds.back();
	}

	availableSound->isAvailable = false;
	availableSound->sound.setBuffer(buffer);
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
		Debug::logError("Music Id is unknown!");
		return nullptr;
	}
}
