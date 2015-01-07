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

	void getCubeType(char &result, const glm::vec3 &pos, int etage, const int profondeur) const;
	void getCubeType(int t, char &result, const glm::vec3 &pos, int etage, const int profondeur) const;
	void setCubeType(const glm::vec3 pos, char type, int etage, const int profondeur, int taille);

	void insert(char type);
	void insert(Octree &tree);
	glm::vec3 getCoordinates();
	void getAllCoordinates(std::vector<glm::vec3> &centres, int etage, const int profondeur);
	void genAllCoordinates(float taille);
	
	void lighten(int etage, const int profondeur, Octree &root);
};