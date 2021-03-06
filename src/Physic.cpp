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

	glm::vec3 next_speed;
	glm::vec3 next_position;

	//Collision en y

	next_position = position;
	next_speed = speed;

	updateVerlett(next_position, next_speed, forces, 1.0/10.0);
	next_position.x = position.x;
	next_position.z = position.z;

	if(chunk.getCubeType(next_position) != EMPTY){
		//std::cout << "COLLISION Y" << std::endl;
		//std::cout << "position = " << position << std::endl;
		forces = forces + glm::vec3(0, - forces.y , 0);
	}

	//Collision en x

	next_position = position;
	next_speed = speed;

	updateVerlett(next_position, next_speed, forces, 1.0/10.0);
	next_position.y = position.y;
	next_position.z = position.z;

	if(chunk.getCubeType(next_position) != EMPTY){
		/*std::cout << "COLLISION X" << std::endl;
		std::cout << "x position = " << position << std::endl;
		std::cout << "x next pos = " << next_position << std::endl;*/
		forces = forces + glm::vec3(- forces.x , 0, 0);
	}

	//Collision en z

	next_position = position;
	next_speed = speed;

	updateVerlett(next_position, next_speed, forces, 1.0/10.0);
	next_position.x = position.x;
	next_position.y = position.y;
	//std::cout << "z current position = " << position.z << std::endl;
	//std::cout << "z current next pos = " << next_position.z << std::endl;

	if(chunk.getCubeType(next_position) != 0){
		/*std::cout << "COLLISION Z" << std::endl;
		std::cout << "z position = " << position << std::endl;
		std::cout << "z next pos = " << next_position << std::endl;*/


		float delta_position = next_position.z - position.z;

		//std::cout << "delta position = " << delta_position << std::endl;

		float signe;
		
		forces = forces + glm::vec3(0, 0, - forces.z );
	}

}




