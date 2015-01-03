#include <vector>
#include <GL/glew.h>

#include <glimac/glm.hpp>

#include "include/GlElement.hpp"
#include "include/GlShader.hpp"

//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------CONSTRUCTOR---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

GlElement::GlElement(std::vector<glm::vec3> &position_index, std::vector<GLubyte> &type_index, ShaderProgram shader_program, GLenum draw_mode){

	setDrawMode(draw_mode);

	m_vertex_number = position_index.size();

	m_shader_program = shader_program;

    glGenBuffers(1, &m_type_vbo);
    glGenBuffers(1, &m_position_vbo);
    
    bindBuffer(POSITION);
    glBufferData(GL_ARRAY_BUFFER, m_vertex_number * sizeof(glm::vec3), position_index.data(), GL_STATIC_DRAW);
    unbindBuffer();

    bindBuffer(TYPE);
    glBufferData(GL_ARRAY_BUFFER, m_vertex_number * sizeof(GLubyte), type_index.data(), GL_STATIC_DRAW);
    unbindBuffer();

    glGenVertexArrays(1, &m_vao);

    glBindVertexArray(m_vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_TYPE = 1;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_TYPE);

    bindBuffer(POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (const GLvoid*)(0*sizeof(GL_FLOAT)));
    unbindBuffer();

    bindBuffer(TYPE); 
    glVertexAttribPointer(VERTEX_ATTR_TYPE, 1, GL_BYTE, GL_FALSE, sizeof(GLubyte), (const GLvoid*)(0*sizeof(GL_FLOAT)));
    unbindBuffer();

    glBindVertexArray(0);

}

GlElement::~GlElement(){

	glDeleteBuffers(1, &m_type_vbo);
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
//--------------------------------------------------GETTERS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

ShaderProgram GlElement::getShaderProgram() const{
	return m_shader_program;
}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void GlElement::bindBuffer(VboType type) const{

	glBindVertexArray(m_vao);

	switch (type) {
		case TYPE:
		 	glBindBuffer(GL_ARRAY_BUFFER, m_type_vbo);
		break;

		case POSITION:
			glBindBuffer(GL_ARRAY_BUFFER, m_position_vbo);
		break;

		default:

		break;
	}

}

void GlElement::unbindBuffer() const{

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void GlElement::data(const std::vector<glm::vec3> &position_index, const std::vector<GLubyte> &type_index){

	m_vertex_number = position_index.size();

	bindBuffer(TYPE);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_number * sizeof(GLubyte), type_index.data(), GL_STATIC_DRAW);
	unbindBuffer();

	bindBuffer(POSITION);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_number * sizeof(glm::vec3), position_index.data(), GL_STATIC_DRAW);
	unbindBuffer();

}

void GlElement::draw() const{

	glBindVertexArray(m_vao);

	glDrawArrays(m_draw_mode, 0, m_vertex_number);

	glBindVertexArray(0);

}