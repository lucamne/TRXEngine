#include "GLSLProgram.h"
#include "Errors.h"

#include <fstream>
#include <vector>

// public member functions

namespace TRXEngine {
	GLSLProgram::GLSLProgram()
		:m_num_attributes{ 0 },
		m_program_id{ 0 },
		m_vertex_shader_id{ 0 },
		m_fragment_shader_id{ 0 }
	{
	}

	GLSLProgram::~GLSLProgram()
	{
	}

	// given filepath to vertex and fragment shaders written in GLSL, compile shaders
	void GLSLProgram::compileShaders(const std::string& vertex_shader_fp, const std::string& fragment_shader_fp)
	{
		// create program id and object
		m_program_id = glCreateProgram();

		// create shader objects
		m_vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
		if (m_vertex_shader_id == 0)
		{
			fatalError("Vertex shader failed to be created!");
		}
		m_fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
		if (m_fragment_shader_id == 0)
		{
			fatalError("Fragment shader failed to be created!");
		}

		compileShader(vertex_shader_fp, m_vertex_shader_id);
		compileShader(fragment_shader_fp, m_fragment_shader_id);
	}

	void GLSLProgram::linkShaders()
	{
		// Attach our shaders to our program
		glAttachShader(m_program_id, m_vertex_shader_id);
		glAttachShader(m_program_id, m_fragment_shader_id);

		// Link our program
		glLinkProgram(m_program_id);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint is_linked{ 0 };
		glGetProgramiv(m_program_id, GL_LINK_STATUS, (int*)&is_linked);
		if (!is_linked)
		{
			GLint max_length{ 0 };
			glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &max_length);

			// The maxLength includes the NULL character
			std::vector<char> error_log(max_length);
			glGetProgramInfoLog(m_program_id, max_length, &max_length, &error_log[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_program_id);
			// Don't leak shaders either.
			glDeleteShader(m_vertex_shader_id);
			glDeleteShader(m_fragment_shader_id);

			// Use the infoLog as you see fit.
			std::printf("%s\n", &error_log[0]);
			fatalError("Shaders failed to link!");
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_program_id, m_vertex_shader_id);
		glDetachShader(m_program_id, m_fragment_shader_id);
		glDeleteShader(m_vertex_shader_id);
		glDeleteShader(m_fragment_shader_id);
	}

	void GLSLProgram::addAtrribute(const std::string& attribute_name)
	{
		glBindAttribLocation(m_program_id, m_num_attributes++, attribute_name.c_str());
	}

	void GLSLProgram::use()
	{
		glUseProgram(m_program_id);
		for (int i{ 0 }; i < m_num_attributes; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuse()
	{
		glUseProgram(0);
		for (int i{ 0 }; i < m_num_attributes; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniform_name)
	{
		GLint location{ glGetUniformLocation(m_program_id, uniform_name.c_str()) };
		if (location == GL_INVALID_INDEX)
		{
			fatalError("Uniform " + uniform_name + " not found in shader!");
		}
		return location;
	}


	/*private functions*/

	void GLSLProgram::compileShader(const std::string& file_path, GLuint id)
	{
		// load vertex shader to read into string for compilation
		std::ifstream vertex_file(file_path);
		if (vertex_file.fail())
		{
			perror(file_path.c_str());
			fatalError("Failed to open " + file_path);
		}
		std::string file_contents{};
		std::string line{};
		while (std::getline(vertex_file, line))
		{
			file_contents += line + '\n';
		}
		vertex_file.close();

		// hack to get pointer to beginning of file_contents string
		const char* contents_ptr{ file_contents.c_str() };
		// Bind shader to shader id and compile
		glShaderSource(id, 1, &contents_ptr, nullptr);
		glCompileShader(id);

		// Error checking for vertex shader compilation
		// see openGL shader compilation documentation for more information on this code
		GLint success{ 0 };
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLint max_length{ 0 };
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &max_length);

			std::vector<char> error_log(max_length);
			glGetShaderInfoLog(id, max_length, &max_length, &error_log[0]);

			glDeleteShader(id);

			std::printf("%s\n", &error_log[0]);
			fatalError("Shader " + file_path + " failed to compile!");
		}
	}
}