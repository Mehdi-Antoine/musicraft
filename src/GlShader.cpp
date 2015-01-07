#include <iostream>
#include <vector>

#include "include/GlShader.hpp"
#include "include/GlUniform.hpp"
#include "include/GlTexture.hpp"

using namespace glimac;

GlShader::GlShader(FilePath dir_path, const std::string & file){
	m_dir_path = dir_path;
	m_file = file;

	m_program = loadProgram(m_dir_path+"shaders/"+m_file+"/shader.vs.glsl",
							m_dir_path+"shaders/"+m_file+"/shader.gs.glsl",
							m_dir_path+"shaders/"+m_file+"/shader.fs.glsl");

}

GlShader::GlShader(const GlShader & shader){
	m_dir_path = shader.m_dir_path;
	m_file = shader.m_file;
	m_program = loadProgram(m_dir_path+"shaders/"+m_file+"/shader.vs.glsl",
							m_dir_path+"shaders/"+m_file+"/shader.gs.glsl",
							m_dir_path+"shaders/"+m_file+"/shader.fs.glsl");
}


GlShader::~GlShader(){
}

void GlShader::attachTexture(const char* uniform_name, int binding) const{
	useShader();
    GLint uTexture = glGetUniformLocation(getProgramId(), uniform_name);
    glUniform1i(uTexture, binding);
}


void GlShader::useShader() const{
	m_program.use();
}

GLuint GlShader::getProgramId() const{
	return m_program.getGLId();
}

void GlShader::linkUniform(UniformType uniform_type, const char* uniform_name){
	if(uniform_type == VEC3){
		GlUniformVec3 uniform(getProgramId(), uniform_name);
		m_uniforms.push_back(&uniform);
	}
	else if(uniform_type == MAT4){
		GlUniformMat4 uniform(getProgramId(), uniform_name);
		m_uniforms.push_back(&uniform);
	}
	else if(uniform_type == FLOAT){
		GlUniformFloat uniform(getProgramId(), uniform_name);
		m_uniforms.push_back(&uniform);
	}


}

