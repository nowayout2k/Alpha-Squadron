// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef AUDIO_H_
#define AUDIO_H_

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "SoundFxId.h"
#include "MusicId.h"
#include "PooledSound.h"
#include <list>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio.hpp>

namespace
{
	const float ListenerZ = 300.f;
	const float Attenuation = 8.f;
	const float MinDistance2D = 200.f;
	const float MinDistance3D = std::sqrt(MinDistance2D*MinDistance2D + ListenerZ*ListenerZ);
}

class Audio
{
 public:
	void playSound(SoundFxId soundFxId, sf::Vector2f position, float volume = 100);
	void playSound(SoundFxId soundFxId, float volume = 100);
	void playMusic(MusicId musicType, float volume = 100);
	void pauseMusic(bool isPaused) { if(isPaused) m_music.pause(); else m_music.play(); }
	void stopMusic();
	void stopAllSounds();
	std::string getMusicPath(MusicId musicId);
	static void setListenerPosition(sf::Vector2f position) {sf::Listener::setPosition(position.x, -position.y, ListenerZ);}
 private:
	static sf::Vector2f getListenerPosition() { return { sf::Listener::getPosition().x, sf::Listener::getPosition().y}; }
	PooledSound* getSoundFromPool();
	std::list<PooledSound> m_sounds;
	sf::Music m_music;
};


#endif //AUDIO_H_
