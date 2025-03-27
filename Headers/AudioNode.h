// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef ALPHA_SQUADRON_HEADERS_AUDIONODE_H_
#define ALPHA_SQUADRON_HEADERS_AUDIONODE_H_

// Local includes using quotes.
#include "SoundFxId.h"
#include "Audio.h"
#include "WorldNode.h"

// SFML include.
#include <SFML/System/Vector2.hpp>

/**
 * File: AudioNode.h
 * Purpose: Declares the AudioNode class which acts as an interface between the audio system and the scene graph.
 *
 * The AudioNode class inherits from WorldNode and provides functions to play sound effects and music.
 */
class AudioNode : public WorldNode
{
 public:
	/**
	 * Constructs an AudioNode.
	 * @param player A reference to an Audio object for playing sound effects and music.
	 */
	explicit AudioNode(Audio& player) : m_audioPlayer(player) {}

	/**
	 * Plays a sound effect at the specified position with the given volume.
	 * @param sound The sound effect identifier.
	 * @param position The position at which to play the sound.
	 * @param volume The volume of the sound (default is 100).
	 */
	void playSound(SoundFxId sound, sf::Vector2f position, float volume) { m_audioPlayer.playSound(sound, position, volume); }

	/**
	 * Plays music of the specified type with the given volume.
	 * @param musicType The music type identifier.
	 * @param volume The volume of the music (default is 100).
	 */
	void playMusic(MusicId musicType, float volume = 100) { m_audioPlayer.playMusic(musicType, volume); }

	/**
	 * Retrieves the node type of this AudioNode.
	 * @return The node type combined with the Sound node flag.
	 */
	unsigned int getNodeType() const override { return WorldNode::getNodeType() | static_cast<unsigned int>(NodeType::Sound); }

	/**
	 * Retrieves the bounding rectangle of the node.
	 * @return A FloatRect representing the bounding rectangle.
	 */
	sf::FloatRect getBoundingRect() const override { return WorldNode::getBoundingRect(); }

 protected:
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override {}
	void loadResources() override {}
	void update(sf::Time deltaTime, CommandQueue& commands) override {}

 private:
	Audio& m_audioPlayer; // Reference to the audio player.
};

#endif // ALPHA_SQUADRON_HEADERS_AUDIONODE_H_
