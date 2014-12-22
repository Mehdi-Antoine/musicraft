#include "include/GlEnvironnement.hpp"


//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------CONSTRUCTOR---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

GlEnvironnement::GlEnvironnement(const char* dir_path){

	m_dir_path = dir_path;
	
}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void GlEnvironnement::addElement(const GlElement gl_element){
	m_elements.push_back(gl_element);
}

void GlEnvironnement::addLight(const GlLight gl_light){
	m_lights.push_back(gl_light);
}

void GlEnvironnement::addTexture(const GlTexture gl_texture){
	m_textures.push_back(gl_texture);
}

void GlEnvironnement::addShader(const GlShader gl_shader){
	m_shaders.push_back(gl_shader);
}

void GlEnvironnement::draw() const{

	for (int i = 0; i < m_elements.size(); ++i){
		ShaderProgram shader = m_elements[i].getShaderProgram();
		m_shaders[shader].useShader();
		m_elements[i].draw();
	}

}

void GlEnvironnement::update(const World &world){

}