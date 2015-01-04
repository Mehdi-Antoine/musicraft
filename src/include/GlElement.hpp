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

	//OPEN GL
	GLenum m_draw_mode;

	GLuint m_vao;

	GLuint m_color_vbo;
	GLuint m_position_vbo;

	//DATA
	int m_vertex_number;

	std::vector<int>       m_empty_box;

	std::vector<glm::vec3> m_position_index;
	std::vector<glm::vec3> m_color_index;

	//OBJECTS FUNCTIONS
	void initVbo();
	void initVao();

public:

//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------CONSTRUCTOR---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

	GlElement(GLenum draw_mode = GL_POINTS);

	GlElement(std::vector<glm::vec3> &position_index, 
			  std::vector<glm::vec3> &color_index,  
			  GLenum                 draw_mode);

	~GlElement();

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------SETTERS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

	void setDrawMode(GLenum drawmode);

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------GETTERS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

	const glm::vec3& getPosition(int vector_index);

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

	void bindBuffer(VboType type) const;

	void unbindBuffer() const;

	int addEntry(const glm::vec3 &position, const glm::vec3 &color);

	void removeEntry(int index);

	void data(const std::vector<glm::vec3> &position_index, const std::vector<glm::vec3> &color_index);

	void subData(const glm::vec3 &position, const glm::vec3 &color, int index);

	void draw() const;

	void update(const std::vector<glm::vec3> &position_index, const std::vector<glm::vec3> &color_index);

};