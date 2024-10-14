//
// Created by Johnnie Otis on 6/16/24.
//

#include "ResourceManager.h"

Cache<sf::Texture> ResourceManager::m_textureCache;
Cache<sf::SoundBuffer> ResourceManager::m_soundBufferCache;
Cache<sf::Font> ResourceManager::m_fontCache;

sf::Font& ResourceManager::loadResource(FontId fontId)
{
	return m_fontCache.load(std::to_string(fontId), getFontPath(fontId));
}

sf::SoundBuffer& ResourceManager::loadResource(SoundFxId soundFxId)
{
	return m_soundBufferCache.load(std::to_string(soundFxId), getSoundPath(soundFxId));
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
	case TextureId::BlueButtonIdle:
		return "../Assets/Textures/UI/Buttons/Blank/Rect-Icon-Blue/Idle.png";
	case TextureId::BlueButtonClicked:
		return "../Assets/Textures/UI/Buttons/Blank/Rect-Icon-Blue/Click.png";
	case TextureId::MagentaButtonIdle:
		return "../Assets/Textures/UI/Buttons/Blank/Rect-Icon-Magenta/Idle.png";
	case TextureId::MagentaButtonClicked:
		return "../Assets/Textures/UI/Buttons/Blank/Rect-Icon-Magenta/Click.png";
	default:
		Debug::logError(std::logic_error("Texture Id is unknown!"));
		return nullptr;
	}
}

std::string ResourceManager::getSoundPath(SoundFxId soundFxId)
{
	switch (soundFxId)
	{
	case SoundFxId::Collect :
		return "../Assets/SFX/Collect.wav";;
	case SoundFxId::Shoot1 :
		return "../Assets/SFX/Shoot1.wav";
	case SoundFxId::Damage :
		return "../Assets/SFX/Damage.wav";
	case SoundFxId::Explosion :
		return "../Assets/SFX/Explosion.wav";
	case SoundFxId::UNSquadronPositiveSelection :
		return "../Assets/SFX/UNSquadronStart.wav";
	default:
		Debug::logError(std::logic_error("Sound FX Id is unknown!"));
		return nullptr;
	}
}

std::string ResourceManager::getFontPath(FontId fontId)
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
