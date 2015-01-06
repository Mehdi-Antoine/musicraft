#pragma once

#include <iostream>
#include <vector>
#include "Octree.hpp"
#include "PerlinNoise.hpp"

class Chunk{

private:
	

public:
	Octree root;
	int profondeur;
	
	Chunk();
	Chunk(int seed, glm::vec3 racine);

	void genFlatFloor(Octree &subTree, int etage);
	void genFullCube(Octree &subTree, int etage);
	void genTerrain(Octree &subTree, int etage, float taille, int seed);
	void fillTerrain(Octree &subTree, int etage, float taille, int x, int z, int y);

	void culling(std::vector<float> centres, Octree &subTree, int etage, float taille);

	char getCubeType(glm::vec3 &pos) const;
	void setCubeType(glm::vec3 &pos, char type);

	std::vector<glm::vec3> getAllCoordinates();

	void lighten();
};
