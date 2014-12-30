#include <vector>

#include <GL/glew.h>

#include <glimac/glm.hpp>

#include "include/GlGlobalUniform.hpp"


GlGlobalUniform::GlGlobalUniform(){

}

GlGlobalUniform::~GlGlobalUniform(){

}

void GlGlobalUniform::init(const char* global_uniform_name){

	m_global_uniform_name = global_uniform_name;

    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2, NULL, GL_STREAM_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    m_ubo_binding_index = 1; //commun à tous les programmes

    glBindBufferRange(GL_UNIFORM_BUFFER, m_ubo_binding_index, m_ubo, 0, sizeof(glm::mat4) * 2);

}

void GlGlobalUniform::attachProgram(GLuint program_id){

	GLuint block_index = glGetUniformBlockIndex(program_id, m_global_uniform_name);

	glUniformBlockBinding(program_id, block_index, m_ubo_binding_index);

	m_global_uniform_block_index.push_back(block_index);

}

void GlGlobalUniform::updateProjectionMatrix(const glm::mat4 &projection_matrix){

	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection_matrix));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}


void GlGlobalUniform::updateViewMatrix(const glm::mat4 &view_matrix){
	
	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view_matrix));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void GlGlobalUniform::update(const glm::mat4 &projection_matrix, const glm::mat4 &view_matrix){

	updateProjectionMatrix(projection_matrix);
	updateViewMatrix(view_matrix);

}

