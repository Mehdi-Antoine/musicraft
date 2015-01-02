#pragma once

#include <vector>

#include <glimac/FilePath.hpp>

#include "World.hpp"
#include "GlElement.hpp"
#include "GlTexture.hpp"
#include "GlShader.hpp"
#include "GlUniform.hpp"
#include "GlGlobalUniform.hpp"


class GlEnvironnement{

private:

	std::vector<GlElement> m_elements;

	std::vector<GlTexture> m_textures;

	std::vector<GlShader>  m_shaders;

	GlGlobalUniformMatrix  m_global_matrix;
	
	GlGlobalUniformLight   m_global_light;

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

	void addTexture(const GlTexture &gl_texture);	
	void addTextureVector(const std::vector<GlTexture> &texture_vector);

	void addShader(const GlShader &gl_shader);
	void addShaderVector(const std::vector<GlShader> &shader_vector);

	void addGlobalUniformMatrix(const GlGlobalUniformMatrix &global_matrix);

	void updateViewMatrix(const glm::mat4 &view_matrix);

	void updateProjectionMatrix(const glm::mat4 &projection_matrix);

	void update(const World &world);


	void draw() const;

};