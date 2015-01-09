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

Inventory & Player::getInventory(){
	return m_inventory;
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

	target = camera_position +  scale * front_vector;
	return target;
}


int Player::foundCube(const World &world, glm::vec3 &target,char & type){

	float scale = 0.01;
	float i = 0.;
	bool found_cube = false;
	float distance;
	glm::vec3 camera_position = m_body.getCamera().getPosition();

	do{

		scale = scale + i;

		target  = getTarget(scale);

		if(world.getCubeType(target) != EMPTY){
			found_cube = true;
			type = world.getCubeType(target);
		}
		
		i = i + 0.01;
		//distance = dot(target - camera_position ,target - camera_position);
		distance = glm::distance(target, camera_position);

	}while(found_cube == false && distance < 4);
	//}while(found_cube == false && sqrt(distance) < 2);

	if(found_cube){
		//std::cout << "CUBE AT COORD : " << target << std::endl;
		return i;
	}
	
	return -1;

}

bool Player::foundVoid(const World &world, glm::vec3 &target){
	float scale = 1.0f;
	bool found_void = false;

	do{

		if(world.getCubeType(target*scale) == EMPTY){
			found_void = true;
			target *= scale;
		}

		scale -= 0.01;
	}while(found_void == false && scale > 0);

	if(found_void){
		std::cout << "VOID AT COORD : " << target << std::endl;
	}

	return found_void;
	
}


void Player::pickCube(World &world){

	glm::vec3 target;
	char type;

	if(foundCube(world, target, type) != -1){
		std::cout << " PICKED"<< std::endl;
		world.setCubeType(target, EMPTY);
		catchCube(type);
		std::cout << "Cube ajouté dans inventaire!"<< std::endl;
	}

}


void Player::addCube(World &world){

	glm::vec3 target;
	char type;
	bool found_void = false;

	int i = foundCube(world, target, type);

	if(i != -1){

		do{
			target *= 0.995;

			if(world.getCubeType(target) == EMPTY){
				found_void = true;
			}

		}while(found_void == false && glm::length(target) > 0.1);

		if(found_void == true){

			if(m_inventory.removeCurrentCube(type)){
				world.setCubeType(target, type);
				std::cout << " ADDED"<< std::endl;
			}

		}
		


	}
	

}

// void Player::addCube(World &world){

// 	glm::vec3 target;
// 	char type;
// 	bool found_void = false;

// 	int i = foundCube(world, target, type);

// 	if(foundVoid(world, target)){
// 		std::cout << " OUI"<< std::endl;
// 		target = Chunk::getPositionIndexed(target);
// 		if(world.getCubeType(target + glm::vec3(1,0,0)) != EMPTY
// 			|| world.getCubeType(target + glm::vec3(-1,0,0)) != EMPTY
// 			|| world.getCubeType(target + glm::vec3(0,1,0)) != EMPTY
// 			|| world.getCubeType(target + glm::vec3(0,-1,0)) != EMPTY
// 			|| world.getCubeType(target + glm::vec3(0,0,1)) != EMPTY
// 			|| world.getCubeType(target + glm::vec3(0,0,-1)) != EMPTY){
// 			if(m_inventory.removeCurrentCube(type)){
// 				world.setCubeType(target, type);
// 				std::cout << " ADDED"<< std::endl;
// 			}
// 		}
		

		
		
// 	}
	

// }

void Player::catchCube(char cube){
	m_inventory.addCube(cube);
}

bool Player::dropCube(char & result){
	return this->m_inventory.removeCurrentCube(result);
}
 

