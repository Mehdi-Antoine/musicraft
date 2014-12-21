#pragma once
#include "Body.hpp"
#include "Inventory.hpp"
#include "State.hpp"

class Player{
private:
	Inventory m_inventory;
	State m_state;
	Body m_body;

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------CONSTRUCTOR--------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
public:
  Player();
  ~Player();

  State getState() const;
  void setState(State state);

  Body getBody() const;
  void setBody(Body body);

//--------------------------------------------------------------------------------------------------------------
//---------------------------------------------------METHODS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
  void updatePlayer();
  void idle();
  void move();
  void jump();
  void run();
  void jetpack();
  bool catchCube(int cube);
  bool dropCube();
  bool deleteCube(int cube); 
};
