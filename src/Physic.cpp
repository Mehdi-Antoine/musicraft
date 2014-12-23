#include "include/Physic.hpp"
#include <glimac/glm.hpp>
#include <vector>
#include <iostream>


//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void updateVerlett(glm::vec3 & position, glm::vec3 & speed, const glm::vec3 & forces){


    glm::vec3 newspeed = glm::vec3(0,0,0);
    glm::vec3 new_position;
    float dt = 1.0 / 30.0;

    newspeed = forces * float(dt);

    position = position + speed  * float(100 * dt);
    speed = newspeed;

    //std::cout << "force: " << forces.x << " " << forces.y << " " << forces.z << std::endl;
}


