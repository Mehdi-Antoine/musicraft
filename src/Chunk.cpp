#include "include/Chunk.hpp"
#include <iostream>
#include "include/Octree.hpp"
#include "include/PerlinNoise.hpp"
#include <glimac/glm.hpp>

Chunk::Chunk(PerlinNoise &noise, glm::vec3 pos){
	root = Octree();
	root.coo = pos;
	int etage = 0;
	//std::cout << noise.GetHeight(pos.x,pos.z) << std::endl;
	genTerrain(root, etage, taille, noise);
}


void Chunk::genFlatFloor(Octree &subTree, int etage){
	
	subTree.children[0] = new Octree();
	subTree.children[1] = new Octree();
	subTree.children[2] = NULL;
	subTree.children[3] = NULL;
	subTree.children[4] = new Octree();
	subTree.children[5] = new Octree();
	subTree.children[6] = NULL;
	subTree.children[7] = NULL;

	if(etage < profondeur){
		++etage;
		Chunk::genFlatFloor(*subTree.children[0], etage);
		Chunk::genFlatFloor(*subTree.children[1], etage);
		Chunk::genFlatFloor(*subTree.children[4], etage);
		Chunk::genFlatFloor(*subTree.children[5], etage);
	}
	else{
		subTree.children[0]->insert(1);
		subTree.children[1]->insert(1);
		subTree.children[4]->insert(1);
		subTree.children[5]->insert(1);
	}
}

void Chunk::genFullCube(Octree &subTree, int etage){
	for(int i = 0; i < 8; ++i){
		subTree.children[i] = new Octree();
	}
	if(etage < profondeur){
		++etage;
		for(int j = 0; j < 8; ++j)
			Chunk::genFullCube(*subTree.children[j], etage);
	}
	else{
		for(int j = 0; j < 8; ++j){
			subTree.children[j]->insert(1);
		}
	}
}

void Chunk::genTerrain(Octree &subTree, int etage, float taille, PerlinNoise &noise){
	for(int x = -taille + root.coo.x; x < taille + root.coo.x; ++x){
		for(int z = -taille + root.coo.z; z < taille + root.coo.z; ++z){
			int height = (int)noise.GetHeight(x, z);

			if (height > taille + root.coo.y)
				height = taille + root.coo.y;
			if(height < -taille +root.coo.y)
				height = -taille + root.coo.y;

			for(int y = -taille + root.coo.y; y < height ; ++y){
				glm::vec3 pos = glm::vec3(x, y, z);
				setCubeType(pos, 1);
			}
		}
	}
}

char Chunk::getCubeType(const glm::vec3 &pos) const{
	int etage = 0;
	char result = 1;
	root.getCubeType(result, pos, etage, profondeur);
	return result;
}

void Chunk::setCubeType(const glm::vec3 &pos, char type){
	int etage = 0;
	root.setCubeType(pos, type, etage, profondeur, taille, root);
}

void Chunk::getAllCoordinates(std::vector<glm::vec3> &centres, std::vector<glm::vec3> &color){
	std::vector<char> typeCube;
	root.getAllCoordinates(centres, typeCube, 0, profondeur);
	for(int i = 0; i < typeCube.size(); ++i){
		color.push_back(Chunk::getColorFromType(typeCube[i]));
	}
}

void Chunk::genAllCoordinates(){
	root.genAllCoordinates(taille, 0, profondeur);
}

void Chunk::lighten(){
	root.lighten(0, profondeur, root);
}

glm::vec3 Chunk::getColorFromType(char cube_type){
	switch (cube_type) {

		case EMPTY:
		  return glm::vec3(0,0,0);
		  break;

		case BASIC1:
		  return glm::vec3(0.75,
						   0.17,
						   0.62);
		  break;

		case BASIC2:
		  return glm::vec3(0.17,
						   0.75,
						   0.47);
		  break;

		case BASIC3:
		  return glm::vec3(0.22,
						   0.4,
						   0.75);
		  break;

		default:
		  return glm::vec3(1,1,1);
		  break;
	}
}

/*void Chunk::culling(std::vector<float> centres, Octree &subTree, int &etage, float taille){
int test = 0;
taille *= .5;
for(int i = 0; i < 8; ++i){
if(subTree.children[i] != NULL){
if(subTree.children[i]->coo[0] + taille > left)
++test;
if(subTree.children[i]->coo[0] - taille < right)
++test;
if(subTree.children[i]->coo[1] + taille > top)
++test;
if(subTree.children[i]->coo[1] - taille < bottom)
++test;
if(subTree.children[i]->coo[2] + taille > far)
++test;
if(subTree.children[i]->coo[2] - taille < near)
++test;
if(etage > profondeur){
if(test == 6){
children[i]->getAllCoordinates(centres);
}
else if(test > 0){
culling(centres, subTree.children[i], etage + 1, taille);
}
}
else if(etage == profondeur){
centres.push_back(coo);
}
}
}
}*/