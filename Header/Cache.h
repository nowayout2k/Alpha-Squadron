//
// Created by Johnnie Otis on 6/16/24.
//

#ifndef CACHE_H_
#define CACHE_H_

#include <iostream>
#include "Debug.h"

template <typename T>
class Cache
{
 public:
	void clear() { m_cache.clear(); }

	template <typename Parameter>
	T& load(const std::string& hash, const std::string& path, Parameter param)
	{
		auto cachedResource = getResource(hash);
		if(cachedResource != nullptr)
			return *cachedResource;

		std::unique_ptr<T> resource = std::make_unique<T>();
		if (!resource->loadFromFile(path, param))
			Debug::logError(std::runtime_error("Failed to load resource at " + path));

		m_cache.insert(std::make_pair(hash, std::move(resource)));

		return *m_cache[hash].get();
	}

	T& load(const std::string& hash, const std::string& path)
	{
		auto cachedResource = getResource(hash);
		if(cachedResource != nullptr)
			return *cachedResource;

		std::unique_ptr<T> resource = std::make_unique<T>();
		if (!resource->loadFromFile(path))
			Debug::logError(std::runtime_error("Failed to load resource at " + path));

		m_cache.insert(std::make_pair(hash, std::move(resource)));

		return *m_cache[hash].get();
	}
 private:
	T* getResource(const std::string& hash)
	{
		if(m_cache.find(hash) != m_cache.end())
			return m_cache[hash].get();

		return nullptr;
	}
	std::unordered_map<std::string, std::unique_ptr<T>> m_cache;
};

#endif //CACHE_H_
