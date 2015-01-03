#pragma once

#include <glimac/glm.hpp>
#include <vector>

class Octree{

private:

	char cubeType;
	

public:

	Octree *children[8];
	glm::vec3 coo;

	Octree();
	Octree(int type);
	Octree(Octree** newChildren);

	char getCubeType();

	bool isLeaf();
	void insert(char type);
	void insert(Octree &tree);
	void getAllCoordinates(std::vector<glm::vec3> &centres, int etage, const int profondeur);
	void genAllCoordinates(float taille);
	char getCubeType(Octree &subTree, int etage, const int taille, glm::vec3 &pos, const int profondeur);
};