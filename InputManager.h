#pragma once

#include <glm/glm.hpp>

#include <unordered_map>

namespace TRXEngine
{
	/// <summary>
	/// Class for managining key presses and mouse movement
	/// </summary>
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		// set a key as pressed
		void pressKey(unsigned int key_id);
		// set a key as releasd
		void releaseKey(unsigned int key_id);
		// return true if key is currently pressed
		bool const isKeyPressed(unsigned int key_id);
		// set coordinates of mouse
		void setMouseCoords(float x, float y);
		// return current mouse coordinates
		constexpr glm::vec2 const getMouseCoords() { return m_mouse_coords; }
	private:
		std::unordered_map<unsigned int, bool> m_key_map{};
		glm::vec2 m_mouse_coords{};
	};
}

