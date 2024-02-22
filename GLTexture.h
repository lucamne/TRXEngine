#pragma once

#include <GL/glew.h>

namespace TRXEngine {
	struct GLTexture
	{
		GLuint id{};
		int width{};
		int height{};
	};
}