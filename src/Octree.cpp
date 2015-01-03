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
	if(isLeaf()){
		cubeType = type;
	}
}

void Octree::insert(Octree &tree){
	for(int i= 0; i < 8; ++i){
		children[i] = tree.children[i];
	}
}

void Octree::getAllCoordinates(std::vector<glm::vec3> &centres){
	if(cubeType != 0){
		std::cout << "x : " << coo[0] << " y : "<< coo[1] << " z : " << coo[2] << std::endl;
		centres.push_back(coo);
	}
	else{
		for(int i = 0; i < 8; ++i)
			if(children[i] != NULL)
				children[i]->getAllCoordinates(centres);
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