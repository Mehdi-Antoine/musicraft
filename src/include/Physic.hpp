#pragma once

#include <glimac/glm.hpp>
#include <vector>


//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

//void updateVerlett(glm::vec3 & position, glm::vec3 & speed, const glm::vec3 & forces);
void updateVerlett(glm::vec3 & position, glm::vec3 & speed, const glm::vec3 & forces, int m_dir_z, int m_dir_x, glm::vec3 left_vector, glm::vec3 front_vector);


