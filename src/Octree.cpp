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

void Octree::insert(char type){
	cubeType = type;
}

void Octree::insert(Octree &tree){
	for(int i= 0; i < 8; ++i){
		children[i] = tree.children[i];
	}
}

glm::vec3 Octree::getCoordinates(){
	return coo;
}

void Octree::getAllCoordinates(std::vector<glm::vec3> &centres, std::vector<char> &color, int etage, const int profondeur){
	for(int i = 0; i < 8; ++i){
		if(children[i] != NULL){
			if(etage < profondeur)
				children[i]->getAllCoordinates(centres, color, etage+1, profondeur);
			else if(children[i]->cubeType > 0){
				color.push_back(children[i]->cubeType);
				centres.push_back(float(2)*children[i]->coo);
			}
		}
	}
}

void Octree::genAllCoordinates(float taille, int etage, const int profondeur){
	taille *= 0.5;
	int coef = 1;
	for(int i = 0; i < 8; ++i){
		if(children[i] != NULL){

			children[i]->coo[0] = coo[0] + (((i&1)*2)-1)*taille;
			children[i]->coo[1] = coo[1] + ((((i&(1<<1))>>1)*2)-1)*taille;
			children[i]->coo[2] = coo[2] + ((((i&(1<<2))>>2)*2)-1)*taille;
			if(etage < profondeur)
				children[i]->genAllCoordinates(taille, etage+1, profondeur);
		}
	}
}

void Octree::getCubeType(char &result, const glm::vec3 &pos, int etage, const int profondeur) const{

	int right, far, top;

	(pos.x > coo[0]) ? right = 1 : right = 0;
	(pos.y > coo[1]) ? top = 1 : top = 0;
	(pos.z > coo[2]) ? far = 1 : far = 0;

	int index = (right|(top<<1))|(far<<2);

	if(children[index] == NULL)
		result = 0;
	
	else if(etage < profondeur){
		children[index]->getCubeType(result, pos, etage+1, profondeur);
	}
	else{
		result = children[index]->cubeType;
	}
}

void Octree::setCubeType(glm::vec3 pos, char type, int etage, const int profondeur, float taille, Octree &root){
	int right, far, top;

	(pos.x > coo[0]) ? right = 1 : right = 0;
	(pos.y > coo[1]) ? top = 1 : top = 0;
	(pos.z > coo[2]) ? far = 1 : far = 0;

	int index = (right|(top<<1))|(far<<2);

	if(children[index] == NULL)
		children[index] = new Octree();

	
	children[index]->coo[0] = coo[0] + ((right*2)-1)*taille;
	children[index]->coo[1] = coo[1] + ((top*2)-1)*taille;
	children[index]->coo[2] = coo[2] + ((far*2)-1)*taille;
	taille *= 0.5;

	if(etage < profondeur){
		children[index]->setCubeType(pos, type, etage+1, profondeur, taille, root);
	}
	else{
		children[index]->insert(type);
		if(type == 0){
			root.checkCubes(profondeur, taille, root);
		}
	}
}

void Octree::lighten(int etage, const int profondeur, Octree &root){
	for(int i = 0; i < 8; ++i){
		if(children[i] != NULL){
			if(etage < profondeur){
				children[i]->lighten(etage+1, profondeur, root);
			}
			else if(children[i]->cubeType != 0){
				char result = 1;
				for(int j = 1; j < 5; ++j){
					if(j == 3) j++;
					glm::vec3 pos = glm::vec3(children[i]->coo.x + (j&1), children[i]->coo.y + ((j>>1)&1), children[i]->coo.z + ((j>>2)&1));
					root.getCubeType(result, pos, 0, profondeur);
					if(result == 0){
						break;
					}
				}
				if(result != 0){
					for(int j = 1; j < 5; ++j){
						if(j == 3) j++;
						glm::vec3 pos = glm::vec3(children[i]->coo.x - (j&1), children[i]->coo.y - ((j>>1)&1), children[i]->coo.z - ((j>>2)&1));
						root.getCubeType(result, pos, 0, profondeur);
						if(result == 0){
							break;
						}
					}
				}
				if(result != 0){
					int tmp = (int)children[i]->cubeType;
					tmp = -tmp;
					children[i]->insert((char)tmp);
				}
			}
		}
	}
}

void Octree::checkCubes(const int profondeur, float taille, Octree &root){

	char result = 1;
	for(int j = 1; j < 5; ++j){
		if(j == 3) j++;
		glm::vec3 pos = glm::vec3(coo.x + (j&1), coo.y + ((j>>1)&1), coo.z + ((j>>2)&1));
		root.getCubeType(result, pos, 0, profondeur);
		if(result < 0){
			root.setCubeType(pos*glm::vec3(.5,.5,.5),1,0, profondeur, taille, root);
		}
	}
	for(int j = 1; j < 5; ++j){
		if(j == 3) j++;
		glm::vec3 pos = glm::vec3(coo.x - (j&1), coo.y - ((j>>1)&1), coo.z - ((j>>2)&1));
		root.getCubeType(result, pos, 0, profondeur);
		if(result < 0){
			root.setCubeType(pos*glm::vec3(.5,.5,.5),1,0, profondeur, taille, root);	
		}
	}
}
