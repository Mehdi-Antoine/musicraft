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

Chunk::Chunk(std::vector<glm::vec3> &centres){
	profondeur = 0;
	int etage = 0;
	root = Octree();
	root.coo = glm::vec3(0,0,0);
	int middle = pow(2, profondeur);
	//genTerrain(root, etage, middle, centres);
	genFlatFloor(root, 0);
	root.genAllCoordinates(middle);
	root.getAllCoordinates(centres);
}

void Chunk::genFlatFloor(Octree &subTree, int etage){

	subTree.children[0] = NULL;
	subTree.children[1] = NULL;
	subTree.children[2] = new Octree();
	subTree.children[3] = new Octree();
	subTree.children[4] = NULL;
	subTree.children[5] = NULL;
	subTree.children[6] = new Octree();
	subTree.children[7] = new Octree();

	if(etage < profondeur){
		++etage;
		Chunk::genFlatFloor(*subTree.children[2], etage);
		Chunk::genFlatFloor(*subTree.children[3], etage);
		Chunk::genFlatFloor(*subTree.children[6], etage);
		Chunk::genFlatFloor(*subTree.children[7], etage);
	}
	else{
		subTree.children[2]->insert(1);
		subTree.children[3]->insert(1);
		subTree.children[6]->insert(1);
		subTree.children[7]->insert(1);
	}
}

void Chunk::genTerrain(Octree &subTree, int etage, float taille, std::vector<glm::vec3> &centres){
	
	double persistence = .3;
    double frequency = 500;
    double amplitude = 5;
    int octaves = 5;
    int randomseed = 0;
    PerlinNoise noise = PerlinNoise(persistence, frequency, amplitude, octaves, randomseed);

    int middle = pow(2, profondeur);

	for(int x = 0; x < middle; ++x){
		for(int z = 0; z < middle; ++z){
			int height = (int)noise.GetHeight(x, z) - middle/2;
			if (height > middle/2)
				height = middle-1;
			if(height < -middle/2)
				height = -middle/2;
			Chunk::fillTerrain(subTree, etage, taille, x, z, height, centres);
		}
	}
}

void Chunk::fillTerrain(Octree &subTree, int etage, float taille,int x, int z, int height, std::vector<glm::vec3> &centres){
	int middle = pow(2, profondeur);
	//std::cout << height << std::endl;
	for(int i = height-1; i <= height; ++i){

		int left, near, bottom;

		(x < subTree.coo[0]) ? left = 0 : left = 1;
		(height < subTree.coo[1]) ? bottom = 0 : bottom = 1;
		(z < subTree.coo[2]) ? near = 0 : near = 1;

		int index = (left|(bottom<<1))|(near<<2);

		for(int i = 0; i < 8;++i){
				if(i == index)
					subTree.children[index] = new Octree();
				else
					subTree.children[i] = NULL;
		}

		taille *= 0.5;
		subTree.children[index]->coo[0] = subTree.coo[0] + ((left*2)-1)*taille;
		subTree.children[index]->coo[1] = subTree.coo[1] + ((bottom*2)-1)*taille;
		subTree.children[index]->coo[2] = subTree.coo[2] + ((near*2)-1)*taille;

		if(etage < profondeur){
			Chunk::fillTerrain(*subTree.children[index], etage+1, taille, x, z, height, centres);
		}
		else{
			subTree.children[index]->insert(1);
			centres.push_back(subTree.children[index]->coo);
		}

	}
}

char Chunk::getCubeType(glm::vec3 &pos){
	int etage = 0;
	return root.getCubeType(root, etage, pow(2, profondeur),pos, profondeur);
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