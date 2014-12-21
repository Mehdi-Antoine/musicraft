#pragma once
#include "Body.hpp"
#include "Inventory.hpp"
#include "State.hpp"

class Player{
private:
	Inventory m_inventory;
	State m_state;
	Body m_body;
  int m_dir_x;
  int m_dir_y;

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------CONSTRUCTOR--------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
public:
  Player();
  ~Player();

//--------------------------------------------------------------------------------------------------------------
//-----------------------------------------------GETTERS-SETTERS------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
  State getState() const;
  void setState(State state);

  Body getBody() const;
  void setBody(Body body);

//--------------------------------------------------------------------------------------------------------------
//---------------------------------------------------METHODS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
  void updatePlayer();
  void idle();
  void walk();
  void jump();
  void run();
  void jetpack();

  void moveFront(int t);
  void moveLeft(int t);


  bool catchCube(int cube);
  bool dropCube();
  bool deleteCube(int cube);
};
