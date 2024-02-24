#pragma once

#include "GLTexture.h"
#include "SpriteBatch.h"

#include <glm/glm.hpp>

#include <string>

namespace TRXEngine 
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(glm::vec4 pos_and_dim, const std::string& path_to_texture, glm::vec4 uv_rec = { 0.0f,0.0f,1.0f,1.0f }, float depth = 1.0f, TRXEngine::Color color = { 255,255,255,255 });

		void draw(TRXEngine::SpriteBatch& sprite_batch) const;

		// getters
		glm::vec4 getPositionAndDimensions() const { return m_pos_and_dim; }
		GLuint getTextureLocation() const { return m_texture.id; }
		// setters
		void setPosition(glm::vec2 new_pos) { m_pos_and_dim = glm::vec4(new_pos, m_pos_and_dim.z, m_pos_and_dim.w); }


	private:
		// render depth
		float m_depth{};
		// x, y, width, height
		glm::vec4 m_pos_and_dim{};
		// all values from 0 to 1, x, y, width, height
		glm::vec4 m_uv_pos_and_dim{};

		TRXEngine::GLTexture m_texture{};
		TRXEngine::Color m_color{};
	};
}