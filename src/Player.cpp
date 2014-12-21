#include "include/Player.hpp"
#include "include/Body.hpp"
#include "include/State.hpp"
#include "include/Physic.hpp"
#include <glimac/glm.hpp>
#include <vector>


// Constructors/Destructors
//  

Player::Player(){
	this->idle();
}

Player::~Player(){
	
}

//  
// Methods
//  

State Player::getState() const{
	return this->m_state;
}
void Player::setState(State state){
	m_state = state;
}

Body Player::getBody() const{
	return this->m_body;
}
void Player::setBody(Body body){
	this->m_body = body;
}


void Player::updatePlayer(){
	std::vector<glm::vec3> forces;
	/*if(this->getState() == Status::idle){
		this->body.setAcceleration(glm::vec3(0,0,0));
		this->body.setOrientation(glm::vec3(0,0,0));
	}
	if(this->getState() == Status::walk){
		this->body.setAcceleration(glm::vec3(0,0,0));
	}
	if(this->getState() == Status::jump){
		f = glm::vec3();
	}
	if(this->getState() == Status::run){
		f = glm::vec3();
	}*/
	forces.push_back(glm::vec3(0,0,0));
	forces.push_back(glm::vec3(0,0,0));
	Physic::updateVerlett(glm::vec3(0,0,0), glm::vec3(0,0,0), forces);
}

void Player::idle(){
	this->setState(State::idle);
}
void Player::move(){
	this->setState(State::walk);
}
void Player::jump(){
	this->setState(State::jump);
}
void Player::run(){
	this->setState(State::run);
}
void Player::jetpack(){
	this->setState(State::jetpack);
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
