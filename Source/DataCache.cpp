//
// Created by Johnnie Otis on 6/9/24.
//

#include "../Header/DataCache.h"
#include "../Header/Logger.h"

std::unordered_map<std::string, std::shared_ptr<sf::Texture>> DataCache::m_textureCache;
std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> DataCache::m_soundCache;
std::unordered_map<std::string, std::shared_ptr<sf::Font>> DataCache::m_fontCache;

std::shared_ptr<sf::Texture> DataCache::getTexture(const std::string path, const sf::IntRect textureRect)
{
	auto hashString = path + std::to_string(textureRect.left) + std::to_string(textureRect.top) +
							std::to_string(textureRect.width) + std::to_string(textureRect.height);

	if(m_textureCache.find(hashString) != m_textureCache.end())
		return m_textureCache[hashString];

	try
	{
		m_textureCache[hashString] = std::make_shared<sf::Texture>();
	}
	catch (const std::overflow_error& e)
	{
		Logger::log(Verbose, "Overflow error!");
	}

	auto texture = m_textureCache[hashString];

	if(textureRect == sf::IntRect())
	{
		if (!texture->loadFromFile(path))
		{
			Logger::log(LogType::Error, "Texture not found at: " + path);
		}
	}
	else
	{
		if (!texture->loadFromFile(path, textureRect))
		{
			Logger::log(LogType::Error, "Texture not found at: " + path);
		}
	}

	return texture;
}

void DataCache::cleanupTextureCache()
{
	for (auto itr = m_textureCache.begin(); itr != m_textureCache.end();)
	{
		if(itr->second.use_count() <= 1)
		{
			m_textureCache.erase(itr->first);
		}
		else
		{
			itr++;
		}
	}
}

std::shared_ptr<sf::SoundBuffer> DataCache::getSoundBuffer(const std::string path)
{
	if(m_soundCache.find(path) != m_soundCache.end())
		return m_soundCache[path];

	m_soundCache[path] = std::make_shared<sf::SoundBuffer>();
	auto soundBuffer = m_soundCache[path];

	if (!soundBuffer->loadFromFile(path))
	{
		Logger::log(LogType::Error, "Sound not found at: " + path);
	}

	return soundBuffer;
}

void DataCache::cleanupSoundCache()
{
	for (auto itr = m_soundCache.begin(); itr != m_soundCache.end();)
	{
		if(itr->second.use_count() <= 1)
		{
			m_soundCache.erase(itr->first);
		}
		else
		{
			itr++;
		}
	}
}

std::shared_ptr<sf::Font> DataCache::getFont(const Font font)
{
	std::string fontName;
	switch(font)
	{
	case Font::Gamer:
		fontName = "../Assets/Fonts/Gamer.ttf";
		break;

	}

	if(m_fontCache.find(fontName) != m_fontCache.end())
		return m_fontCache[fontName];

	m_fontCache[fontName] = std::make_shared<sf::Font>();
	auto fontBuffer = m_fontCache[fontName];

	if (!fontBuffer->loadFromFile(fontName))
	{
		Logger::log(LogType::Error, "Font name not found: " + fontName);
	}

	return fontBuffer;
}

void DataCache::cleanupFontCache()
{
	for (auto itr = m_fontCache.begin(); itr != m_fontCache.end();)
	{
		if(itr->second.use_count() <= 1)
		{
			m_fontCache.erase(itr->first);
		}
		else
		{
			itr++;
		}
	}
}
