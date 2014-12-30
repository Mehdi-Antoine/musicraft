#pragma once

#include <GL/glew.h>

#include <glimac/glm.hpp>

class GlGlobalUniform{

private:

	const char*                m_global_uniform_name;

	glm::mat4            m_projection_matrix,
	                     m_view_matrix;

	GLuint               m_ubo;                         //Commun à tous les programmes glsl

	GLuint               m_ubo_binding_index;			//Commun à tous les programmes glsl

	std::vector <GLuint> m_global_uniform_block_index;  //Spécifique à chaque programme glsl

public:

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

	GlGlobalUniform();
	~GlGlobalUniform();

//-------------------------------------------------FUNCTIONS----------------------------------------------------

	void init(const char* global_uniform_name);

	void attachProgram(GLuint program_id);

	void updateProjectionMatrix(const glm::mat4 &projection_matrix);

	void updateViewMatrix(const glm::mat4 &view_matrix);

	void update(const glm::mat4 &projection_matrix, const glm::mat4 &view_matrix);

};