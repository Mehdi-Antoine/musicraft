#include "include/Body.hpp"
#include "include/Physic.hpp"
#include <iostream>

// Constructors/Destructors
//  

using namespace glm;

Body::Body(vec3 position, vec3 speed, vec3 acceleration, vec3 orientation){

     float t = 2;
     float x = position.x;
     float y = position.y;
     float z = position.z;

	 m_position = position; 
	 m_speed = speed; 
	 m_acceleration = acceleration; 
	 m_orientation = orientation; 
      m_camera = Camera(x,y,z);
     
     std::vector<vec3> hitbox_corners;
     //base
     hitbox_corners.push_back(vec3(x-t/2, y-2*t-t/2, z));
     hitbox_corners.push_back(vec3(x+t/2, y-2*t-t/2, z));
     hitbox_corners.push_back(vec3(x-t/2, y-2*t-t/2, z-t));
     hitbox_corners.push_back(vec3(x+t/2, y-2*t-t/2, z-t));
     //top
     hitbox_corners.push_back(vec3(x-t/2, y+t/2, z));
     hitbox_corners.push_back(vec3(x+t/2, y+t/2, z));
     hitbox_corners.push_back(vec3(x-t/2, y+t/2, z-t));
     hitbox_corners.push_back(vec3(x+t/2, y+t/2, z-t));

     m_hitbox_corners = hitbox_corners;

}

Body::Body(Body & body){
     m_position = body.getPosition();
     m_speed = body.getSpeed();
     m_acceleration = body.getAcceleration();
     m_orientation = body.getOrientation();
     m_hitbox_corners = body.getHitboxCorners();
     m_camera = body.getCamera();
}


Body::~Body(){
	
}

//  
// Methods
//  

void Body::updateBody(vec3 forces, int m_dir_z, int m_dir_x){
     
     //updateVerlett(m_position, m_speed, forces);
     //m_camera.setPosition(m_position);

     //updateVerlett(m_camera.getPtPosition(), m_speed, forces);
     updateVerlett(m_camera.getPtPosition(), m_speed, forces, m_dir_z, m_dir_x, m_camera.getLeftVector(), m_camera.getFrontVector());
     //m_camera.setPosition(m_position);
     
     //m_orientation = m_camera.getFrontVector();



}

// Accessor methods
//  

vec3 Body::getPosition() const{
     return this->m_position;
}

vec3 Body::getSpeed() const{
     return this->m_speed;
}

vec3 Body::getAcceleration() const{
     return this->m_acceleration;
}

vec3 Body::getOrientation() const{
     return this->m_orientation;
}

std::vector<vec3> Body::getHitboxCorners() const{
     return this->m_hitbox_corners;
}

Camera & Body::getCamera(){
     return m_camera;
}



void Body::setPosition(vec3 & position){
     m_position = position;
}

void Body::setSpeed(vec3 & speed){
     m_speed = speed;
}

void Body::setAcceleration(vec3 & acceleration){
     m_acceleration = acceleration;
}

void Body::setOrientation(vec3 & orientation){
     m_orientation = orientation;
}

void Body::setHitboxCorners(std::vector<vec3> & hitbox_corners){
     m_hitbox_corners = hitbox_corners;
}

void Body::setCamera(Camera & camera){
     m_camera = camera;
}



// Other methods
//  



