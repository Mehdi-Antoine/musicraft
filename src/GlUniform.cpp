#include <GL/glew.h>

#include <glimac/glm.hpp>

#include "include/GlUniform.hpp"


//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//----------------------------------------------CLASS GL_UNIFORM------------------------------------------------
//-------------------------------------------------(VIRTUAL)----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

GlUniform::GlUniform(){

}

GlUniform::~GlUniform(){
	
}


//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------CLASS GL_UNIFORM_VEC3---------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

GlUniformVec3::GlUniformVec3(GLuint program_id, const char* uniform_name){
	m_id = glGetUniformLocation(program_id, uniform_name);
	m_data = glm::vec3(0,0,0);
}

GlUniformVec3::GlUniformVec3() : m_id(-1) {

}

GlUniformVec3::~GlUniformVec3(){
	
}

//                                         --------------------------
//                                         ---------FUNCTIONS--------
//                                         --------------------------


void GlUniformVec3::init(GLuint program_id, const char* uniform_name){
	if(m_id == -1){
		m_id = glGetUniformLocation(program_id, uniform_name);
		m_data = glm::vec3(0,0,0);
	}
}

void GlUniformVec3::update(glm::vec3 new_data){
	m_data = new_data;
	glUniform3fv(m_id, 1, glm::value_ptr(m_data));
}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------CLASS GL_UNIFORM_MAT4---------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

GlUniformMat4::GlUniformMat4(GLuint program_id, const char* uniform_name){
	m_id = glGetUniformLocation(program_id, uniform_name);
	m_data = glm::mat4(1);
}

GlUniformMat4::GlUniformMat4() : m_id(-1) {

}

GlUniformMat4::~GlUniformMat4(){
	
}

//                                         --------------------------
//                                         ---------FUNCTIONS--------
//                                         --------------------------


void GlUniformMat4::init(GLuint program_id, const char* uniform_name){
	if(m_id == -1){
		m_id = glGetUniformLocation(program_id, uniform_name);
		m_data = glm::mat4(1);
	}
}

void GlUniformMat4::update(glm::mat4 new_data){
	m_data = new_data;
	glUniformMatrix4fv(m_id, 1, GL_FALSE, glm::value_ptr(m_data));
}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------CLASS GL_UNIFORM_FLOAT---------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

GlUniformFloat::GlUniformFloat(GLuint program_id, const char* uniform_name){
	m_id = glGetUniformLocation(program_id, uniform_name);
	m_data = 0;
}

GlUniformFloat::GlUniformFloat() : m_id(-1) {

}

GlUniformFloat::~GlUniformFloat(){
	
}

//                                         --------------------------
//                                         ---------FUNCTIONS--------
//                                         --------------------------


void GlUniformFloat::init(GLuint program_id, const char* uniform_name){
	if(m_id == -1){
		m_id = glGetUniformLocation(program_id, uniform_name);
		m_data = 0;
	}
}

void GlUniformFloat::update(float new_data){
	m_data = new_data;
	glUniform1f(m_id, m_data);
}

