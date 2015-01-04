#pragma once
#include <glimac/glm.hpp>
#include <vector>

#include "World.hpp"
#include "Physic.hpp"
#include "Camera.hpp"
#include "Chunk.hpp"

using namespace glm;

class Body{
private:

  vec3 m_position;
  vec3 m_speed;
  vec3 m_acceleration;
  vec3 m_orientation;
  std::vector<vec3> m_hitbox_corners;
  Camera m_camera;

public:

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------GETTERS------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

vec3 getPosition() const;
vec3 getSpeed() const;
vec3 getAcceleration() const;
vec3 getOrientation() const;
std::vector<vec3> getHitboxCorners() const;
Camera & getCamera();



//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------SETTERS------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void setPosition(vec3 & position);
void setSpeed(vec3 & speed);
void setAcceleration(vec3 & acceleration);
void setOrientation(vec3 & orientation);
void setHitboxCorners(std::vector<vec3> & hitbox_corners);
void setCamera(Camera & camera);

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------METHODS------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

//void updateBody(vec3 forces);
void updateBody(float m_dir_x, float m_dir_z, float coeffRunning, float coeffJetpacking, World &world);


//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------CONSTRUCTOR--------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

  Body(vec3 position =  vec3(0, 0, 0),
       vec3 speed = vec3(0,0,0),
       vec3 acceleration = vec3(0,0,0),
       vec3 orientation = vec3(0,0,0)
  );

  Body(Body & body);

  ~Body();

};