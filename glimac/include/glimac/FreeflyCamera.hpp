#pragma once
#include <glimac/glm.hpp>

class FreeflyCamera{

private:

	glm::vec3 m_Position,
			  m_FrontVector,
			  m_LeftVector,
			  m_UpVector;

	float m_fPhi,
		  m_fTeta;

public:

//---------------------------CONSTRUCTOR-------------------------------------

	FreeflyCamera();

//----------------------------FUNCTIONS--------------------------------------

	void computeDirectionVectors();
	glm::mat4 getViewMatrix();
	glm::vec3 getPosition();

	void moveLeft(float t);
	void moveFront(float t);

	void rotateLeft(float degrees);
	void rotateUp(float degrees);

};