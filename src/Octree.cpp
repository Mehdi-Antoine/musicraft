#include "include/Octree.hpp"
#include <glimac/glm.hpp>
#include <iostream>
#include <vector>

Octree::Octree(){
	for(int i=0; i<8; ++i) 
		children[i] = NULL;
	cubeType = 0;
}

Octree::Octree(int type){
	for(int i=0; i<8; ++i) 
		children[i] = NULL;
	cubeType = type;
}

Octree::Octree(Octree** newChildren){
	for(int i= 0; i < 8; ++i){
		children[i] = newChildren[i];
	}
	cubeType = 0;
}

/*char Octree::getCubeType(){
	return cubeType;
}*/

bool Octree::isLeaf(){
	for(int i = 0; i < 8; ++i){
		if(children[i] != NULL)
			return false;
	}
	return true;
}

void Octree::insert(char type){
	//if(isLeaf()){
		cubeType = type;
		for(int i=0; i<8; ++i) 
			children[i] = NULL;
	//}
}

void Octree::insert(Octree &tree){
	for(int i= 0; i < 8; ++i){
		children[i] = tree.children[i];
	}
}

glm::vec3 Octree::getCoordinates(){
	return coo;
}

void Octree::getAllCoordinates(std::vector<glm::vec3> &centres, int etage, const int profondeur){
	for(int i = 0; i < 8; ++i){
		if(children[i] != NULL){
			if(etage < profondeur){
				children[i]->getAllCoordinates(centres, etage+1, profondeur);
			}
			else{
				//std::cout << children[i]->coo[0] << " " << children[i]->coo[1] << " " << children[i]->coo[2] << std::endl;
				centres.push_back(children[i]->coo);
			}
		}
	}
}

void Octree::genAllCoordinates(float taille){
	taille *= 0.5;
	for(int i = 0; i < 8; ++i){
		if(children[i] != NULL){
			children[i]->coo[0] = coo[0] + (((i&1)*2)-1)*taille;
			children[i]->coo[1] = coo[1] + ((((i&(1<<1))>>1)*2)-1)*taille;
			children[i]->coo[2] = coo[2] + ((((i&(1<<2))>>2)*2)-1)*taille;
			children[i]->genAllCoordinates(taille);
		}
	}
}

void Octree::getCubeType(char &result, glm::vec3 &pos, int etage, const int profondeur){

	int right, far, top;

	(pos.x > coo[0]) ? right = 1 : right = 0;
	(pos.y > coo[1]) ? top = 1 : top = 0;
	(pos.z > coo[2]) ? far = 1 : far = 0;

	int index = (right|(top<<1))|(far<<2);

	//std::cout << index << std::endl;
	//std::cout<< "etage : " << etage << " profondeur : " << profondeur << std::endl;
	//std::cout << "p: "<< pos[0] << " " <<pos[1] << " " << pos[2] << std::endl;
	if(children[index] == NULL)
		result = 0;
	else if(etage < profondeur){
		//std::cout << index << std::endl;
		children[index]->getCubeType(result, pos, etage+1, profondeur);
	}
	else{
		std::cout << "COLLISION" << std::endl;
		result = 1;
	}
}

void Octree::setCubeType(glm::vec3 pos, char type, int etage, const int profondeur){
	int right, far, top;

	(pos.x > coo[0]) ? right = 1 : right = 0;
	(pos.y > coo[1]) ? top = 1 : top = 0;
	(pos.z > coo[2]) ? far = 1 : far = 0;

	int index = (right|(top<<1))|(far<<2);

	if(children[index] == NULL)
		children[index] = new Octree();

	if(etage < profondeur){
		children[index]->setCubeType(pos, type, etage+1, profondeur);
	}
	else{
		children[index]->cubeType = type;
	}
}

