#include "include/Physic.hpp"
#include "include/Chunk.hpp"
#include <glimac/glm.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

/*void updateVerlett(glm::vec3 & position, glm::vec3 & speed, const glm::vec3 & forces, float dt){

    glm::vec3 new_speed = forces * dt;

    position = position + speed * float(100 * dt);

    speed = new_speed;
}*/

void updateVerlett(glm::vec3 & position, glm::vec3 & speed, const glm::vec3 & forces, float dt){

    glm::vec3 new_speed = forces * dt;

    position = position + (new_speed + speed) * float(0.5) * float(100 * dt);

    speed = new_speed;
}

void collisionSeeker(glm::vec3 &forces, const glm::vec3 &speed, const Chunk& chunk, const glm::vec3 &position){

	glm::vec3 next_speed = speed;

	glm::vec3 next_position = position;

	updateVerlett(next_position, next_speed, forces, 1.0/10);

	if(chunk.getCubeType(next_position) != EMPTY){
		std::cout << "COLLISION BIATCH !!" << std::endl;
		forces = forces + glm::vec3(0, - forces.y + 0.000001, 0);
	}

}




