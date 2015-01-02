#pragma once

#include <GL/glew.h>

#include <glimac/glm.hpp>

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------CLASS GL_GLOBAL_UNIFORM--------------------------------------------
//-------------------------------------------------(VIRTUAL)----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

class GlGlobalUniform{

private:


public:

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

	GlGlobalUniform();
	virtual ~GlGlobalUniform() = 0;

//-------------------------------------------------FUNCTIONS----------------------------------------------------

	//virtual void init(const char* global_uniform_name) = 0;

	//virtual void attachProgram(GLuint program_id) = 0;

};

//--------------------------------------------------------------------------------------------------------------
//---------------------------------------CLASS GL_GLOBAL_UNIFORM_MATRIX-----------------------------------------
//----------------(contient les matrices View et Projection, ainsi que les coordonées de la caméra)-------------
//--------------------------------------------------------------------------------------------------------------

class GlGlobalUniformMatrix : public GlGlobalUniform{

private:

	const char*          m_global_uniform_name;

	glm::mat4            m_projection_matrix,
	                     m_view_matrix;

	glm::vec3            m_camera_position;

	GLuint               m_ubo;                         //Commun à tous les programmes glsl

	GLuint               m_ubo_binding_index;			//Commun à tous les programmes glsl

	std::vector <GLuint> m_global_uniform_block_index;  //Spécifique à chaque programme glsl

public:

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

	GlGlobalUniformMatrix();
	~GlGlobalUniformMatrix();

//-------------------------------------------------FUNCTIONS----------------------------------------------------

	void init(const char* global_uniform_name, int binding_index);

	void attachProgram(GLuint program_id);

	void updateProjectionMatrix(const glm::mat4 &projection_matrix);

	void updateViewMatrix(const glm::mat4 &view_matrix);

	void updateCameraPosition(const glm::vec3 &camera_position);

	void update(const glm::mat4 &projection_matrix, //Ordre à respecter dans les shaders
			    const glm::mat4 &view_matrix,
			    const glm::vec3 &camera_position); 

};

//--------------------------------------------------------------------------------------------------------------
//----------------------------------------CLASS GL_GLOBAL_UNIFORM_LIGHT-----------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

class GlGlobalUniformLight : public GlGlobalUniform{

private:

	const char*          m_global_uniform_name;

	glm::vec3            m_position,
						 m_intensity,
						 m_ks;

	float                m_shininess;

	GLuint               m_ubo;                         //Commun à tous les programmes glsl

	GLuint               m_ubo_binding_index;			//Commun à tous les programmes glsl

	std::vector <GLuint> m_global_uniform_block_index;  //Spécifique à chaque programme glsl

public:

//------------------------------------------------CONSTRUCTOR---------------------------------------------------

	GlGlobalUniformLight();
	~GlGlobalUniformLight();

//-------------------------------------------------FUNCTIONS----------------------------------------------------

	void init(const char* global_uniform_name, int binding_index);

	void attachProgram(GLuint program_id);

	void updatePosition(const glm::vec3 &position);

	void updateIntensity(const glm::vec3 &intensity);

	void updateKs(const glm::vec3 &ks);

	void updateShininess(float shininess);

	void update(const glm::vec3 position,  //Cet ordre est à respecter dans la structure qui récupère les valeurs dans le shader
				const glm::vec3 intensity, 
				const glm::vec3 ks, 
				float           shininess);

};