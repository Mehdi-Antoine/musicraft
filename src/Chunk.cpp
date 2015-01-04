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
	profondeur = 8;
	int etage = 0;
	root = Octree();
	int taille = pow(2, profondeur);
	root.coo = glm::vec3(0,0,0);
	std::cout << root.coo[0] << " " <<root.coo[1] << " " << root.coo[2] << std::endl;
	//std::vector<glm::vec3> tuc;
	genTerrain(root, etage, profondeur, taille, centres);
	//genFlatFloor(root, 0);
	//root.genAllCoordinates(taille);
	//root.getAllCoordinates(centres, etage, profondeur);
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

void Chunk::genTerrain(Octree &subTree, int etage, const int profondeur, float taille, std::vector<glm::vec3> &centres){
	
	double persistence = .9;
    double frequency = 10;
    double amplitude = 20;
    int octaves = 5;
    int randomseed = 0;
    PerlinNoise noise = PerlinNoise(persistence, frequency, amplitude, octaves, randomseed);

	for(int x = 0; x < taille; ++x){
		for(int z = 0; z < taille; ++z){
			int height = (int)noise.GetHeight(x, z) - taille/2;
			if (height > taille/2)
				height = taille-1;
			if(height < -taille/2)
				height = -taille/2;
			for(int y = -pow(2,profondeur)/2; y <= height ; ++y)
				Chunk::fillTerrain(subTree, etage, profondeur, taille, x, z, y, centres);
		}
	}
}

void Chunk::fillTerrain(Octree &subTree, int etage, const int profondeur, float taille,int x, int z, int height, std::vector<glm::vec3> &centres){

	int right, far, top;

	(x > subTree.coo[0]) ? right = 1 : right = 0;
	(height > subTree.coo[1]) ? top = 1 : top = 0;
	(z > subTree.coo[2]) ? far = 1 : far = 0;

	int index = (right|(top<<1))|(far<<2);

	for(int i = 0; i < 8;++i){
			if(i == index)
				subTree.children[index] = new Octree();
			/*else
				subTree.children[i] = NULL;*/
	}
	subTree.children[index]->coo[0] = subTree.coo[0] + ((right*2)-1)*taille;
	subTree.children[index]->coo[1] = subTree.coo[1] + ((top*2)-1)*taille;
	subTree.children[index]->coo[2] = subTree.coo[2] + ((far*2)-1)*taille;

	taille *= 0.5;

	if(etage < profondeur){
		Chunk::fillTerrain(*subTree.children[index], etage+1, profondeur, taille, x, z, height, centres);
	}
	else{
		centres.push_back(subTree.children[index]->coo);
		//if(subTree.children[index]->coo[0] < 0)
		std::cout << subTree.children[index]->coo[0] << " " <<subTree.children[index]->coo[1] << " " << subTree.children[index]->coo[2] << std::endl;
		subTree.children[index]->insert(1);
		//subTree.getAllCoordinates(centres, etage, profondeur);
		//centres.push_back(subTree.getCoordinates());
	}
}

char Chunk::getCubeType(glm::vec3 &pos){
	int etage = 0;
	char result = 1;
	pos = pos+glm::vec3(255,-255,255);
	root.getCubeType(result, root, etage, pow(2, profondeur),pos, profondeur);

	return result;
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