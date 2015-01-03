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
	void getAllCoordinates(std::vector<glm::vec3> &centres);
	void genAllCoordinates(float taille);
};