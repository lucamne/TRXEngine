#include "InputManager.h"
#include "InputManager.h"

namespace TRXEngine
{
	InputManager::InputManager()
		:m_mouse_coords{ 0 }
	{
	}
	InputManager::~InputManager()
	{
	}
	void InputManager::pressKey(unsigned int key_id)
	{
		m_key_map[key_id] = true;
	}
	void InputManager::releaseKey(unsigned int key_id)
	{
		m_key_map[key_id] = false;
	}
	bool const InputManager::isKeyPressed(unsigned int key_id)
	{
		auto iter{ m_key_map.find(key_id) };
		if (iter != m_key_map.end())
			return m_key_map[key_id];
		else
			return false;
	}
	void TRXEngine::InputManager::setMouseCoords(float x, float y)
	{
		m_mouse_coords.x = x;
		m_mouse_coords.y = y;
	}
}