//
// Created by Johnnie Otis on 6/9/24.
//

#include "../Header/DataCache.h"
#include "../Header/Debug.h"

std::unordered_map<std::string, std::unique_ptr<sf::Texture>> DataCache::m_textureCache;
std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> DataCache::m_soundCache;
std::unordered_map<std::string, std::unique_ptr<sf::Font>> DataCache::m_fontCache;

sf::Texture* DataCache::getTexture(const std::string path, const sf::IntRect textureRect)
{
	auto hashString = path + std::to_string(textureRect.left) + std::to_string(textureRect.top) +
							std::to_string(textureRect.width) + std::to_string(textureRect.height);

	if(m_textureCache.find(hashString) != m_textureCache.end())
		return m_textureCache[hashString].get();

	try
	{
		m_textureCache[hashString] = std::make_unique<sf::Texture>();
	}
	catch (const std::overflow_error& e)
	{
		Debug::log(Verbose, "Overflow error!");
	}

	auto texture = m_textureCache[hashString].get();

	if(textureRect == sf::IntRect())
	{
		if (!texture->loadFromFile(path))
		{
			Debug::log(LogType::Error, "Texture not found at: " + path);
		}
	}
	else
	{
		if (!texture->loadFromFile(path, textureRect))
		{
			Debug::log(LogType::Error, "Texture not found at: " + path);
		}
	}

	return texture;
}

sf::SoundBuffer* DataCache::getSoundBuffer(const std::string path)
{
	if(m_soundCache.find(path) != m_soundCache.end())
		return m_soundCache[path].get();

	m_soundCache[path] = std::make_unique<sf::SoundBuffer>();
	auto soundBuffer = m_soundCache[path].get();

	if (!soundBuffer->loadFromFile(path))
	{
		Debug::log(LogType::Error, "Sound not found at: " + path);
	}

	return soundBuffer;
}

sf::Font* DataCache::getFont(const Font font)
{
	std::string fontName;
	switch(font)
	{
	case Font::Gamer:
		fontName = "../Assets/Fonts/Gamer.ttf";
		break;

	}

	if(m_fontCache.find(fontName) != m_fontCache.end())
		return m_fontCache[fontName].get();

	m_fontCache[fontName] = std::make_unique<sf::Font>();
	auto fontBuffer = m_fontCache[fontName].get();

	if (!fontBuffer->loadFromFile(fontName))
	{
		Debug::log(LogType::Error, "Font name not found: " + fontName);
	}

	return fontBuffer;
}
