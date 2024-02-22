#pragma once

#include <glm/glm.hpp>

#include <unordered_map>

namespace TRXEngine
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void pressKey(unsigned int key_id);
		void releaseKey(unsigned int key_id);

		bool const isKeyPressed(unsigned int key_id);

		void setMouseCoords(float x, float y);
		constexpr glm::vec2 const getMouseCoords() { return m_mouse_coords; }
	private:
		std::unordered_map<unsigned int, bool> m_key_map{};
		glm::vec2 m_mouse_coords{};
	};
}

