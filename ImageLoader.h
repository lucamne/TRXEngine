#pragma once

#include "GLTexture.h"

#include <string>

namespace TRXEngine {
	/* Class to manager loading textures */
	class ImageLoader
	{
	public:
		/* Given filepath fp, load image into harware memory */
		static GLTexture loadPNG(std::string fp);
	};
}

