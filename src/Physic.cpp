#include "include/Physic.hpp"
#include <glimac/glm.hpp>

using namespace glm;

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void Physic::updateVerlett(vec3 &position, vec3 &speed, const std::vector<vec3> &forces){

    vec3 old_speed = speed;

    vec3 new_speed = vec3(0,0,0);

    vec3 new_position;

    vec3 sum_forces = vec3(0, 0, 0);

    float dt = 1.0 / 30.0;

    for(int i = 0; i < forces.size(); ++i){
    	sum_forces += forces[i];
    }

    new_speed = speed + sum_forces * dt;

    new_position = position + (old_speed + new_speed) * float(0.5 * dt);

    position = new_position;
    speed = new_speed;
}


