//
// Created by Johnnie on 2/11/2025.
//

#include "../Headers/AudioNode.h"

AudioNode::AudioNode(Audio& player) : m_audioPlayer(player)
{

}

void AudioNode::playSound(SoundFxId sound, sf::Vector2f position, float volume)
{

}

unsigned int AudioNode::getCategory() const
{
	return WorldNode::getNodeType() | static_cast<unsigned int>(NodeType::Sound);
}

sf::FloatRect AudioNode::getBoundingRect() const
{
	return WorldNode::getBoundingRect();
}
void AudioNode::render(sf::RenderTarget& renderTarget, sf::RenderStates states) const
{

}
void AudioNode::loadResources()
{

}
void AudioNode::update(sf::Time deltaTime, CommandQueue& commands)
{

}
void AudioNode::playMusic(MusicId musicType, float volume)
{

}
