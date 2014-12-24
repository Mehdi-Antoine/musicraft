#include "include/Camera.hpp"
#include <glimac/glm.hpp>
#include <iostream>

Camera::Camera(){
	m_Position = glm::vec3(5, 20, 5);
	m_fPhi = M_PI;
	m_fTeta = 0;
	Camera::computeDirectionVectors();
}

Camera::Camera(float x, float y, float z){
	m_Position = glm::vec3(x, y, z);
	m_fPhi = M_PI;
	m_fTeta = 0;
	Camera::computeDirectionVectors();
}

Camera::Camera(const Camera & camera){
     m_Position = camera.getPosition();
     m_FrontVector = camera.getFrontVector();
     m_LeftVector = camera.getLeftVector();
     m_UpVector = camera.getUpVector();
     m_fPhi = camera.getPhi();
     m_fTeta = camera.getTheta();
}

glm::vec3 Camera::getPosition() const{ return m_Position; }
glm::vec3 Camera::getFrontVector() const{ return m_FrontVector; }
glm::vec3 Camera::getLeftVector() const{ return m_LeftVector; }
glm::vec3 Camera::getUpVector() const{ return m_UpVector; }
float Camera::getPhi() const{ return m_fPhi; }
float Camera::getTheta() const{ return m_fTeta; }

glm::vec3 Camera::getPosition(){
	return m_Position;
}

void Camera::computeDirectionVectors(){

	//F =(cos(θ)sin(ϕ), sin(θ), cos(θ)cos(ϕ))
	m_FrontVector = glm::vec3(glm::cos(m_fTeta) * glm::sin(m_fPhi),
							  glm::sin(m_fTeta),
							  glm::cos(m_fTeta) * glm::cos(m_fPhi));

	//L =(sin(ϕ+π/2), 0, cos(ϕ+π/2))
	m_LeftVector =  glm::vec3(glm::sin(m_fPhi + M_PI / 2),
							  0,
							  glm::cos(m_fPhi + M_PI / 2));

	//U = F × L (produit vectoriel)
	m_UpVector =    glm::cross(m_FrontVector, m_LeftVector);
	//std::cout << "M_upVector: " << m_UpVector << std::endl;

}

void Camera::moveLeft(float t){
	m_Position += t * m_LeftVector;
}

void Camera::moveFront(float t){
	m_Position += t * m_FrontVector;
}

void Camera::rotateLeft(float degrees){
	m_fPhi += glm::radians(degrees);
	computeDirectionVectors();

}

void Camera::rotateUp(float degrees){
	m_fTeta += glm::radians(degrees);
	computeDirectionVectors();
}

glm::mat4 Camera::getViewMatrix(){
	return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
}

void Camera::setPosition(glm::vec3 position){
	m_Position = position;
}