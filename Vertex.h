#pragma once

#include "GL/glew.h"

namespace TRXEngine {
	// Holds x and y coordinates
	struct Position
	{
		float x{};
		float y{};
	};

	// Holds r, g, b, alpha color information
	struct Color
	{
		GLubyte r{};
		GLubyte g{};
		GLubyte b{};
		GLubyte a{};
	};


	struct UV
	{
		float u{};
		float v{};
	};

	// holds vertex attribute information
	struct Vertex
	{
		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
		void setPosition(float x, float y);
		void setUV(float u, float v);

		Position position{};
		Color color{};
		UV uv{};
	};
}