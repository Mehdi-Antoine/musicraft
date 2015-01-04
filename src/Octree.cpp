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

char Octree::getCubeType(){
	return cubeType;
}

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
				centres.push_back(children[i]->coo);
			}
		}
	}
}

void Octree::genAllCoordinates(float taille){
	taille *= 0.5;
	for(int i = 0; i < 8; ++i){
		if(children[i] != NULL){
			children[i]->coo[0] = coo[0] + (((i&1)*2)-1)*taille*2;
			children[i]->coo[1] = coo[1] - ((((i&(1<<1))>>1)*2)-1)*taille*2;
			children[i]->coo[2] = coo[2] + ((((i&(1<<2))>>2)*2)-1)*taille*2;
			children[i]->genAllCoordinates(taille);
		}
	}
}

void Octree::getCubeType(char &result, Octree &subTree, int etage, const int taille, glm::vec3 &pos, const int profondeur){

	// Trouver les bonnes positions

	int left, near, top;

	(pos.x > subTree.coo[0]) ? left = 1 : left = 0;
	(pos.y > subTree.coo[1]) ? top = 1 : top = 0;
	(pos.z > subTree.coo[2]) ? near = 1 : near = 0;

	int index = (left|(top<<1))|(near<<2);

	std::cout << index << std::endl;
	//std::cout<< "etage : " << etage << " profondeur : " << profondeur << std::endl;
	//std::cout << "p: "<< pos[0] << " " <<pos[1] << " " << pos[2] << std::endl;
	

	if(subTree.children[index] != NULL){
		//std::cout << subTree.children[index]->coo[0] << " " <<subTree.children[index]->coo[1] << " " << subTree.children[index]->coo[2] << std::endl;
		if(etage < profondeur)
			Octree::getCubeType(result, *subTree.children[index], etage+1, taille*0.5, pos, profondeur);
		else{
			//std::cout << subTree.coo[0] << " " <<subTree.coo[1] << " " << subTree.coo[2] << std::endl;
			result = subTree.children[index]->cubeType;
		}
	}
	else{
		//std::cout << subTree.coo[0] << " " <<subTree.coo[1] << " " << subTree.coo[2] << std::endl;
		result = 0;
	}
}