// Copyright (c) 2025 No Way Out LLC All rights reserved.

/**
 * @file ResourceManager.h
 * @brief Declaration of the ResourceManager class.
 *
 * This header declares the ResourceManager class, which provides static methods
 * to load and cache various game resources such as fonts, sound buffers, textures,
 * and shaders. It utilizes a generic Cache class to store and retrieve resources,
 * ensuring that each resource is loaded only once.
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include "SoundFxId.h"
#include "TextureId.h"
#include "../Engine/Cache.h"
#include "../Engine/FontId.h"
#include "../Engine/ShaderId.h"

namespace AlphaSquadron
{
	/**
	 * @class ResourceManager
	 * @brief Manages loading and caching of game resources.
	 *
	 * The ResourceManager class provides static methods for loading and caching resources.
	 * It supports fonts, sound buffers, textures, and shaders. Each resource is identified
	 * by an ID, and helper functions generate the corresponding file paths.
	 */
	class ResourceManager
	{
	 public:
		/**
		 * @brief Loads a font resource.
		 * @param fontId The identifier of the font to load.
		 * @return A reference to the loaded sf::Font.
		 */
		static sf::Font& loadResource(Engine::FontId fontId);

		/**
		 * @brief Loads a sound buffer resource.
		 * @param soundFxId The identifier of the sound effect to load.
		 * @return A reference to the loaded sf::SoundBuffer.
		 */
		static sf::SoundBuffer& loadResource(SoundFxId soundFxId);

		/**
		 * @brief Loads a texture resource with a specific sub-rectangle.
		 * @param textureId The identifier of the texture to load.
		 * @param textureRect The rectangle defining the sub-area to load.
		 * @return A reference to the loaded sf::Texture.
		 */
		static sf::Texture& loadResource(TextureId textureId, sf::Rect<int> textureRect);

		/**
		 * @brief Loads a texture resource.
		 * @param textureId The identifier of the texture to load.
		 * @return A reference to the loaded sf::Texture.
		 */
		static sf::Texture& loadResource(TextureId textureId);

		/**
		 * @brief Loads a shader resource.
		 * @param shaderId The identifier of the shader to load.
		 * @return A reference to the loaded sf::Shader.
		 */
		static sf::Shader& loadResource(Engine::ShaderId shaderId);

		/// Clears the font cache.
		static void clearFontCache()
		{
			m_fontCache.clear();
		}
		/// Clears the sound buffer cache.
		static void clearSoundBufferCache()
		{
			m_soundBufferCache.clear();
		}
		/// Clears the texture cache.
		static void clearTextureCache()
		{
			m_textureCache.clear();
		}
		/// Clears the shader cache.
		static void clearShaderCache()
		{
			m_shaderCache.clear();
		}
		/// Clears all resource caches.
		static void clearAllCache()
		{
			m_textureCache.clear();
			m_soundBufferCache.clear();
			m_fontCache.clear();
			m_shaderCache.clear();
		}

	 private:
		/**
		 * @brief Retrieves the file path for a given texture ID.
		 * @param textureId The texture identifier.
		 * @return The file path as a string.
		 */
		static std::string getTexturePath(TextureId textureId);

		/**
		 * @brief Retrieves the file path for a given sound effect ID.
		 * @param soundFxId The sound effect identifier.
		 * @return The file path as a string.
		 */
		static std::string getSoundPath(SoundFxId soundFxId);

		/**
		 * @brief Retrieves the file path for a given font ID.
		 * @param fontId The font identifier.
		 * @return The file path as a string.
		 */
		static std::string getFontPath(Engine::FontId fontId);

		/**
		 * @brief Retrieves the file path for a given shader ID.
		 * @param shaderId The shader identifier.
		 * @return The file path as a string.
		 */
		static std::string getShaderPath(Engine::ShaderId shaderId);

		// Resource caches for each type.
		static Engine::Cache<sf::Texture> m_textureCache;
		static Engine::Cache<sf::SoundBuffer> m_soundBufferCache;
		static Engine::Cache<sf::Font> m_fontCache;
		static Engine::Cache<sf::Shader> m_shaderCache;
	};
}
#endif //RESOURCEMANAGER_H_
