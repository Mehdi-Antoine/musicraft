#pragma once

#include <GL/glew.h>

#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>

using namespace glimac;

class GlTexture{
private:

	glm::vec4* m_texture_data;

	unsigned int m_texture_width,
		         m_texture_height;

	GLuint m_texture_id;
	
public:

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

	GlTexture();
	GlTexture(const GlTexture& gl_texture);
	GlTexture(glimac::FilePath path);

	~GlTexture();

//--------------------------------------------------GETTERS-----------------------------------------------------

	GLuint getTextureId() const;

	glm::vec4* getTextureData() const;
	
	unsigned int getTextureWidth() const;
	unsigned int getTextureHeight() const;

//-------------------------------------------------FUNCTIONS----------------------------------------------------

	void load(glimac::FilePath path);

	void use(GLenum texture); //GL_TEXTURE0, GL_TEXTURE1, ...

	void stopUse(GLenum texture); //GL_TEXTURE0, GL_TEXTURE1, ...

};