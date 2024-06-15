//
// Created by Johnnie Otis on 6/9/24.
//

#ifndef ALPHA_SQUADRON_HEADER_DATACACHE_H_
#define ALPHA_SQUADRON_HEADER_DATACACHE_H_

#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "Font.h"

class DataCache
{
 public:
	static sf::Texture* getTexture(const std::string path, const sf::IntRect textureRect = sf::IntRect());
	static void clearTextureCache() { m_textureCache.clear(); };

	static sf::SoundBuffer* getSoundBuffer(const std::string path);
	static void clearSoundCache() { m_soundCache.clear(); };

	static sf::Font* getFont(const Font font);
	static void clearFontCache() { m_fontCache.clear(); };

 private:
	static std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textureCache;
	static std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> m_soundCache;
	static std::unordered_map<std::string, std::unique_ptr<sf::Font>> m_fontCache;
};

#endif //ALPHA_SQUADRON_HEADER_DATACACHE_H_
