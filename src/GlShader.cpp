#include <vector>

#include "include/GlShader.hpp"
#include "include/GlUniform.hpp"

using namespace glimac;

GlShader::GlShader(FilePath dir_path, const std::string & file){
	m_dir_path = dir_path;
	m_file = file;
	m_program = loadProgram(m_dir_path+"shaders/"+m_file+"/"+m_file+".vs.glsl",
							m_dir_path+"shaders/"+m_file+"/"+m_file+".fs.glsl",
							m_dir_path+"shaders/"+m_file+"/"+m_file+".gs.glsl");
}

GlShader::GlShader(const GlShader & shader){
	m_dir_path = shader.m_dir_path;
	m_file = shader.m_file;
	m_program = loadProgram(m_dir_path+"shaders/"+m_file+"/"+m_file+".vs.glsl",
							m_dir_path+"shaders/"+m_file+"/"+m_file+".fs.glsl",
							m_dir_path+"shaders/"+m_file+"/"+m_file+".gs.glsl");
}


GlShader::~GlShader(){
}


void GlShader::useShader() const{
	m_program.use();
}

GLenum GlShader::getProgramId() const{
	return m_program.getGLId();
}

void GlShader::addUniform(UniformType uniform_type, const char* uniform_name){
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