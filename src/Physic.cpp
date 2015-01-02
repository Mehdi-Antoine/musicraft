#include "include/Physic.hpp"
#include <glimac/glm.hpp>
#include <vector>
#include <iostream>


//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

<<<<<<< HEAD

/*

void updateVerlett(glm::vec3 & position, glm::vec3 & speed, const glm::vec3 & forces, int m_dir_z, int m_dir_x, glm::vec3 left_vector, glm::vec3 front_vector){
=======
>>>>>>> chunk

void updateVerlett(glm::vec3 & position, glm::vec3 & speed, const glm::vec3 & forces, int m_dir_z, int m_dir_x, glm::vec3 left_vector, glm::vec3 front_vector){

    glm::vec3 newspeed = glm::vec3(0,0,0);
    glm::vec3 new_position;
    float dt = 1.0 / 30.0;

    newspeed = forces * float(dt);

    position = position + speed  * float(100 * dt);

    if(m_dir_x !=0) position += (float)m_dir_x * left_vector;
    if(m_dir_z !=0) position += (float)m_dir_z * front_vector;

    speed = newspeed;

    //std::cout << "force: " << forces.x << " " << forces.y << " " << forces.z << std::endl;
}

*/

void updateVerlett(glm::vec3 & position, glm::vec3 & speed, const glm::vec3 & forces, float dt){

	glm::vec3 force = glm::vec3(0,0,0);

    force += forces;

    glm::vec3 new_speed = forces * dt;

    position = position + speed * float(100 * dt);

    speed = new_speed;
}




