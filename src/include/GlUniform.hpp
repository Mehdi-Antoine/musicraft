#pragma once
#include <GL/glew.h>
#include <string>

class GlUniform{
private:
	std::string m_name;
	GLint m_value;
	
	
public:
	GlUniform(GLuint gl_id, const std::string & name);
	~GlUniform();

	/* data */
};