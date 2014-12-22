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

GlTexture::GlTexture(FilePath path){

    m_texture_data = loadImage(path);

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
                  m_texture_data->getWidth(),  
                  m_texture_data->getHeight(),  
                  0,  
                  GL_RGBA,  
                  GL_FLOAT,  
                  m_texture_data->getPixels());

    glBindTexture(GL_TEXTURE_2D, 0);

}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void GlTexture::load(FilePath path){
	if(m_texture_data == NULL){

		m_texture_data = loadImage(path);

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
	                  m_texture_data->getWidth(),  
	                  m_texture_data->getHeight(),  
	                  0,  
	                  GL_RGBA,  
	                  GL_FLOAT,  
	                  m_texture_data->getPixels());

	    glBindTexture(GL_TEXTURE_2D, 0);

	}
}

void GlTexture::use(){

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

}

void GlTexture::stopUse(){

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

}