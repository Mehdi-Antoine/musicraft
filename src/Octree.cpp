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
	for(int i = 0; i < 8; ++i){
		if(children[i] != NULL)
			/*if(cubeType != 1)
				children[i]->getAllCoordinates(centres);
			else*/
				centres.push_back(children[i]->coo);
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

char Octree::getCubeType(Octree &subTree, int etage, const int taille, glm::vec3 &pos, const int profondeur){
	int left, near, bottom;

	(pos[0]	< subTree.coo[0]) ? left = 0 : left = 1;
	(pos[1] < subTree.coo[1]) ? bottom = 0 : bottom = 1;
	(pos[2] < subTree.coo[2]) ? near = 0 : near = 1;
	int index = (left|(bottom<<1))|(near<<2);

	//std::cout << index << std::endl;
	//std::cout<< "etage : " << etage << " profondeur : " << profondeur << std::endl;
	//std::cout << pos[0] << " " <<pos[1] << " " << pos[2] << std::endl;
	//std::cout << subTree.coo[0] << " " <<subTree.coo[1] << " " << subTree.coo[2] << std::endl;

	if(subTree.children[index] != NULL){
		if(etage < profondeur)
			return Octree::getCubeType(*subTree.children[index], etage+1, taille*0.5, pos, profondeur);
		else
			return 1;
	}
	else{
		return 0;
	}
}