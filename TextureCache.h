#pragma once

#include "GLTexture.h"

#include <map>
#include <string>

namespace TRXEngine {
	/*Implements a texture cache class*/
	class TextureCache
	{
	public:
		TextureCache();
		~TextureCache();

		/* Retrieves texture with given file_path if it has been cached.
		Otherwise, load, cache, and return the new texture */
		GLTexture getTexture(std::string texture_path);

	private:
		std::map<std::string, GLTexture> m_texture_map{};
	};

}