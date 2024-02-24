#include "Sprite.h"

#include "ResourceManager.h"

namespace TRXEngine 
{
	Sprite::Sprite()
	{
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::init(const std::string& path_to_texture, glm::vec4 pos_and_dim, glm::vec4 uv_rec, float depth, TRXEngine::Color color)
	{
		m_pos_and_dim = pos_and_dim;
		m_texture = TRXEngine::ResourceManager::getTexture(path_to_texture);
		m_uv_pos_and_dim = uv_rec;
		m_depth = depth;
		m_color = color;
	}

	void Sprite::draw(TRXEngine::SpriteBatch& sprite_batch) const
	{
		sprite_batch.draw(m_pos_and_dim, m_uv_pos_and_dim, m_texture.id, m_depth, m_color);
	}
}