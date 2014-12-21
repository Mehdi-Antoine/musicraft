#include "include/Player.hpp"
#include "include/Body.hpp"
#include "include/Physic.hpp"
#include <glimac/glm.hpp>
#include <vector>


// Constructors/Destructors
//  

Player::Player(){
	
}

Player::~Player(){
	
}

//  
// Methods
//  

	

Body Player::getBody() const{
	return this->m_body;
}
void Player::setBody(Body body){
	this->m_body = body;
}


void Player::updatePlayer(){
	std::vector<glm::vec3> forces;

	float coeffRunning=0;
	if(this->m_is_running) coeffRunning = 3.;
	else coeffRunning = 1.5;
	forces.push_back(glm::vec3(this->m_dir_x * coeffRunning, 0, this->m_dir_z * coeffRunning));

	float coeffJetpacking=0;
	if(this->m_is_flying) coeffJetpacking = 3.;
	else coeffJetpacking = 1.5;
	forces.push_back(glm::vec3(0, 1 * coeffJetpacking, coeffJetpacking/4));

	this->m_body.updateBody(forces);
}


void Player::jetpack(bool is_flying){
	this->m_is_flying = is_flying;
}
void Player::run(bool is_running){
	this->m_is_running = is_running;
}

void Player::moveFront(int t){
	this->m_dir_z = t;
}
void Player::moveLeft(int t){
	this->m_dir_x = t;
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


// Accessor methods
//  



// Other methods
//  
