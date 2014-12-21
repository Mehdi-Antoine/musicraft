#include "include/Physic.hpp"
#include <glimac/glm.hpp>
#include <vector>

//using namespace glm;

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void Physic::updateVerlett(glm::vec3 position, glm::vec3 speed, const std::vector<glm::vec3> forces){


    glm::vec3 old_speed = speed;

    glm::vec3 new_speed = glm::vec3(0,0,0);

    glm::vec3 new_position;

    glm::vec3 sum_forces = glm::vec3(0, 0, 0);

    float dt = 1.0 / 30.0;

    for(int i = 0; i < forces.size(); ++i){
    	sum_forces += forces[i];
    }

    new_speed = speed + sum_forces * dt;

    new_position = position + (old_speed + new_speed) * float(0.5 * dt);

    position = new_position;
    speed = new_speed;
}


