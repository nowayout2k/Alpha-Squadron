//
// Created by Johnnie Otis on 6/9/24.
//

#include "../Header/Debug.h"

std::unordered_map<std::string, std::unique_ptr<sf::Texture>> DataCache::m_textureCache;
std::unordered_map<SoundEffectType, std::unique_ptr<sf::SoundBuffer>> DataCache::m_soundCache;
std::unordered_map<FontType, std::unique_ptr<sf::Font>> DataCache::m_fontCache;

sf::Texture* DataCache::getTexture(const TextureType textureType, const sf::IntRect textureRect)
{
	std::string path;
	switch (textureType)
	{
	case TextureType::AircraftSpriteSheet :
		path = "../Assets/Textures/AircraftSpriteSheet.png";
		break;
	case TextureType::Coin :
		path = "../Assets/Textures/Coin.png";
		break;
	case TextureType::DecayedBuildings1 :
		path = "../Assets/Textures/house1.png";
		break;
	case TextureType::DecayedBuildings2 :
		path = "../Assets/Textures/house2.png";
		break;
	case TextureType::DecayedBuildings3 :
		path = "../Assets/Textures/house3.png";
		break;
	case TextureType::EnemiesSpriteSheet :
		path = "../Assets/Textures/EnemiesSpriteSheet.png";
		break;
	case TextureType::SmoggySky :
		path = "../Assets/Textures/sky.png";
		break;
	}

	std::string hash = path + std::to_string(textureRect.left) + std::to_string(textureRect.top) + std::to_string(textureRect.width) + std::to_string(textureRect.height);

	if(m_textureCache.find(hash) != m_textureCache.end())
		return m_textureCache[hash].get();

	m_textureCache[hash] = std::make_unique<sf::Texture>();

	auto texture = m_textureCache[hash].get();

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

sf::SoundBuffer* DataCache::getSoundBuffer(const SoundEffectType soundType)
{
	std::string path;

	switch(soundType)
	{
	case SoundEffectType::Collect :
		path = "../Assets/SFX/Collect.wav";;
		break;
	case SoundEffectType::Shoot1 :
		path = "../Assets/SFX/Shoot1.wav";
		break;
	case SoundEffectType::UNSquadronPositiveSelection :
		path = "../Assets/SFX/UNSquadronStart.wav";
		break;
	default:
		Debug::log(Error, "Sound Effect Type is unknown!");
		return nullptr;
	}
	if(m_soundCache.find(soundType) != m_soundCache.end())
		return m_soundCache[soundType].get();

	m_soundCache[soundType] = std::make_unique<sf::SoundBuffer>();
	auto soundBuffer = m_soundCache[soundType].get();

	if (!soundBuffer->loadFromFile(path))
	{
		Debug::log(LogType::Error, "Sound not found at: " + path);
	}

	return soundBuffer;
}

sf::Font* DataCache::getFont(const FontType fontType)
{
	std::string fontName;
	switch(fontType)
	{
	case FontType::Gamer:
		fontName = "../Assets/Fonts/Gamer.ttf";
		break;
	}

	if(m_fontCache.find(fontType) != m_fontCache.end())
		return m_fontCache[fontType].get();

	m_fontCache[fontType] = std::make_unique<sf::Font>();
	auto fontBuffer = m_fontCache[fontType].get();

	if (!fontBuffer->loadFromFile(fontName))
	{
		Debug::log(LogType::Error, "Font name not found: " + fontName);
	}

	return fontBuffer;
}
