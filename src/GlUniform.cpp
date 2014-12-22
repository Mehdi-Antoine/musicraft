#include "include/GlUniform.hpp"

GlUniform::GlUniform(GLuint gl_id, const std::string & name){
	m_name = name;
	m_value = glGetUniformLocation(gl_id, m_name);
}

GlUniform::~GlUniform(){
	
}