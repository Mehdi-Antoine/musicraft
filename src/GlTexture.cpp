#include <GL/glew.h>
#include <iostream>

#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>

#include "include/GlTexture.hpp"

using namespace glimac;

//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------CONSTRUCTOR---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

GlTexture::GlTexture(){
	m_texture_data = NULL;
	m_texture_id = 0;
}

GlTexture::GlTexture(const GlTexture& gl_texture){
	m_texture_data = gl_texture.getTextureData();

	m_texture_width = gl_texture.getTextureWidth();
	m_texture_height = gl_texture.getTextureHeight();

	m_texture_id = gl_texture.getTextureId();
}

GlTexture::GlTexture(FilePath path){

    m_texture_data = loadImage(path)->getPixels();

    m_texture_width = loadImage(path)->getWidth();
    m_texture_height = loadImage(path)->getHeight();

    if(m_texture_data == NULL){
        std::cerr << "Pas de fichier image chargé pour la texture : " << path;
    }


    //CREATION DES VARIABLES OPENGL
    glGenTextures(1, &m_texture_id);

    //LOAD DES TEXTURES DANS OPEN GL
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,  
                 0,  
                  GL_RGBA,  
                  m_texture_width,  
                  m_texture_height,  
                  0,  
                  GL_RGBA,  
                  GL_FLOAT,  
                  m_texture_data);

    glBindTexture(GL_TEXTURE_2D, 0);

}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------GETTERS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

	GLuint GlTexture::getTextureId() const{
		return m_texture_id;
	}

	glm::vec4* GlTexture::getTextureData() const{
		return m_texture_data;
	}

	unsigned int GlTexture::getTextureWidth() const{
		return m_texture_width;
	}

	unsigned int GlTexture::getTextureHeight() const{
		return m_texture_height;
	}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void GlTexture::load(FilePath path){
	if(m_texture_data == NULL){

		m_texture_data = loadImage(path)->getPixels();

	    m_texture_width = loadImage(path)->getWidth();
	    m_texture_height = loadImage(path)->getHeight();

	    if(m_texture_data == NULL){
	        std::cerr << "Pas de fichier image chargé pour la texture : " << path;
	    }

	    //CREATION DES VARIABLES OPENGL
	    glGenTextures(1, &m_texture_id);

	    //LOAD DES TEXTURES DANS OPEN GL
	    glBindTexture(GL_TEXTURE_2D, m_texture_id);

	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	    glTexImage2D(GL_TEXTURE_2D,  
	                 0,  
	                  GL_RGBA,  
	                  m_texture_width,  
	                  m_texture_height,  
	                  0,  
	                  GL_RGBA,  
	                  GL_FLOAT,  
	                  m_texture_data);

	    glBindTexture(GL_TEXTURE_2D, 0);

	}
}

void GlTexture::use(GLenum texture){

	glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

}

void GlTexture::stopUse(GLenum texture){

	glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, 0);

}