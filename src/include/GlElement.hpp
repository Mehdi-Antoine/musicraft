#pragma once

#include <GL/glew.h>
#include <vector>

#include <glimac/glm.hpp>

#include "GlShader.hpp"



enum VboType{ 
	POSITION, 
	COLOR
};


class GlElement{
private:

	int m_vertex_number;

	ShaderProgram m_shader_program;

	GLenum m_draw_mode;

	GLuint m_vao;

	GLuint m_color_vbo;
	GLuint m_position_vbo;

public:

//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------CONSTRUCTOR---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

	GlElement(std::vector<glm::vec3> &position_index, 
			  std::vector<glm::vec3> &color_index,  
			  ShaderProgram          shader_program,
			  GLenum                 draw_mode);

	~GlElement();

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------SETTERS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

	void setDrawMode(GLenum drawmode);

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------GETTERS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

	ShaderProgram getShaderProgram() const;

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

	void bindBuffer(VboType type) const;

	void unbindBuffer() const;

	void data(const std::vector<glm::vec3> &position_index, const std::vector<glm::vec3> &color_index);

	void draw() const;

	void update(const std::vector<glm::vec3> &position_index, const std::vector<glm::vec3> &color_index);

};