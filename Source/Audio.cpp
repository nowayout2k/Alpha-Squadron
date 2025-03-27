// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/Audio.h"
#include "../Headers/Debug.h"
#include "../Headers/ResourceManager.h"

namespace Engine
{

#define POOL_RESIZE_LIMIT 40

	PooledSound* Audio::getSoundFromPool()
	{
		PooledSound* availableSound = nullptr;

		for (auto& pooledSound : m_sounds)
		{
			if (!pooledSound.IsAvailable && pooledSound.Sound.getStatus() == sf::Sound::Status::Stopped)
			{
				pooledSound.IsAvailable = true;
			}
		}

		for (auto& pooledSound : m_sounds)
		{
			if (pooledSound.IsAvailable)
			{
				availableSound = &pooledSound;
				break;
			}
		}

		if (!availableSound)
		{
			if (m_sounds.size() > POOL_RESIZE_LIMIT)
			{
				Engine::Debug::logWarning("Audio pool limit reached. Cannot play sound!");
				return nullptr;
			}
			m_sounds.emplace_back();
			availableSound = &m_sounds.back();
		}

		return availableSound;
	}

	void Audio::playSound(AlphaSquadron::SoundFxId soundFxId, float volume)
	{
		playSound(soundFxId, getListenerPosition(), volume);
	}

	void Audio::playSound(AlphaSquadron::SoundFxId soundFxId, sf::Vector2f position, float volume)
	{
		sf::SoundBuffer& buffer = AlphaSquadron::ResourceManager::loadResource(soundFxId);
		PooledSound* availableSound = getSoundFromPool();
		if (!availableSound)
			return;

		availableSound->IsAvailable = false;
		availableSound->Sound.setBuffer(buffer);
		availableSound->Sound.setPosition(position.x, -position.y, 0.f);
		availableSound->Sound.setAttenuation(Attenuation);
		availableSound->Sound.setMinDistance(MinDistance3D);
		availableSound->Sound.setVolume(volume);
		availableSound->Sound.play();
	}

	void Audio::playMusic(AlphaSquadron::MusicId musicId, float volume)
	{
		return;
		try
		{
			m_music.stop();
			std::string pathToFile = getMusicPath(musicId);
			if (!m_music.openFromFile(pathToFile))
				return;

			m_music.setLoop(true);
			m_music.setVolume(volume);
			m_music.play();
		}
		catch (std::exception& e)
		{
			Engine::Debug::logWarning(e.what());
		}
	}

	void Audio::stopMusic()
	{
		try
		{
			m_music.stop();
		}
		catch (std::exception& e)
		{
			Engine::Debug::logWarning(e.what());
		}
	}

	std::string Audio::getMusicPath(AlphaSquadron::MusicId musicId)
	{
		switch (musicId)
		{
		case AlphaSquadron::MusicId::GameMusic:
			return "../Assets/Music/game_music.wav";
		case AlphaSquadron::MusicId::MenuMusic:
			return "../Assets/Music/menu_music.wav";
		default:
			Engine::Debug::logError("Music Id is unknown!");
			return "";
		}
	}

	void Audio::stopAllSounds()
	{
		try
		{
			m_music.stop();
			for (auto& pooledSound : m_sounds)
			{
				if (pooledSound.Sound.getStatus() == sf::Sound::Status::Playing)
				{
					pooledSound.Sound.stop();
				}
			}
		}
		catch (std::exception& e)
		{
			Engine::Debug::logWarning(e.what());
		}
	}
}