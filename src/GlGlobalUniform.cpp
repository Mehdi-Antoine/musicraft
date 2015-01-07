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

void GlGlobalUniform::init(const char* global_uniform_name, int binding_index){

}

void GlGlobalUniform::attachProgram(GLuint program_id){

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
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STREAM_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    m_ubo_binding_index = binding_index; //commun à tous les programmes

    glBindBufferRange(GL_UNIFORM_BUFFER, m_ubo_binding_index, m_ubo, 0, 2 * sizeof(glm::mat4));

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

//--------------------------------------------------------------------------------------------------------------
//----------------------------------------CLASS GL_GLOBAL_UNIFORM_FLOAT-----------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

GlGlobalUniformFloat::GlGlobalUniformFloat(){

}

GlGlobalUniformFloat::~GlGlobalUniformFloat(){

}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void GlGlobalUniformFloat::init(const char* global_uniform_name, int binding_index){

    m_global_uniform_name = global_uniform_name;

    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(float), NULL, GL_STREAM_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    m_ubo_binding_index = binding_index; //commun à tous les programmes

    glBindBufferRange(GL_UNIFORM_BUFFER, m_ubo_binding_index, m_ubo, 0, sizeof(float));

}

void GlGlobalUniformFloat::attachProgram(GLuint program_id){

    GLuint block_index = glGetUniformBlockIndex(program_id, m_global_uniform_name);

    glUniformBlockBinding(program_id, block_index, m_ubo_binding_index);

    m_global_uniform_block_index.push_back(block_index);

}

void GlGlobalUniformFloat::updateShininess(float shininess){

    m_shininess = shininess;

    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float), &shininess);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

//--------------------------------------------------------------------------------------------------------------
//----------------------------------------CLASS GL_GLOBAL_UNIFORM_VEC4-----------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

GlGlobalUniformVec4::GlGlobalUniformVec4(){

}

GlGlobalUniformVec4::~GlGlobalUniformVec4(){

}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void GlGlobalUniformVec4::init(const char* global_uniform_name, int binding_index){

    m_global_uniform_name = global_uniform_name;

    glGenBuffers(1, &m_ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, 5 * sizeof(glm::vec4), NULL, GL_STREAM_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    m_ubo_binding_index = binding_index; //commun à tous les programmes

    glBindBufferRange(GL_UNIFORM_BUFFER, m_ubo_binding_index, m_ubo, 0, 5 * sizeof(glm::vec4));

}

void GlGlobalUniformVec4::attachProgram(GLuint program_id){

    GLuint block_index = glGetUniformBlockIndex(program_id, m_global_uniform_name);

    glUniformBlockBinding(program_id, block_index, m_ubo_binding_index);

    m_global_uniform_block_index.push_back(block_index);

}

void GlGlobalUniformVec4::updateLightPosition(const glm::vec4 &light_position){

    m_light_position = light_position;

    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(m_light_position));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void GlGlobalUniformVec4::updateLightIntensity(const glm::vec3 &light_intensity){

    m_light_intensity = glm::vec4(light_intensity, 0);

    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 1 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(m_light_intensity));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void GlGlobalUniformVec4::updateLightKs(const glm::vec3 &light_ks){

    m_light_ks = glm::vec4(light_ks, 0);

    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER,  2 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(m_light_ks));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}

void GlGlobalUniformVec4::updateCameraPosition(const glm::vec3 &camera_position){
    m_camera_position = glm::vec4(camera_position, 0);
    
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(m_camera_position));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void GlGlobalUniformVec4::updateCameraFrontVector(const glm::vec3 &front_vector){
    m_camera_front_vector = glm::vec4(front_vector, 0);
    
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, 4 * sizeof(glm::vec4), sizeof(glm::vec4), glm::value_ptr(m_camera_front_vector));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}