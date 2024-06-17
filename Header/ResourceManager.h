//
// Created by Johnnie Otis on 6/16/24.
//

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "SoundFxId.h"
#include "TextureId.h"
#include "Cache.h"
#include "FontId.h"

class ResourceManager
{
 public:
	static sf::Font* loadResource(FontId fontId);
	static sf::SoundBuffer* loadResource(SoundFxId soundFxId);
	static sf::Texture* loadResource(TextureId textureId, sf::Rect<int> textureRect);
	static void clearFontCache() { m_fontCache.clear(); }
	static void clearSoundBufferCache() { m_soundBufferCache.clear(); }
	static void clearTextureCache() { m_textureCache.clear(); }
 private:
	static std::string getTexturePath(TextureId textureId);
	static std::string getSoundPath(SoundFxId soundFxId);
	static std::string getFontPath(FontId fontId);

	static Cache<sf::Texture> m_textureCache;
	static Cache<sf::SoundBuffer> m_soundBufferCache;
	static Cache<sf::Font> m_fontCache;
};

#endif //RESOURCEMANAGER_H_
