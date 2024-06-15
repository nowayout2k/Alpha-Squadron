//
// Created by Johnnie Otis on 6/9/24.
//

#ifndef ALPHA_SQUADRON_HEADER_DATACACHE_H_
#define ALPHA_SQUADRON_HEADER_DATACACHE_H_

#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "Font.h"
#include "TextureTypes.h"
#include "SoundEffectType.h"

class DataCache
{
 public:
	static sf::Texture* getTexture(const TextureType textureType, const sf::IntRect textureRect = sf::IntRect());
	static void clearTextureCache() { m_textureCache.clear(); };

	static sf::SoundBuffer* getSoundBuffer(const SoundEffectType soundType);
	static void clearSoundCache() { m_soundCache.clear(); };

	static sf::Font* getFont(const FontType fontType);
	static void clearFontCache() { m_fontCache.clear(); };

 private:
	static std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textureCache;
	static std::unordered_map<SoundEffectType, std::unique_ptr<sf::SoundBuffer>> m_soundCache;
	static std::unordered_map<FontType, std::unique_ptr<sf::Font>> m_fontCache;
};

#endif //ALPHA_SQUADRON_HEADER_DATACACHE_H_
