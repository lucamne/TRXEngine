#include "ResourceManager.h"

namespace TRXEngine {
	TextureCache ResourceManager::m_texture_cache{};

	GLTexture ResourceManager::getTexture(std::string texture_path)
	{
		return m_texture_cache.getTexture(texture_path);
	}
}