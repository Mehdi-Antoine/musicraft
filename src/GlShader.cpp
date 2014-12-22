#include "include/GlShader.hpp"

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

}