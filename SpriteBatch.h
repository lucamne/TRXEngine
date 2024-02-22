#pragma once

#include "Vertex.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <vector>

namespace TRXEngine 
{
	enum class GlyphSortType
	{
		NONE,
		FRONT_TO_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	struct Glyph
	{
		GLuint texture{};
		float depth{};

		Vertex top_left{};
		Vertex bottom_left{};
		Vertex top_right{};
		Vertex bottom_right{};
	};

	// render batch contains information on where sprite batches are located in vertex buffer object
	struct RenderBatch
	{
		RenderBatch(GLuint Offset, GLuint Num_Vertices, GLuint Texture)
			:offset{ Offset },
			num_vertices {Num_Vertices},
			texture{Texture}{}

		GLuint offset{};
		GLuint num_vertices{};
		GLuint texture{};
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void init();

		void begin(GlyphSortType sort_type = GlyphSortType::TEXTURE);
		void end();

		void draw(const glm::vec4& destinstion_rectangle, const glm::vec4& uv_rectangle, GLuint texture, float depth, const Color& color);
		void renderBatch();

	private:
		void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();

		static bool compareFrontToBack(Glyph* a, Glyph* b);
		static bool compareBackToFront(Glyph* a, Glyph* b);
		static bool compareTexture(Glyph* a, Glyph* b);

		// vertex buffer object
		GLuint m_vbo{};
		// vertex array object holds openGl state information
		GLuint m_vao{};

		GlyphSortType m_sort_type{};

		std::vector<Glyph *> m_glyphs{};
		std::vector<RenderBatch> m_render_batches{};
	};
}

