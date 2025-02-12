//
// Created by Johnnie on 2/11/2025.
//

#ifndef ALPHA_SQUADRON_HEADERS_AUDIONODE_H_
#define ALPHA_SQUADRON_HEADERS_AUDIONODE_H_

#include <SFML/System/Vector2.hpp>
#include "SoundFxId.h"
#include "Audio.h"
#include "WorldNode.h"

class AudioNode : public WorldNode
{
 public:
	explicit AudioNode(Audio& player);
	void playSound(SoundFxId sound, sf::Vector2f position, float volume);
	void playMusic(MusicId musicType, float volume = 100);
	virtual unsigned int getCategory() const;
	sf::FloatRect getBoundingRect() const override;
 protected:
	void render(sf::RenderTarget& renderTarget, sf::RenderStates states) const override;
	void loadResources() override;
	void update(sf::Time deltaTime, CommandQueue& commands) override;
 private:
	Audio& m_audioPlayer;
};

#endif //ALPHA_SQUADRON_HEADERS_AUDIONODE_H_
