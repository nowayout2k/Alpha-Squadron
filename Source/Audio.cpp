// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/Audio.h"
#include "../Headers/Debug.h"
#include <SFML/Audio.hpp>
#include "../Headers/ResourceManager.h"

std::list<PooledSound> Audio::m_sounds;
sf::Music Audio::m_music;

#define POOL_RESIZE_LIMIT 40

void Audio::playSound(SoundFxId soundFxId, float volume)
{
	sf::SoundBuffer& buffer = ResourceManager::loadResource(soundFxId);
	PooledSound* availableSound = nullptr;

	for (auto& pooledSound : m_sounds)
	{
		if(!pooledSound.IsAvailable && pooledSound.Sound.getStatus() == sf::Sound::Status::Stopped)
		{
			pooledSound.IsAvailable = true;
		}
	}

	for (auto& pooledSound : m_sounds )
	{
		if(pooledSound.IsAvailable)
		{
			availableSound = &pooledSound;
			break;
		}
	}

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

	availableSound->IsAvailable = false;
	availableSound->Sound.setBuffer(buffer);
	availableSound->Sound.setVolume(volume);
	availableSound->Sound.play();
}

void Audio::playMusic(MusicId musicId, float volume)
{
	m_music.stop();
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
	case MusicId::GameMusic:
		return "../Assets/Music/game_music.wav";
	case MusicId::MenuMusic:
		return "../Assets/Music/menu_music.wav";
	default:
		Debug::logError("Music Id is unknown!");
		return nullptr;
	}
}
void Audio::stopAllSounds()
{
	m_music.stop();
	for (auto& pooledSound : m_sounds )
	{
		if(pooledSound.Sound.getStatus() == sf::Sound::Status::Playing)
		{
			pooledSound.Sound.stop();
		}
	}

}
