#pragma once

#include <GL/glew.h>

#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>

using namespace glimac;

class GlTexture{
private:

	std::unique_ptr<Image> m_texture_data;

	GLuint m_texture_id;
	
public:

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

	GlTexture();
	GlTexture(glimac::FilePath path);

	~GlTexture();

//-------------------------------------------------FUNCTIONS----------------------------------------------------

	void load(glimac::FilePath path);

	void use();

	void stopUse();

};