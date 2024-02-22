#pragma once

#include "GLTexture.h"

#include <GL/glew.h>
#include <string>

namespace TRXEngine {
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		// public member functions
		void init(float x, float y, float width, float height, std::string texture_path);
		void draw();

	private:
		float m_x{};
		float m_y{};
		float m_width{};
		float m_height{};
		// video buffer id of sprete
		GLuint m_vbo_id;
		GLTexture m_texture{};
	};
}