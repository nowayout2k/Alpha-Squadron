// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef AUDIO_H_
#define AUDIO_H_

#include "SoundFxId.h"
#include "MusicId.h"
#include "PooledSound.h"

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <list>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

/**
 * File: Audio.h
 * Purpose: Declares the Audio class for handling game audio including sound effects and music.
 */

namespace
{
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D * MinDistance2D + ListenerZ * ListenerZ);
}

/**
 * Class: Audio
 * Purpose: Handles playing of sound effects and music.
 */
class Audio
{
 public:
	/**
	 * Plays a sound effect at a given position.
	 * @param soundFxId Identifier for the sound effect.
	 * @param position Position in 2D space where the sound should be played.
	 * @param volume Volume of the sound effect (default is 100).
	 */
	void playSound(SoundFxId soundFxId, sf::Vector2f position, float volume = 100);

	/**
	 * Plays a sound effect at the listener's position.
	 * @param soundFxId Identifier for the sound effect.
	 * @param volume Volume of the sound effect (default is 100).
	 */
	void playSound(SoundFxId soundFxId, float volume = 100);

	/**
	 * Plays music of a specified type.
	 * @param musicType Identifier for the music.
	 * @param volume Volume for the music (default is 100).
	 */
	void playMusic(MusicId musicType, float volume = 100);

	/**
	 * Pauses or resumes the music.
	 * @param isPaused True to pause, false to resume.
	 */
	void pauseMusic(bool isPaused) { if (isPaused) m_music.pause(); else m_music.play(); }

	/**
	 * Stops the currently playing music.
	 */
	void stopMusic();

	/**
	 * Stops all currently playing sounds.
	 */
	void stopAllSounds();

	/**
	 * Retrieves the file path for the given music type.
	 * @param musicId Identifier for the music.
	 * @return The file path as a string.
	 */
	std::string getMusicPath(MusicId musicId);

	/**
	 * Sets the listener position in 2D space.
	 * @param position Listener's position.
	 */
	static void setListenerPosition(sf::Vector2f position) { sf::Listener::setPosition(position.x, -position.y, ListenerZ); }

 private:
	/**
	 * Retrieves the listener's position.
	 * @return The listener's position as a vector.
	 */
	static sf::Vector2f getListenerPosition() { return { sf::Listener::getPosition().x, sf::Listener::getPosition().y }; }

	/**
	 * Retrieves an available sound from the sound pool.
	 * @return Pointer to a PooledSound.
	 */
	PooledSound* getSoundFromPool();

	std::list<PooledSound> m_sounds;  // Pool of sound objects.
	sf::Music m_music;                // Music object.
};

#endif // AUDIO_H_
