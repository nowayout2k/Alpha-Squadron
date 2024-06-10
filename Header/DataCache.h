//
// Created by Johnnie Otis on 6/9/24.
//

#ifndef ALPHA_SQUADRON_HEADER_DATACACHE_H_
#define ALPHA_SQUADRON_HEADER_DATACACHE_H_

#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class DataCache
{
 public:
	static std::shared_ptr<sf::Texture> getTexture(const std::string path, const sf::IntRect textureRect = sf::IntRect());
	static void clearTextureCache() { m_textureCache.clear(); };
	static void cleanupTextureCache();

	static std::shared_ptr<sf::SoundBuffer> getSoundBuffer(const std::string path);
	static void clearSoundCache() { m_soundCache.clear(); };
	static void cleanupSoundCache();
 private:
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> m_textureCache;
	static std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> m_soundCache;
};

#endif //ALPHA_SQUADRON_HEADER_DATACACHE_H_
