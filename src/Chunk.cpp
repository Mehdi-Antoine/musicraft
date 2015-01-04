#include "include/Chunk.hpp"
#include "include/Octree.hpp"
#include "include/PerlinNoise.hpp"
#include <glimac/glm.hpp>

Chunk::Chunk(){
	profondeur = 8;
	int etage = 0;
	root = Octree();
	root.coo = glm::vec3(0,0,0);
}

Chunk::Chunk(int seed){
	profondeur = 8;
	int etage = 0;
	root = Octree();
	int taille = pow(2, profondeur);
	root.coo = glm::vec3(0,0,0);
	//std::cout << root.coo[0] << " " <<root.coo[1] << " " << root.coo[2] << std::endl;
	genTerrain(root, etage, taille, seed);
	//genFullCube(root, 0);
	
	//genFlatFloor(root, 0);
	//root.genAllCoordinates(taille);
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

void Chunk::genTerrain(Octree &subTree, int etage, float taille, int seed){
	
	double persistence = 0.9;
    double frequency = 10;
    double amplitude = 20;
    int octaves = 2;
    int randomseed = seed;
    PerlinNoise noise = PerlinNoise(persistence, frequency, amplitude, octaves, randomseed);

	for(int x = 0; x < taille; ++x){
		for(int z = 0; z < taille; ++z){
			int height = (int)noise.GetHeight(x, z) - taille/2;
			if (height > taille/2)
				height = taille-1;
			if(height < -taille/2)
				height = -taille/2;
			for(int y = -pow(2,profondeur)/2; y <= height ; ++y)
				Chunk::fillTerrain(subTree, etage, taille, x, z, y);
		}
	}
}

void Chunk::fillTerrain(Octree &subTree, int etage, float taille, int x, int z, int y){

	int right, far, top;

	(x > subTree.coo[0]) ? right = 1 : right = 0;
	(y > subTree.coo[1]) ? top = 1 : top = 0;
	(z > subTree.coo[2]) ? far = 1 : far = 0;

	int index = (right|(top<<1))|(far<<2);

	for(int i = 0; i < 8;++i){
		if(i == index)
			if(subTree.children[index] == NULL)
				subTree.children[index] = new Octree();
	}

	subTree.children[index]->coo[0] = subTree.coo[0] + ((right*2)-1)*taille;
	subTree.children[index]->coo[1] = subTree.coo[1] + ((top*2)-1)*taille;
	subTree.children[index]->coo[2] = subTree.coo[2] + ((far*2)-1)*taille;

	taille *= 0.5;

	if(etage < profondeur){
		Chunk::fillTerrain(*subTree.children[index], etage+1, taille, x, z, y);
	}
	else{
		subTree.children[index]->insert(1);
	}
}

char Chunk::getCubeType(glm::vec3 &pos){
	int etage = 0;
	char result = 1;
	root.getCubeType(result, pos, etage, profondeur);
	return result;
}

void Chunk::setCubeType(glm::vec3 &pos, char type){
	int etage = 0;
	root.setCubeType(pos, type, etage, profondeur);
}

std::vector<glm::vec3> Chunk::getAllCoordinates(){
	std::vector<glm::vec3> result;
	root.getAllCoordinates(result, 0, profondeur);
	return result;
}

void Chunk::lighten(){
	root.lighten(0, profondeur);
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