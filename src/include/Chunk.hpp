#pragma once

#include <iostream>
#include <vector>
#include "Octree.hpp"
#include "PerlinNoise.hpp"

class Chunk{

private:
	int profondeur;
	

public:
	Octree root;
	
	Chunk();
	Chunk(std::vector<glm::vec3> &centres);
	void genFlatFloor(Octree &subTree, int etage);
	void genTerrain(Octree &subTree, int etage, float taille, std::vector<glm::vec3> &centres);
	void fillTerrain(Octree &subTree, int etage, float taille, int x, int z, PerlinNoise noise, std::vector<glm::vec3> &centres);
	void culling(std::vector<float> centres, Octree &subTree, int etage, float taille);
};
