//
// Created by Johnnie Otis on 6/9/24.
//

#include "../Header/Debug.h"

std::unordered_map<std::string, std::unique_ptr<sf::Texture>> ResourceCache::m_textureCache;
std::unordered_map<SoundFxId, std::unique_ptr<sf::SoundBuffer>> ResourceCache::m_soundCache;
std::unordered_map<FontId, std::unique_ptr<sf::Font>> ResourceCache::m_fontCache;

std::string ResourceCache::getTexturePath(TextureId textureId)
{
	switch (textureId)
	{
	case TextureId::AircraftSpriteSheet :
		return "../Assets/Textures/AircraftSpriteSheet.png";
	case TextureId::Coin :
		return "../Assets/Textures/Coin.png";
	case TextureId::DecayedBuildings1 :
		return "../Assets/Textures/house1.png";
	case TextureId::DecayedBuildings2 :
		return "../Assets/Textures/house2.png";
	case TextureId::DecayedBuildings3 :
		return "../Assets/Textures/house3.png";
	case TextureId::EnemiesSpriteSheet :
		return "../Assets/Textures/EnemiesSpriteSheet.png";
	case TextureId::SmoggySky :
		return "../Assets/Textures/sky.png";
	default:
		Debug::logError(std::logic_error("Texture Id is unknown!"));
		return nullptr;
	}
}

sf::Texture* ResourceCache::getTexture(const TextureId textureId, const sf::IntRect textureRect)
{
	std::string path = getTexturePath(textureId);

	std::string hash = path + std::to_string(textureRect.left) + std::to_string(textureRect.top) + std::to_string(textureRect.width) + std::to_string(textureRect.height);

	if(m_textureCache.find(hash) != m_textureCache.end())
		return m_textureCache[hash].get();

	m_textureCache[hash] = std::make_unique<sf::Texture>();

	auto texture = m_textureCache[hash].get();

	if(textureRect == sf::IntRect())
	{
		if (!texture->loadFromFile(path))
		{
			Debug::logError(std::runtime_error("Texture not found at: " + path));
		}
	}
	else
	{
		if (!texture->loadFromFile(path, textureRect))
		{
			Debug::logError(std::runtime_error("Texture not found at: " + path));
		}
	}

	return texture;
}

std::string ResourceCache::getSoundPath(SoundFxId soundFxId)
{
	switch(soundFxId)
	{
	case SoundFxId::Collect :
		return "../Assets/SFX/Collect.wav";;
	case SoundFxId::Shoot1 :
		return "../Assets/SFX/Shoot1.wav";
	case SoundFxId::UNSquadronPositiveSelection :
		return "../Assets/SFX/UNSquadronStart.wav";
	default:
		Debug::logError(std::logic_error("Sound FX Id is unknown!"));
		return nullptr;
	}
}

sf::SoundBuffer* ResourceCache::getSoundBuffer(const SoundFxId soundFxId)
{
	std::string path = getSoundPath(soundFxId);
	if(m_soundCache.find(soundFxId) != m_soundCache.end())
		return m_soundCache[soundFxId].get();

	m_soundCache[soundFxId] = std::make_unique<sf::SoundBuffer>();
	auto soundBuffer = m_soundCache[soundFxId].get();

	if (!soundBuffer->loadFromFile(path))
	{
		Debug::logError(std::runtime_error("Sound not found at: " + path));
	}

	return soundBuffer;
}

std::string ResourceCache::getFontPath(FontId fontId)
{
	switch(fontId)
	{
	case FontId::Gamer:
		return "../Assets/Fonts/Gamer.ttf";
	default:
		Debug::logError(std::logic_error("Font Id is unknown!"));
		return nullptr;
	}
}

sf::Font* ResourceCache::getFont(const FontId fontId)
{
	std::string fontPath = getFontPath(fontId);

	if(m_fontCache.find(fontId) != m_fontCache.end())
		return m_fontCache[fontId].get();

	m_fontCache[fontId] = std::make_unique<sf::Font>();
	auto fontBuffer = m_fontCache[fontId].get();

	if (!fontBuffer->loadFromFile(fontPath))
	{
		Debug::logError(std::runtime_error("Font name not found: " + fontPath));
	}

	return fontBuffer;
}
