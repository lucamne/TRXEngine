#include "Camera2D.h"

namespace TRXEngine {

	Camera2D::Camera2D()
		:m_screen_width{ 500 },
		m_screen_height{ 500 },
		m_needs_matrix_update{ true },
		m_scale{ 1.0f },
		m_position{ 0.0f, 0.0f },
		m_camera_matrix{ 1.0f },
		m_ortho_matrix{ 1.0f }
	{
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int screen_width, int screen_height)
	{
		m_screen_height = screen_height;
		m_screen_width = screen_width;
		m_ortho_matrix = glm::ortho(0.0f, (float)m_screen_width, 0.0f, float(m_screen_height));
	}

	void Camera2D::update()
	{
		if (m_needs_matrix_update)
		{
			glm::vec3 translate{ -m_position.x + m_screen_width/2.0f,-m_position.y + m_screen_height/2.0f, 0.0f };
			m_camera_matrix = glm::translate(m_ortho_matrix, translate);

			glm::vec3 scale{ m_scale,m_scale,0.0f };
			m_camera_matrix = glm::scale(glm::mat4(1.0f), scale) * m_camera_matrix;


			m_needs_matrix_update = false;
		}
	}
	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screen_coords)
	{
		// invert y direction
		screen_coords.y = m_screen_height - screen_coords.y;
		// make it so that 0 is the center of the screen
		screen_coords -= glm::vec2(m_screen_width / 2, m_screen_height / 2);
		// scale the coordinates
		screen_coords /= m_scale;
		// translate relative to camera position
		screen_coords += m_position;
		return screen_coords;
	}
}