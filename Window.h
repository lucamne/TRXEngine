#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>

#include <string>

namespace TRXEngine {
	enum WindowFlags
	{
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4,
	};


	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string window_name, int screen_width, int screen_height, unsigned int current_flags);
		int getScreenWidth() { return m_screen_width; }
		int getScreenHeight() { return m_screen_height; }
		void swapBuffer() { SDL_GL_SwapWindow(m_sdl_window); }
	private:
		SDL_Window* m_sdl_window{};
		int m_screen_width{};
		int m_screen_height{};
	};
}