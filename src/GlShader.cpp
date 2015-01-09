#include <iostream>
#include <vector>

#include "include/GlShader.hpp"
#include "include/GlUniform.hpp"
#include "include/GlTexture.hpp"

using namespace glimac;

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//----------------------------------------------CLASS GL SHADER-------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------


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
	GlShader::useShader();
    GLint uTexture = glGetUniformLocation(getProgramId(), uniform_name);
    glUniform1i(uTexture, binding);
}


void GlShader::useShader() const{
	m_program.use();
}

GLuint GlShader::getProgramId() const{
	return m_program.getGLId();
}


//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------CLASS GL SHADER 2D------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------


GlShader2D::GlShader2D(FilePath dir_path, const std::string & file){

	m_dir_path = dir_path;
	m_file = file;

	m_program = loadProgram(m_dir_path+"shaders/"+m_file+"/shader.vs.glsl",
							m_dir_path+"shaders/"+m_file+"/shader.fs.glsl");

}

GlShader2D::GlShader2D(const GlShader2D & shader){
	m_dir_path = shader.m_dir_path;
	m_file = shader.m_file;
	m_program = loadProgram(m_dir_path+"shaders/"+m_file+"/shader.vs.glsl",
							m_dir_path+"shaders/"+m_file+"/shader.fs.glsl");
}


GlShader2D::~GlShader2D(){
}

void GlShader2D::attachTexture(const char* uniform_name, int binding) const{
	GlShader2D::useShader();
    GLint uTexture = glGetUniformLocation(getProgramId(), uniform_name);
    glUniform1i(uTexture, binding);
}


void GlShader2D::useShader() const{
	m_program.use();
}

GLuint GlShader2D::getProgramId() const{
	return m_program.getGLId();
}