// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include "SoundFxId.h"
#include "TextureId.h"
#include "Cache.h"
#include "FontId.h"
#include "ShaderId.h"

class ResourceManager
{
 public:
	static sf::Font& loadResource(FontId fontId);
	static sf::SoundBuffer& loadResource(SoundFxId soundFxId);
	static sf::Texture& loadResource(TextureId textureId, sf::Rect<int> textureRect);
	static sf::Texture& loadResource(TextureId textureId);
	static sf::Shader& loadResource(ShaderId shaderId);
	static void clearFontCache() { m_fontCache.clear(); }
	static void clearSoundBufferCache() { m_soundBufferCache.clear(); }
	static void clearTextureCache() { m_textureCache.clear(); }
	static void clearShaderCache() { m_shaderCache.clear(); }
	static void clearAllCache() { m_textureCache.clear(); m_soundBufferCache.clear(); m_fontCache.clear(); m_shaderCache.clear(); }
 private:
	static std::string getTexturePath(TextureId textureId);
	static std::string getSoundPath(SoundFxId soundFxId);
	static std::string getFontPath(FontId fontId);
	static std::string getShaderPath(ShaderId shaderId);

	static Cache<sf::Texture> m_textureCache;
	static Cache<sf::SoundBuffer> m_soundBufferCache;
	static Cache<sf::Font> m_fontCache;
	static Cache<sf::Shader> m_shaderCache;
};

#endif //RESOURCEMANAGER_H_
