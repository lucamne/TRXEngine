#pragma once

#include "TextureCache.h"
#include "GLTexture.h"

namespace TRXEngine {
	/*
	Manages an instance of a TextureCache texture cache*/
	class ResourceManager
	{
	public:
		static GLTexture getTexture(std::string texture_path);
	private:
		static TextureCache m_texture_cache;
	};

}