#include "SpriteBatch.h"

#include <algorithm>
#include <iostream>

namespace TRXEngine 
{
	SpriteBatch::SpriteBatch()
		:m_vbo{0},
		m_vao{0},
		m_glyphs{}
	{
	}
	SpriteBatch::~SpriteBatch()
	{
	}
	void SpriteBatch::init()
	{
		createVertexArray();
	}
	void SpriteBatch::begin(GlyphSortType sort_type /* = GlyphSortType::Texture*/)
	{
		m_sort_type = sort_type;
		m_render_batches.clear();

		for (Glyph* glyph : m_glyphs)
		{
			delete glyph;
		}

		m_glyphs.clear();
	}
	void SpriteBatch::end()
	{
		sortGlyphs();
	}
	// first 2 components of destination_rectangle and uv_rectangle are position and the second two components are dimensions
	void SpriteBatch::draw(const glm::vec4& destination_rectangle, const glm::vec4& uv_rectangle, GLuint texture, float depth, const Color& color)
	{
		Glyph* new_glyph{new Glyph};
		new_glyph->texture = texture;
		new_glyph->depth = depth;
		
		new_glyph->top_left.color = color;
		new_glyph->top_left.setPosition(destination_rectangle.x, destination_rectangle.y + destination_rectangle.w);
		new_glyph->top_left.setUV(uv_rectangle.x, uv_rectangle.y + uv_rectangle.w);

		new_glyph->bottom_left.color = color;
		new_glyph->bottom_left.setPosition(destination_rectangle.x, destination_rectangle.y);
		new_glyph->bottom_left.setUV(uv_rectangle.x, uv_rectangle.y);

		new_glyph->top_right.color = color;
		new_glyph->top_right.setPosition(destination_rectangle.x + destination_rectangle.z, destination_rectangle.y + destination_rectangle.w);
		new_glyph->top_right.setUV(uv_rectangle.x + uv_rectangle.z , uv_rectangle.y + uv_rectangle.w);

		new_glyph->bottom_right.color = color;
		new_glyph->bottom_right.setPosition(destination_rectangle.x + destination_rectangle.z, destination_rectangle.y);
		new_glyph->bottom_right.setUV(uv_rectangle.x + uv_rectangle.z, uv_rectangle.y);

		m_glyphs.push_back(new_glyph);
	}
	void SpriteBatch::renderBatch()
	{
		createRenderBatches();
		glBindVertexArray(m_vao);
		for (int i{ 0 }; i < m_render_batches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_render_batches[i].texture);
			glDrawArrays(GL_TRIANGLES, m_render_batches[i].offset, m_render_batches[i].num_vertices);
		}
		glBindVertexArray(0);
	}
	void SpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices{};
		vertices.resize(m_glyphs.size() * 6);

		if (m_glyphs.empty())
			return;

		int current_vertex{ 0 };
		int offset{ 0 };
		m_render_batches.emplace_back(offset, 6, m_glyphs[0]->texture);

		vertices[current_vertex++] = m_glyphs[0]->top_left;
		vertices[current_vertex++] = m_glyphs[0]->bottom_left;
		vertices[current_vertex++] = m_glyphs[0]->bottom_right;
		vertices[current_vertex++] = m_glyphs[0]->bottom_right;
		vertices[current_vertex++] = m_glyphs[0]->top_right;
		vertices[current_vertex++] = m_glyphs[0]->top_left;

		offset += 6;

		for (int current_glyph{ 1 }; current_glyph < m_glyphs.size(); current_glyph++)
		{
			if (m_glyphs[current_glyph]->texture != m_glyphs[current_glyph - 1]->texture)
			{
				m_render_batches.emplace_back(offset, 6, m_glyphs[0]->texture);
			}
			else
			{
				m_render_batches.back().num_vertices += 6;
			}
			vertices[current_vertex++] = m_glyphs[current_glyph]->top_left;
			vertices[current_vertex++] = m_glyphs[current_glyph]->bottom_left;
			vertices[current_vertex++] = m_glyphs[current_glyph]->bottom_right;
			vertices[current_vertex++] = m_glyphs[current_glyph]->bottom_right;
			vertices[current_vertex++] = m_glyphs[current_glyph]->top_right;
			vertices[current_vertex++] = m_glyphs[current_glyph]->top_left;

			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		// orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void SpriteBatch::createVertexArray()
	{
		if (m_vao == 0)
			glGenVertexArrays(1, &m_vao);
		
		// after binding anything done to change opengl state is stored in vertex array object
		glBindVertexArray(m_vao);


		if (m_vbo == 0)
			glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// vertexPosition attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		// vertexColor attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		// vertexUV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}
	void SpriteBatch::sortGlyphs()
	{
		switch (m_sort_type)
		{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_glyphs.begin(),m_glyphs.end(), compareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_glyphs.begin(), m_glyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(m_glyphs.begin(), m_glyphs.end(), compareTexture);
			break;
		}
		
	}
	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return a->depth < b->depth;
	}
	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b)
	{
		return  a->depth > b->depth;
	}
	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
	{
		return a->texture < b->texture;
	}
}