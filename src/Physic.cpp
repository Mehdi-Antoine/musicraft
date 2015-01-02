#include "include/Physic.hpp"
#include <glimac/glm.hpp>
#include <vector>
#include <iostream>


//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void updateVerlett(glm::vec3 & position, glm::vec3 & speed, const glm::vec3 & forces, float dt){

	glm::vec3 force = glm::vec3(0,0,0);

    force += forces;

    glm::vec3 new_speed = forces * dt;

    position = position + speed * float(100 * dt);

    speed = new_speed;
}




