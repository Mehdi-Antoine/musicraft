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

//-------------------------------------------------CONSTRUCTOR--------------------------------------------------

  Player();
  Player(Player & player);
  Player(int name);
  ~Player();

//---------------------------------------------------GETTERS----------------------------------------------------

  Body& getBody();
  
  int getName() const;
  
  int getDirZ() const;
  
  int getDirX() const;
  
  bool getIsRunning() const;

  bool getIsFlying() const;
  Inventory& getInventory();

//---------------------------------------------------SETTERS----------------------------------------------------

  void setBody(Body body);

  void setName(int name);

  void setDirZ(int z);

  void setDirX(int x);

//---------------------------------------------------METHODS----------------------------------------------------

  void updatePlayer(World &world);

  void jetpack(bool is_flying);
  void run(bool is_running);

  void moveFront(int t);
  void moveLeft(int t);

  int foundCube(const World &world, glm::vec3 &target);
  int foundCube(const World &world, glm::vec3 &target, char &type);
  bool foundVoid(const World &world, glm::vec3 &target);

  glm::vec3 getTarget(float scale);

  void pickCube(World &world); //Méthode qui permet d'attraper un cube, le cherche dans le chunk etc.

  void addCube(World &world);

  void catchCube(char cube);
  bool dropCube(char & result);

};

