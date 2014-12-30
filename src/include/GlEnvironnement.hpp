#pragma once

#include <vector>

#include <glimac/FilePath.hpp>

#include "World.hpp"
#include "GlElement.hpp"
#include "GlLight.hpp"
#include "GlTexture.hpp"
#include "GlShader.hpp"
#include "GlUniform.hpp"
#include "GlGlobalUniform.hpp"


class GlEnvironnement{

private:

	std::vector<GlElement> m_elements;

	std::vector<GlTexture> m_textures;

	std::vector<GlLight>   m_lights;

	std::vector<GlShader>  m_shaders;

	GlGlobalUniform        m_global_uniforms;

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

	void addGlobalUniform(const GlGlobalUniform &gl_global_uniform);

	void updateViewMatrix(const glm::mat4 &view_matrix);

	void updateProjectionMatrix(const glm::mat4 &projection_matrix);

	void update(const World &world);


	void draw() const;

};