#include "TextureCache.h"
#include "ImageLoader.h"

#include <iostream>
namespace TRXEngine {
	TextureCache::TextureCache()
	{
	}

	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string texture_path)
	{
		auto map_iter{ m_texture_map.find(texture_path) };
		// if texture_path in map, return GLTexture
		if (map_iter != m_texture_map.end())
		{
			std::cout << "Used cached texture: " << texture_path << '\n';
			return map_iter->second;
		}
		GLTexture new_texture{ ImageLoader::loadPNG(texture_path) };
		// add new pair (texture_path, GLTexture)  to m_texture_map
		m_texture_map.emplace(texture_path, new_texture);

		std::cout << "Loaded texture: " << texture_path << '\n';

		return new_texture;
	}
}