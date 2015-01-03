#pragma once

#include "Chunk.hpp"

#include <glimac/glm.hpp>
#include <vector>


//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void updateVerlett(glm::vec3 & position, glm::vec3 & speed, const glm::vec3 & forces, float dt = 1.0/30.0);
//void updateVerlett(glm::vec3 & position, glm::vec3 & speed, const glm::vec3 & forces, int m_dir_z, int m_dir_x, glm::vec3 left_vector, glm::vec3 front_vector);

void collisionSeeker(glm::vec3 &forces, const glm::vec3 &speed, const Chunk& chunk, const glm::vec3 &position);