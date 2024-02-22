#include "Window.h"
#include "Errors.h"

namespace TRXEngine {
	Window::Window()
	{
	}

	Window::~Window()
	{
	}

	int Window::create(std::string window_name, int screen_width, int screen_height, unsigned int current_flags)
	{
		Uint32 flags{ SDL_WINDOW_OPENGL };

		if (current_flags & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (current_flags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (current_flags & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		m_sdl_window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, flags);
		if (m_sdl_window == nullptr)
		{
			fatalError("SDL Window could not be created!");
		}

		// context holds 'context' information about current use of OpenGL (textures, etc.)
		SDL_GLContext gl_context{ SDL_GL_CreateContext(m_sdl_window) };
		if (gl_context == nullptr)
		{
			fatalError("SDL_GL context could not be created!");
		}

		// glewInit initializes extensions for hardware that does not support all openGL functionality
		GLenum err{ glewInit() };
		if (err != GLEW_OK)
		{
			fatalError("Could not initialize glew!");
		}
		// check openGl version
		std::printf("***\tOpenGL Version: %s\t***\n", glGetString(GL_VERSION));

		// Sets default background color after calling glClear()
		glClearColor(0.0f, 0.0f, 1.0f, 1.0);

		// set vsync
		SDL_GL_SetSwapInterval(1);

		// enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}
}