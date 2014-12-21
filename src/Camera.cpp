#include "include/Camera.hpp"
#include <glimac/glm.hpp>

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