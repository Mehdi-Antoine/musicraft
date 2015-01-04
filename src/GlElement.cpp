#include <vector>
#include <GL/glew.h>

#include <glimac/glm.hpp>

#include "include/GlElement.hpp"

//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------CONSTRUCTOR---------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

GlElement::GlElement(GLenum draw_mode){
	setDrawMode(draw_mode);

	m_vertex_number = 0;
	
	initVbo();

    initVao();
}


GlElement::GlElement(std::vector<glm::vec3> &position_index, std::vector<glm::vec3> &color_index, GLenum draw_mode){

	setDrawMode(draw_mode);

	m_vertex_number = position_index.size();

	m_position_index = position_index;
	m_color_index = color_index;

    initVbo();

    bindBuffer(COLOR);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_number * sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
	unbindBuffer();

	bindBuffer(POSITION);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_number * sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
	unbindBuffer();
    
    bindBuffer(POSITION);
    glBufferData(GL_ARRAY_BUFFER, m_vertex_number * sizeof(glm::vec3), position_index.data(), GL_STATIC_DRAW);
    unbindBuffer();

    bindBuffer(COLOR);
    glBufferData(GL_ARRAY_BUFFER, m_vertex_number * sizeof(glm::vec3), color_index.data(), GL_STATIC_DRAW);
    unbindBuffer();

    initVao();

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
//--------------------------------------------------GETTERS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

const glm::vec3& GlElement::getPosition(int vector_index){

	return m_position_index[vector_index];

}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void GlElement::initVbo(){
	glGenBuffers(1, &m_color_vbo);
    glGenBuffers(1, &m_position_vbo);
}

void GlElement::initVao(){

	glGenVertexArrays(1, &m_vao);

    glBindVertexArray(m_vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR = 1;

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

    bindBuffer(POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (const GLvoid*)(0*sizeof(GL_FLOAT)));
    unbindBuffer();

    bindBuffer(COLOR); 
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (const GLvoid*)(0*sizeof(GL_FLOAT)));
    unbindBuffer();

    glBindVertexArray(0);

}

void GlElement::bindBuffer(VboType type) const{

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

void GlElement::unbindBuffer() const{

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void GlElement::data(const std::vector<glm::vec3> &position_index, const std::vector<glm::vec3> &color_index){

	m_vertex_number = position_index.size();

	bindBuffer(COLOR);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_number * sizeof(glm::vec3), color_index.data(), GL_STATIC_DRAW);
	unbindBuffer();

	bindBuffer(POSITION);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_number * sizeof(glm::vec3), position_index.data(), GL_STATIC_DRAW);
	unbindBuffer();

}

void GlElement::subData(const glm::vec3 &position, const glm::vec3 &color, int index){

	bindBuffer(COLOR);
	glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(GL_FLOAT), sizeof(glm::vec3), glm::value_ptr(color));
	unbindBuffer();

	bindBuffer(POSITION);
	glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(GL_FLOAT), sizeof(glm::vec3), glm::value_ptr(position));
	unbindBuffer();

}

int GlElement::addEntry(const glm::vec3 &position, const glm::vec3 &color){

	int vector_index = 0;

	if(m_empty_box.size() == 0){
		m_position_index.push_back(position);
		m_color_index.push_back(color);

		vector_index = m_position_index.size() - 1;
	}
	else{
		vector_index = m_empty_box.back();

		m_position_index[vector_index] = position;

		m_empty_box.pop_back();
	}

	m_vertex_number = m_position_index.size();

	subData(position, color, vector_index);
	
	return vector_index;
}

void GlElement::removeEntry(int vector_index){
	m_empty_box.push_back(vector_index);
	subData(glm::vec3(0,0,0), glm::vec3(0,0,0), vector_index);
}

void GlElement::draw() const{

	glBindVertexArray(m_vao);

	glDrawArrays(m_draw_mode, 0, m_vertex_number);

	glBindVertexArray(0);

}

void GlElement::update(const std::vector<glm::vec3> &position_index, const std::vector<glm::vec3> &color_index){

	data(position_index, color_index);

}