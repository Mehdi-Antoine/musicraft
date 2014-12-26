#include <glimac/FilePath.hpp>

#include "include/World.hpp"
#include "include/GlEnvironnement.hpp"
#include "include/GlTexture.hpp"
#include "include/GlLight.hpp"
#include "include/GlElement.hpp"
#include "include/GlShader.hpp"
#include "include/GlUniform.hpp"


//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------CONSTRUCTOR---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

GlEnvironnement::GlEnvironnement(FilePath dir_path){

	m_dir_path = dir_path;
	
}

GlEnvironnement::~GlEnvironnement(){
	
}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void GlEnvironnement::addElement(const GlElement &gl_element){
	m_elements.push_back(gl_element);
}

void GlEnvironnement::addLight(const GlLight &gl_light){
	m_lights.push_back(gl_light);
}

void GlEnvironnement::addTexture(const GlTexture &gl_texture){
	m_textures.push_back(gl_texture);
}

void GlEnvironnement::addTextureVector(const std::vector<GlTexture> &texture_vector){
	for(int i = 0; i< texture_vector.size(); ++i){
		m_textures.push_back(texture_vector[i]);
	}
}

void GlEnvironnement::addShader(const GlShader &gl_shader){
	m_shaders.push_back(gl_shader);
}

void GlEnvironnement::addShaderVector(const std::vector<GlShader> &shader_vector){
	for(int i =0; i < shader_vector.size(); ++i){
		addShader(shader_vector[i]);
	}
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