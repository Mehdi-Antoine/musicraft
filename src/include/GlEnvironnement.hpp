#pragma once

#include <vector>

#include <glimac/FilePath.hpp>

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

	FilePath               m_dir_path;

public:

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

	GlEnvironnement(FilePath dir_path);

	~GlEnvironnement();
//--------------------------------------------------GETTERS-----------------------------------------------------

	glm::mat4 getViewMatrix();

	glm::mat4 getProjectionMatrix();

	

//-------------------------------------------------FUNCTIONS----------------------------------------------------

	void addElement(const GlElement &gl_element);

	void addLight(const GlLight &gl_light);

	void addTexture(const GlTexture &gl_texture);	
	void addTextureVector(const std::vector<GlTexture> &texture_vector);

	void addShader(const GlShader &gl_shader);
	void addShaderVector(const std::vector<GlShader> &shader_vector);


	void updateViewMatrix(glm::mat4 view_matrix);

	void updateProjectionMatrix(glm::mat4 projection_matrix);

	void update(const World &world);


	void draw() const;

};