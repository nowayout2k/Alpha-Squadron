// Copyright (c) 2025 No Way Out LLC All rights reserved.

#ifndef CACHE_H_
#define CACHE_H_

// Local includes using quotes.
#include "Debug.h"

// Standard library includes.
#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>

/**
 * @file Cache.h
 * @brief Declares the Cache template class.
 *
 * The Cache class provides a resource management system that caches resources identified
 * by a unique hash. It supports loading resources from a file with or without additional
 * parameters, and it ensures that a resource is loaded only once.
 */
template <typename T>
class Cache
{
 public:
	/**
	 * @brief Clears all cached resources.
	 */
	void clear() { m_cache.clear(); }

	/**
	 * @brief Loads a resource with an extra parameter.
	 *
	 * If the resource is already cached, it returns the cached instance.
	 * Otherwise, it attempts to load the resource from the specified file.
	 *
	 * @param hash A unique string identifier for the resource.
	 * @param path The file path to load the resource from.
	 * @param param A parameter passed to the resource's loadFromFile method.
	 * @return A reference to the loaded resource.
	 */
	template <typename Parameter>
	T& load(const std::string& hash, const std::string& path, Parameter param)
	{
		T* cachedResource = getResource(hash);
		if (cachedResource != nullptr)
			return *cachedResource;

		std::unique_ptr<T> resource = std::make_unique<T>();
		if (!resource->loadFromFile(path, param))
		{
			Debug::logError("Failed to load resource at " + path);
		}

		m_cache.insert(std::make_pair(hash, std::move(resource)));
		return *m_cache[hash].get();
	}

	/**
	 * @brief Loads a resource without an extra parameter.
	 *
	 * If the resource is already cached, it returns the cached instance.
	 * Otherwise, it attempts to load the resource from the specified file.
	 *
	 * @param hash A unique string identifier for the resource.
	 * @param path The file path to load the resource from.
	 * @return A reference to the loaded resource.
	 */
	T& load(const std::string& hash, const std::string& path)
	{
		T* cachedResource = getResource(hash);
		if (cachedResource != nullptr)
			return *cachedResource;

		std::unique_ptr<T> resource = std::make_unique<T>();
		if (!resource->loadFromFile(path))
		{
			Debug::logError("Failed to load resource at " + path);
		}

		m_cache.insert(std::make_pair(hash, std::move(resource)));
		return *m_cache[hash].get();
	}

 private:
	/**
	 * @brief Retrieves a cached resource.
	 *
	 * @param hash The unique string identifier for the resource.
	 * @return A pointer to the resource if found; otherwise, nullptr.
	 */
	T* getResource(const std::string& hash)
	{
		if (m_cache.find(hash) != m_cache.end())
			return m_cache[hash].get();

		return nullptr;
	}

	std::unordered_map<std::string, std::unique_ptr<T>> m_cache; // Map of cached resources.
};

#endif // CACHE_H_
