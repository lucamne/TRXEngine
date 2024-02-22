#pragma once

#include "SpriteBatch.h"
#include <glm/glm.hpp>

namespace TRXEngine {
	class Bullet
	{
	public:
		Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifetime);
		~Bullet();

		void draw(TRXEngine::SpriteBatch& sprite_batch);
		// returns true when we are out of life
		bool update();

	private:
		int m_lifetime{};
		float m_speed{};
		glm::vec2 m_direction{};
		glm::vec2 m_position{};
	};
}