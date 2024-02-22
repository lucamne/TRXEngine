#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace TRXEngine {

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screen_width, int screen_height);

		void update();

		// setters
		void setPosition(glm::vec2 new_position) { m_position = new_position; m_needs_matrix_update = true; }
		void setScale(float new_scale) { m_scale = new_scale; m_needs_matrix_update = true;}

		// getters
		glm::vec2 const getPosition() {  return m_position;}
		float getScale() const { return m_scale; }
		glm::mat4 getCameraMatrix() const { return m_camera_matrix; }

		glm::vec2 convertScreenToWorld(glm::vec2 screen_coords);

	private:
		int m_screen_width{};
		int m_screen_height{};
		bool m_needs_matrix_update{};
		float m_scale{};
		glm::vec2 m_position{};
		glm::mat4 m_camera_matrix{};
		glm::mat4 m_ortho_matrix{};
	};

}