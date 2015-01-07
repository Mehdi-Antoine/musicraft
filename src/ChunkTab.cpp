#include "include/Chunk.hpp"
#include <iostream>
#include "include/Octree.hpp"
#include "include/PerlinNoise.hpp"
#include <glimac/glm.hpp>


Chunk::Chunk(int seed, glm::vec3 pos){
	int etage = 0;
	root = Octree();
	root.coo = pos;
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

<<<<<<< HEAD:src/Chunk.cpp
void Chunk::genTerrain(Octree &subTree, int etage, float taille, int seed){
	double persistence = 0.9;
	double frequency = .2;
	double amplitude = 60;
	int octaves = 1;
	int randomseed = seed;
	PerlinNoise noise = PerlinNoise(persistence, frequency, amplitude, octaves, randomseed);
	
	for(int x = -taille; x < taille; ++x){
		for(int z = -taille; z < taille; ++z){
			int height = (int)noise.GetHeight(x, z) - taille;
			if (height > taille)
				height = taille;
			if(height < -taille)
				height = -taille;
			for(int y = -taille; y <= height ; ++y){
				glm::vec3 pos = glm::vec3(x, y, z);
				setCubeType(pos, 1);
=======
	for (int x = 0; x < SIZE; ++x)
	{
		for (int y = 0; y < SIZE; ++y)
		{
			for (int z = 0; z < SIZE; ++z)
			{		
				m_chunk[x][y][z] = cube_type;				
>>>>>>> origin/multi_chunk:src/ChunkTab.cpp
			}
		}
	}
}

<<<<<<< HEAD:src/Chunk.cpp
char Chunk::getCubeType(const glm::vec3 &pos) const{
	int etage = 0;
	char result = 1;
	root.getCubeType(result, pos, etage, profondeur);
	return result;
=======
Chunk::Chunk(const Chunk &chunk){

	m_world_position = chunk.getWorldPosition();

	for (int x = 0; x < SIZE; ++x)
	{
		for (int y = 0; y < SIZE; ++y)
		{
			for (int z = 0; z < SIZE; ++z)
			{		
				m_chunk[x][y][z] = chunk.getCubeType(x, y, z);				
			}
		}
	} 

}

Chunk::~Chunk(){

>>>>>>> origin/multi_chunk:src/ChunkTab.cpp
}

void Chunk::setCubeType(const glm::vec3 &pos, char type){
	int etage = 0;
	root.setCubeType(pos, type, etage, profondeur, taille, root);
}

std::vector<glm::vec3> Chunk::getAllCoordinates(){
	std::vector<glm::vec3> result;
	root.getAllCoordinates(result, 0, profondeur);
	return result;
}

<<<<<<< HEAD:src/Chunk.cpp
void Chunk::lighten(){
	root.lighten(0, profondeur, root);
=======
glm::vec3 Chunk::getWorldPosition() const{
	return m_world_position;
}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------SETTERS-----------------------------------------------------
//--------------------------------------------------------------------------------------------------------------	

void Chunk::setCubeType(int x, int y, int z, char cube_type){

	m_chunk[getIndex(x)][getIndex(y)][getIndex(z)] = cube_type;

>>>>>>> origin/multi_chunk:src/ChunkTab.cpp
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
<<<<<<< HEAD:src/Chunk.cpp
else if(test > 0){
culling(centres, subTree.children[i], etage + 1, taille);
=======

void Chunk::setWorldPosition(const glm::vec3 world_position){
	m_world_position = world_position;
}

//-------------------------------------------------FUNCTIONS----------------------------------------------------

int Chunk::getIndex(float value) const{


	float decimal = value - int(value);
	return round(value);
>>>>>>> origin/multi_chunk:src/ChunkTab.cpp
}
}
else if(etage == profondeur){
centres.push_back(coo);
}
}
}
}*/
