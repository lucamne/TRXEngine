#include "Sprite.h"

#include "ResourceManager.h"

namespace TRXEngine 
{
	Sprite::Sprite(glm::vec4 pos_and_dim, const std::string& path_to_texture, glm::vec4 uv_rec, float depth, TRXEngine::Color color)
		:m_depth{ depth },
		m_pos_and_dim{ pos_and_dim },
		m_uv_pos_and_dim{ uv_rec },
		m_texture{ TRXEngine::ResourceManager::getTexture(path_to_texture) },
		m_color{ color }
	{
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::draw(TRXEngine::SpriteBatch& sprite_batch) const
	{
		sprite_batch.draw(m_pos_and_dim, m_uv_pos_and_dim, m_texture.id, m_depth, m_color);
	}
}