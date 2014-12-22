#include "include/GlElement.hpp"
#include <vector>
#include <glimac/glm.hpp>
#include <GL/glew.h>

//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------CONSTRUCTOR---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

GlElement::GlElement(std::vector<glm::vec3> &position_index, std::vector<glm::vec3> &color_index, char* shader_type){

	m_size = position_index.size();

	m_shaders = ShaderProgram(position_index, color_index, shader_type);

    glGenBuffers(1, &m_color_vbo);
    glGenBuffers(1, &m_position_vbo);
    
    bind(COLOR);
    glBufferData(GL_ARRAY_BUFFER, m_size * sizeof(glm::vec3), m_color_vbo, GL_STATIC_DRAW);
    unbind();

    bind(POSITION);
    glBufferData(GL_ARRAY_BUFFER, m_size * sizeof(glm::vec3), m_position_vbo, GL_STATIC_DRAW);
    unbind();

    glGenVertexArrays(1, &m_vao);

    glBindVertexArray(m_vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR = 1;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    glBindBuffer(GL_ARRAY_BUFFER, m_position_vbo);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (const GLvoid*)(0*sizeof(GL_FLOAT)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, m_color_vbo);  
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (const GLvoid*)(0*sizeof(GL_FLOAT)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

}

GlElement::~GlElement(){

	glDeleteBuffers(1, &m_color_vbo);
    glDeleteBuffers(1, &m_position_vbo);
    glDeleteVertexArrays(1, &m_vao);

}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------SETTERS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void GlElement::setDrawMode(GLenum drawmode){
	m_draw_mode = drawmode;
}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void GlElement::bind(vboType type){

	glBindVertexArray(m_vao);

	switch (type) {
		case COLOR:
		 	glBindBuffer(GL_ARRAY_BUFFER, m_color_vbo);
		break;

		case POSITION:
			glBindBuffer(GL_ARRAY_BUFFER, m_position_vbo);
		break;

		default:

		break;
	}

}

void GlElement::unbind(){

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void GlElement::data(std::vector<glm::vec3> position_index, std::vector<glm::vec3> color_index){

	m_size = position_index.size();

	bind(COLOR);
	glBufferData(GL_ARRAY_BUFFER, m_size * sizeof(glm::vec3), m_color_vbo, GL_STATIC_DRAW);
	unbind();

	bind(POSITION);
	glBufferData(GL_ARRAY_BUFFER, m_size * sizeof(glm::vec3), m_color_vbo, GL_STATIC_DRAW);
	unbind();

}

void GlElement::draw(){

	glBindVertexArray(m_vao);

	glDrawArrays(m_draw_mode, 0, m_size);

	glBindVertexArray(0);

}