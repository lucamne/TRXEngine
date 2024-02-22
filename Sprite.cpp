#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <iostream>
#include <cstddef>

namespace TRXEngine {
	// public member functions
	Sprite::Sprite()
		:m_vbo_id{ 0 }
	{

	}

	Sprite::~Sprite()
	{
		if (m_vbo_id != 0)
		{
			glDeleteBuffers(1, &m_vbo_id);
		}
	}

	// Basic sprite class
	void Sprite::init(float x, float y, float width, float height, std::string texture_path)
	{
		m_x = x;
		m_y = y;
		m_width = width;
		m_height = height;
		m_texture = ResourceManager::getTexture(texture_path);


		if (m_vbo_id == 0)
		{
			glGenBuffers(1, &m_vbo_id);
		}
		// Vertex data of a square with 6 vertices (2 triangles)
		Vertex vertex_data[6];

		// First triangle
		// top right
		vertex_data[0].setPosition(m_x + m_width, m_y + m_height);
		vertex_data[0].setUV(1.0f, 1.0f);
		// top left
		vertex_data[1].setPosition(m_x, m_y + m_height);
		vertex_data[1].setUV(0.0f, 1.0f);
		// bottom left
		vertex_data[2].setPosition(m_x, m_y);
		vertex_data[2].setUV(0.0f, 0.0f);
		// Second triangle
		// bottom left
		vertex_data[3].setPosition(m_x, m_y);
		vertex_data[3].setUV(0.0f, 0.0f);
		// bottom right
		vertex_data[4].setPosition(m_x + m_width, m_y);
		vertex_data[4].setUV(1.0f, 0.0f);
		// top right
		vertex_data[5].setPosition(m_x + m_width, m_y + m_height);
		vertex_data[5].setUV(1.0f, 1.0f);



		for (int i{ 0 }; i < 6; i++)
		{
			vertex_data[i].setColor(255, 0, 0, 255);
		}

		vertex_data[1].setColor(0, 0, 255, 255);

		vertex_data[4].setColor(0, 255, 0, 255);


		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::draw()
	{
		glBindTexture(GL_TEXTURE_2D, m_texture.id);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// vertexPosition attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		// vertexColor attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		// vertexUV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}