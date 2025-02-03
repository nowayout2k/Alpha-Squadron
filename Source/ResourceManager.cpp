// Copyright (c) 2025 No Way Out LLC All rights reserved.

#include "../Headers/ResourceManager.h"

Cache<sf::Texture> ResourceManager::m_textureCache;
Cache<sf::SoundBuffer> ResourceManager::m_soundBufferCache;
Cache<sf::Font> ResourceManager::m_fontCache;

sf::Font& ResourceManager::loadResource(FontId fontId)
{
	return m_fontCache.load(std::to_string(static_cast<int>(fontId)), getFontPath(fontId));
}

sf::SoundBuffer& ResourceManager::loadResource(SoundFxId soundFxId)
{
	return m_soundBufferCache.load(std::to_string(static_cast<int>(soundFxId)), getSoundPath(soundFxId));
}

sf::Texture& ResourceManager::loadResource(TextureId textureId, sf::Rect<int> area)
{
	std::string path = getTexturePath(textureId);
	std::string hash = path + std::to_string(area.left) + std::to_string(area.top) + std::to_string(area.width) + std::to_string(area.height);
	return m_textureCache.load(hash, path, area);
}

sf::Texture& ResourceManager::loadResource(TextureId textureId)
{
	return loadResource(textureId, sf::Rect<int>());
}

std::string ResourceManager::getTexturePath(TextureId textureId)
{
	switch (textureId)
	{
	case TextureId::AircraftSpriteSheet :
		return "../Assets/Textures/AircraftSpriteSheet.png";
	default:
		Debug::logError("Texture Id is unknown!");
		return nullptr;
	}
}

std::string ResourceManager::getSoundPath(SoundFxId soundFxId)
{
	switch (soundFxId)
	{
	case SoundFxId::ButtonClick :
		return "../Assets/SFX/button_click.wav";
	case SoundFxId::CollectPickup :
		return "../Assets/SFX/collect_pickup.wav";
	case SoundFxId::Explosion :
		return "../Assets/SFX/explosion.wav";
	case SoundFxId::MenuClick :
		return "../Assets/SFX/menu_click.wav";
	case SoundFxId::MissileLaunch :
		return "../Assets/SFX/missile_launch.wav";
	default:
		Debug::logError("Sound FX Id is unknown!");
		return nullptr;
	}
}

std::string ResourceManager::getFontPath(FontId fontId)
{
	switch(fontId)
	{
	case FontId::Arnold:
		return "../Assets/Fonts/Arnold.ttf";
	default:
		Debug::logError("Font Id is unknown!");
		return nullptr;
	}
}
