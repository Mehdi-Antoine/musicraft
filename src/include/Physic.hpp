#pragma once

#include <vector>

#include <glimac/glm.hpp>

class Physic{

public:

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------FUNCTIONS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

 //static void updateVerlett(glm::vec3 &position, glm::vec3 &speed, const std::vector<glm::vec3> &forces);
  static void updateVerlett(glm::vec3 &position, glm::vec3 &speed, glm::vec3 &forces);

};