#pragma once
#include "Body.hpp"
#include "World.hpp"
#include "Inventory.hpp"



class Player{
private:
	Inventory m_inventory;

	Body m_body;

  int m_dir_z;
  int m_dir_x;
  bool m_is_running;
  bool m_is_flying;
  int m_name;

public:
//--------------------------------------------------------------------------------------------------------------
//-----------------------------------------------GETTERS-SETTERS------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

  Body& getBody();
  void setBody(Body body);
  int getName() const;
  void setName(int name);
  int getDirZ() const;
  void setDirZ(int z);
  int getDirX() const;
  void setDirX(int x);
  bool getIsRunning() const;
  bool getIsFlying() const;
  Inventory getInventory();

//--------------------------------------------------------------------------------------------------------------
//---------------------------------------------------METHODS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
  void updatePlayer(World &world);

  void jetpack(bool is_flying);
  void run(bool is_running);

  void moveFront(int t);
  void moveLeft(int t);

  bool catchCube(int cube);
  bool dropCube();
  bool deleteCube(int cube);

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------CONSTRUCTOR--------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

  Player();
  Player(Player & player);
  Player(int name);
  ~Player();

};

