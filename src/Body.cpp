#include "include/Body.hpp"

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


Body::~Body(){
	
}

//  
// Methods
//  


// Accessor methods
//  


// Other methods
//  



