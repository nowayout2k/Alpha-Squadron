//
// Created by Johnnie Otis on 6/9/24.
//

#include "../Header/DataCache.h"
#include "../Header/Logger.h"

std::unordered_map<std::string, std::shared_ptr<sf::Texture>> DataCache::m_textureCache;
std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> DataCache::m_soundCache;

std::shared_ptr<sf::Texture> DataCache::getTexture(const std::string path, const sf::IntRect textureRect)
{
	auto hashString = path + std::to_string(textureRect.left) + std::to_string(textureRect.top) +
							std::to_string(textureRect.width) + std::to_string(textureRect.height);

	if(m_textureCache.find(hashString) != m_textureCache.end())
		return m_textureCache[hashString];

	m_textureCache[hashString] = std::make_shared<sf::Texture>();
	auto texture = m_textureCache[hashString];

	if(textureRect == sf::IntRect())
	{
		if (!texture->loadFromFile(path))
		{
			Logger::Log(LogType::Error, "Texture not found at: " + path);
		}
	}
	else
	{
		if (!texture->loadFromFile(path, textureRect))
		{
			Logger::Log(LogType::Error, "Texture not found at: " + path);
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
		Logger::Log(LogType::Error, "Sound not found at: " + path);
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
