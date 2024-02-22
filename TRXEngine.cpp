#include <SDL/SDL.h>
#include <GL/glew.h>
#include "TRXEngine.h"

namespace TRXEngine {
	int init()
	{
		// initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);
		// creates double buffer which lets us draw to one and then switch with active buffer to prvent flickering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		// Handle to created window

		return 0;
	}
}