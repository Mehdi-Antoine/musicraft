#pragma once

#include <vector>

#include "World.hpp"
#include "GlElement.hpp"
#include "GlLight.hpp"
#include "GlTexture.hpp"
#include "GlShader.hpp"
#include "GlUniform.hpp"


class GlEnvironnement{

private:

	std::vector<GlElement> m_elements;

	std::vector<GlTexture> m_textures;

	std::vector<GlLight>   m_lights;

	std::vector<GlShader>  m_shaders;

	GlUniform              m_projection_matrix,
			               m_view_matrix;

	const char*            m_dir_path;

public:

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

	GlEnvironnement(const char* dir_path);
	~GlEnvironnement();

//-------------------------------------------------FUNCTIONS----------------------------------------------------

	void addElement(const GlElement gl_element);

	void addLight(const GlLight gl_light);

	void addTexture(const GlTexture gl_texture);

	void addShader(const GlShader gl_shader);

	void draw() const;

	void update(const World &world);

};