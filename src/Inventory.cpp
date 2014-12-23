#include "include/Inventory.hpp"
#include <iostream>


// Constructors/Destructors
//  

Inventory::Inventory()
	: m_max_size(50), m_current_cube(-1)
{}

Inventory::~Inventory(){
	
}

//  
// Methods
//  

bool Inventory::isEmpty() const{
	return this->m_list.empty();
}

int Inventory::size() const{
	int result = 0;
	for (int i = 0; i < this->m_list.size(); ++i)
	{
		result += this->m_list[i];
	}
	return result;
}

int Inventory::getCurrentCube(){
	return this->m_current_cube;
}

void Inventory::setCurrentCube(int cube){
	this->m_current_cube = cube;
}

bool Inventory::addCube(int cube){
	if (this->size() <= m_max_size){
		this->m_list[cube]++;
		std::cout << "Cube ajouté!" << std::endl;
		return true;
	}
	std::cout << "Ineventaire plein!" << std::endl;
	return false;
}

bool Inventory::removeCube(int cube){
	if(this->m_list[cube] > 0){
		this->m_list[cube]--;
		std::cout << "Cube supprimé!" << std::endl;
		return true;
	}
	std::cout << "Pas de cube!" << std::endl;
	return false;
}

bool Inventory::removeCurrentCube(){
	if(this->m_current_cube > -1){
		return this->removeCube(this->getCurrentCube());
	}
	return false;
}

// Accessor methods
//  


// Other methods
//  
