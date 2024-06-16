//
// Created by Johnnie Otis on 6/9/24.
//

#ifndef ALPHA_SQUADRON_HEADER_RESOURCECACHE_H_
#define ALPHA_SQUADRON_HEADER_RESOURCECACHE_H_

#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "FontId.h"
#include "TextureId.h"
#include "SoundFxId.h"

class ResourceCache
{
 public:
	static void clearTextureCache() { m_textureCache.clear(); };
	static void clearSoundCache() { m_soundCache.clear(); };
	static void clearFontCache() { m_fontCache.clear(); };
	static sf::Texture* getTexture(const TextureId textureType, const sf::IntRect textureRect = sf::IntRect());
	static sf::SoundBuffer* getSoundBuffer(const SoundFxId soundType);
	static sf::Font* getFont(const FontId fontType);
 private:
	static std::string getTexturePath(TextureId textureId);
	static std::string getSoundPath(SoundFxId soundFxId);
	static std::string getFontPath(FontId fontId);

	static std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textureCache;
	static std::unordered_map<SoundFxId, std::unique_ptr<sf::SoundBuffer>> m_soundCache;
	static std::unordered_map<FontId, std::unique_ptr<sf::Font>> m_fontCache;
};

#endif //ALPHA_SQUADRON_HEADER_RESOURCECACHE_H_
