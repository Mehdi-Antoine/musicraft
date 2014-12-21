#pragma once

#include <GL/glew.h>
#include "Shader.hpp"
#include "FilePath.hpp"

namespace glimac {

class Program {
public:
	Program(): m_nGLId(glCreateProgram()) {
	}

	~Program() {
		glDeleteProgram(m_nGLId);
	}

	Program(Program&& rvalue): m_nGLId(rvalue.m_nGLId) {
		rvalue.m_nGLId = 0;
	}

	Program& operator =(Program&& rvalue) {
		m_nGLId = rvalue.m_nGLId;
		rvalue.m_nGLId = 0;
		return *this;
	}

	GLuint getGLId() const {
		return m_nGLId;
	}

	void attachShader(const Shader& shader) {
		glAttachShader(m_nGLId, shader.getGLId());
	}

	bool link();

	const std::string getInfoLog() const;

	void use() const {
		glUseProgram(m_nGLId);
	}

private:
	Program(const Program&);
	Program& operator =(const Program&);

	GLuint m_nGLId;
};

// Build a GLSL program from source code with vertex shader and fragment shader
Program buildProgram(const GLchar* vsSrc, const GLchar* fsSrc);

// Build a GLSL program from source code with vertex shader, fragment shader, and geometry shader
Program buildProgram(const GLchar* vsSrc, const GLchar* fsSrc, const GLchar* gsSrc);

// Load source code from files and build a GLSL program with vs an fs
Program loadProgram(const FilePath& vsFile, const FilePath& fsFile);

// Load source code from files and build a GLSL program with vs, gs and fs
Program loadProgram(const FilePath& vsFile, const FilePath& fsFile, const FilePath& gsFile); 


}
