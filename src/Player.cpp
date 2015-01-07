#include "include/Player.hpp"
#include "include/Body.hpp"
#include "include/World.hpp"
#include "include/Physic.hpp"
#include <glimac/glm.hpp>
#include <vector>
#include <iostream>

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------------CONSTRUCTOR--------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

Player::Player(){
	m_dir_x = 0;
	m_dir_z = 0;
	m_is_running = false;
	m_is_flying = false;
	m_name = 47;
}

Player::Player(Player & player){
	m_dir_x = player.getDirX();
	m_dir_z = player.getDirZ();
	m_is_running = player.getIsRunning();
	m_is_flying = player.getIsFlying();
	m_name = player.getName();
	m_body = player.getBody();

}

Player::Player(int name){
	m_dir_x = 0;
	m_dir_z = 0;
	m_is_running = false;
	m_is_flying = false;
	m_name = name;
}

Player::~Player(){
	
}

//--------------------------------------------------------------------------------------------------------------
//---------------------------------------------------GETTERS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

Body& Player::getBody(){
	return m_body;
}

int Player::getName() const{
	return m_name;
}

int Player::getDirZ() const{
	return m_dir_z;
}

int Player::getDirX() const{
	return m_dir_x;
}

bool Player::getIsRunning() const{
	return m_is_running;
}

bool Player::getIsFlying() const{
	return m_is_flying;
}

//--------------------------------------------------------------------------------------------------------------
//---------------------------------------------------SETTERS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void Player::setBody(Body body){
	m_body = body;
}

void Player::setName(int name){
	m_name = name;
}

void Player::setDirZ(int z){
	m_dir_z = z;
}

void Player::setDirX(int x){
	m_dir_x = x;
}

//--------------------------------------------------------------------------------------------------------------
//---------------------------------------------------METHODS----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

void Player::updatePlayer(World &world){
	
	float coeffRunning=0;
	if(m_is_running) coeffRunning = 2; 
	else coeffRunning = 1;

    float coeffJetpacking=0;
	if(m_is_flying) coeffJetpacking = 2;
	else coeffJetpacking = 0;

	m_body.updateBody(m_dir_x, m_dir_z, coeffRunning, coeffJetpacking, world);

}


void Player::jetpack(bool is_flying){
	this->m_is_flying = is_flying;
}

void Player::run(bool is_running){
	this->m_is_running = is_running;
}

void Player::moveFront(int t){
	setDirZ(t);
}

void Player::moveLeft(int t){
	setDirX(t);
}

glm::vec3 Player::getTarget(float scale){
	
	glm::vec3 target;

	glm::vec3 front_vector = m_body.getCamera().getFrontVector();
	glm::vec3 camera_position = m_body.getCamera().getPosition();

	//std::cout << glm::length(front_vector) << std::endl;

	target = camera_position +  scale * front_vector;
	return target;
}

int Player::foundCube(const World &world, glm::vec3 &target){

	float scale = 0.5;
	int i = 0;
	bool found_cube = false;

	do{

		scale += i;

		target  = getTarget(scale);

		//std::cout << "target length" << glm::length(getTarget(1)) << std::endl;

		if(world.getCubeType(target) != EMPTY){
			found_cube = true;
		}
		
		++i;

	}while(found_cube == false && i < 4);

	if(found_cube){
		std::cout << "CUBE AT COORD : " << target << std::endl;
		std::cout << "i : " << i << std::endl;
		return i;
	}
	
	return -1;

}

void Player::foundPreviousVoid(const World &world, glm::vec3 &target){
	float scale = 0.99;
	int i = 0;
	bool found_void = false;

	do{

		scale -= 0.01;

		target  *= scale;

		if(world.getCubeType(target) == 0){ //EMPTY
			found_void = true;
		}
		
		++i;

		std::cout << i << std::endl;

	}while(found_void == false && scale > 0);

	if(found_void){
		std::cout << "VOID AT COORD : " << target << std::endl;
	}
	
}


void Player::pickCube(World &world){

	glm::vec3 target;

	if(foundCube(world, target) != -1){
		std::cout << " PICKED"<< std::endl;
		world.setCubeType(target, EMPTY);
	}

}

 
void Player::addCube(World &world){

	glm::vec3 target;

	int i = foundCube(world, target);

	if(i != -1){
		std::cout << " ADDED"<< std::endl;

		foundPreviousVoid(world, target);

		if(glm::length(target) > 3){
			world.setCubeType(target, BASIC);
		}
		
		
	}
	

}

bool Player::catchCube(int cube){
	return this->m_inventory.addCube(cube);
}

bool Player::dropCube(){
	return this->m_inventory.removeCurrentCube();
}

bool Player::deleteCube(int cube){
	return this->m_inventory.removeCube(cube);
}
 

