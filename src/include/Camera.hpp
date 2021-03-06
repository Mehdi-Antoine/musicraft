#pragma once
#include <glimac/glm.hpp>

class Camera{

private:

	glm::vec3 m_Position,
			  m_FrontVector,
			  m_LeftVector,
			  m_UpVector;

	float m_fPhi,
		  m_fTeta;

public:

//--------------GETTERS------------------------//

	glm::vec3 getPosition() const;
	glm::vec3 & getPtPosition();
	glm::vec3 getFrontVector() const;
	glm::vec3 getLeftVector() const;
	glm::vec3 getUpVector() const;
	float getPhi() const;
	float getTheta() const;


//---------------------------CONSTRUCTOR-------------------------------------

	Camera();
	Camera(const Camera & camera);
	Camera(float x, float y, float z);

//----------------------------FUNCTIONS--------------------------------------

	void computeDirectionVectors();
	glm::mat4 getViewMatrix();
	//glm::vec3 getPosition();

	void moveLeft(float t);
	void moveFront(float t);

	void rotateLeft(float degrees);
	void rotateUp(float degrees);

	void setPosition(glm::vec3 position);

};