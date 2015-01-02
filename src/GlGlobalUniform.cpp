#include <vector>

#include <GL/glew.h>

#include <glimac/glm.hpp>

#include "include/GlGlobalUniform.hpp"

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------CLASS GL_GLOBAL_UNIFORM--------------------------------------------
//-------------------------------------------------(VIRTUAL)----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

GlGlobalUniform::GlGlobalUniform(){

}

GlGlobalUniform::~GlGlobalUniform(){

}

//--------------------------------------------------------------------------------------------------------------
//---------------------------------------CLASS GL_GLOBAL_UNIFORM_MATRIX-----------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

GlGlobalUniformMatrix::GlGlobalUniformMatrix(){

}

GlGlobalUniformMatrix::~GlGlobalUniformMatrix(){

}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void GlGlobalUniformMatrix::init(const char* global_uniform_name, int binding_index){

	m_global_uniform_name = global_uniform_name;

    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4) * 2 + sizeof(glm::vec3), NULL, GL_STREAM_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    m_ubo_binding_index = binding_index; //commun à tous les programmes

    glBindBufferRange(GL_UNIFORM_BUFFER, m_ubo_binding_index, m_ubo, 0, sizeof(glm::mat4) * 2 + sizeof(glm::vec3));

}

void GlGlobalUniformMatrix::attachProgram(GLuint program_id){

	GLuint block_index = glGetUniformBlockIndex(program_id, m_global_uniform_name);

	glUniformBlockBinding(program_id, block_index, m_ubo_binding_index);

	m_global_uniform_block_index.push_back(block_index);

}

void GlGlobalUniformMatrix::updateProjectionMatrix(const glm::mat4 &projection_matrix){

    m_projection_matrix = projection_matrix;

	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection_matrix));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}


void GlGlobalUniformMatrix::updateViewMatrix(const glm::mat4 &view_matrix){

    m_view_matrix = view_matrix;
	
	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view_matrix));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void GlGlobalUniformMatrix::updateCameraPosition(const glm::vec3 &camera_position){
    m_camera_position = camera_position;
    
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::vec3), glm::value_ptr(camera_position));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void GlGlobalUniformMatrix::update(const glm::mat4 &projection_matrix, const glm::mat4 &view_matrix, const glm::vec3 &camera_position){

	updateProjectionMatrix(projection_matrix);
	updateViewMatrix(view_matrix);
    updateCameraPosition(camera_position);

}

//--------------------------------------------------------------------------------------------------------------
//----------------------------------------CLASS GL_GLOBAL_UNIFORM_LIGHT-----------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

GlGlobalUniformLight::GlGlobalUniformLight(){

}

GlGlobalUniformLight::~GlGlobalUniformLight(){

}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void GlGlobalUniformLight::init(const char* global_uniform_name, int binding_index){

    m_global_uniform_name = global_uniform_name;

    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::vec3) + sizeof(float), NULL, GL_STREAM_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    m_ubo_binding_index = binding_index; //commun à tous les programmes

    glBindBufferRange(GL_UNIFORM_BUFFER, m_ubo_binding_index, m_ubo, 0, 3 * sizeof(glm::vec3) + sizeof(float));

}

void GlGlobalUniformLight::attachProgram(GLuint program_id){

    GLuint block_index = glGetUniformBlockIndex(program_id, m_global_uniform_name);

    glUniformBlockBinding(program_id, block_index, m_ubo_binding_index);

    m_global_uniform_block_index.push_back(block_index);

}

void GlGlobalUniformLight::updatePosition(const glm::vec3 &position){

    m_position = position;

    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), glm::value_ptr(position));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void GlGlobalUniformLight::updateIntensity(const glm::vec3 &intensity){

    m_intensity = intensity;

    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec3), sizeof(glm::vec3), glm::value_ptr(intensity));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void GlGlobalUniformLight::updateKs(const glm::vec3 &ks){

    m_ks = ks;

    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER,  2 * sizeof(glm::vec3), sizeof(glm::vec3), glm::value_ptr(ks));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void GlGlobalUniformLight::updateShininess(float shininess){

    m_shininess = shininess;

    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER,  3 * sizeof(glm::vec3), sizeof(float), &shininess);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void GlGlobalUniformLight::update(const glm::vec3 position, const glm::vec3 intensity, const glm::vec3 ks, float shininess){

    updatePosition(position);
    updateIntensity(intensity);
    updateKs(ks);
    updateShininess(shininess);
}

