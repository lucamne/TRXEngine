#include "Bullet.h"
#include "GLTexture.h"
#include "ResourceManager.h"

namespace TRXEngine {
	Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifetime)
		:m_position{ pos },
		m_direction{ dir },
		m_speed{ speed },
		m_lifetime{lifetime}
	{
	}

	Bullet::~Bullet()
	{
	}
	void Bullet::draw(TRXEngine::SpriteBatch& sprite_batch)
	{
		glm::vec4 uv{ 0.0f, 0.0f, 1.0f, 1.0f };
		static TRXEngine::GLTexture texture{ TRXEngine::ResourceManager::getTexture("Textures/jimmy_jump/PNG/CharacterLeft_Standing.png") };
		TRXEngine::Color color{ 255,255,255,255 };

		glm::vec4 pos_and_size = glm::vec4(m_position.x, m_position.y, 30, 30);
		sprite_batch.draw(pos_and_size, uv, texture.id, 0.0f, color);
	}
	bool Bullet::update()
	{
		m_position += m_direction * m_speed;
		m_lifetime--;
		if (m_lifetime == 0)
		{
			return true;
		}
		return false;
	}
}