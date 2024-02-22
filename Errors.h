#pragma once

#include <string>
#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>


namespace TRXEngine {
	// Header only file
	// Returns error message and quits SDL
	inline void fatalError(std::string error_string)
	{
		std::cout << error_string << "\nEnter any key to quit...";
		int temp{};
		std::cin >> temp;
		SDL_Quit();
		exit(69);
	}
}