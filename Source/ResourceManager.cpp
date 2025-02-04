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
	case TextureId::DecayedCityBg :
		return "../Assets/Textures/Backgrounds/decayed_city_bg_2048x1536.png";
	case TextureId::ForestBg :
		return "../Assets/Textures/Backgrounds/forest_bg_2048x1536.png";
	case TextureId::GameSpriteSheet :
		return "../Assets/Textures/Characters/game_sprite_sheet.png";
	case TextureId::MetalBg :
		return "../Assets/Textures/UI/metal_bg.png";
	case TextureId::JungleBg :
		return "../Assets/Textures/Backgrounds/jungle_bg_2048x1536.png";
	case TextureId::NightCityBg :
		return "../Assets/Textures/Backgrounds/night_city_bg_1920x1080.png";
	case TextureId::SkyBg:
		return "../Assets/Textures/Backgrounds/sky_bg_2048x1536.png";
	case TextureId::TallCityBg :
		return "../Assets/Textures/Backgrounds/tall_city_bg.png";
	case TextureId::UiSpriteSheet :
		return "../Assets/Textures/UI/ui_sprite_sheet.png";
	default:
		Debug::logError("Texture Id is unknown!");
		return "../Assets/Textures/UI/ui_sprite_sheet.png";
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
	case SoundFxId::DamageWarning1 :
		return "../Assets/SFX/damage_warning_1.wav";
	case SoundFxId::DamageWarning2 :
		return "../Assets/SFX/damage_warning_2.wav";
	case SoundFxId::TakeDamage :
		return "../Assets/SFX/take_damage.wav";
	case SoundFxId::BulletLaunch :
		return "../Assets/SFX/bullet_launch.wav";
	default:
		Debug::logError("Sound FX Id is unknown!" + std::to_string(static_cast<int>(soundFxId)));
		return "../Assets/SFX/button_click.wav";
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
		return "../Assets/Fonts/Arnold.ttf";
	}
}
