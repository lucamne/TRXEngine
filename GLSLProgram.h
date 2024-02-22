#pragma once

#include <GL/glew.h>
#include <string>

namespace TRXEngine {
	// Used to compile shaders written in GLSL
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();
		// compile vertex and fragment shaders
		void compileShaders(const std::string& vertex_shader_fp, const std::string& fragment_shader_fp);
		// link vertex and fragment shaders using created ids
		void linkShaders();
		// add attributes to GLSL program
		void addAtrribute(const std::string& attribute_name);
		// Select program for use
		void use();
		// Unuse program
		void unuse();

		GLint getUniformLocation(const std::string& unifrom_name);
	private:
		// number of attributes per vertex (position, textures, colors, etc.)
		int m_num_attributes{};
		// id/handle to entire openGl program
		GLuint m_program_id{};
		GLuint m_vertex_shader_id{};
		GLuint m_fragment_shader_id{};


		// private functions
		void compileShader(const std::string& fp, GLuint id);
	};
}

