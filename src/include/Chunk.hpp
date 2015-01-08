#pragma once
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <iostream>
#include <vector>
#include "Octree.hpp"
#include "PerlinNoise.hpp"

#define SIZE 32 

enum CubeType{ 
  EMPTY = 0,
  BASIC1 = 1,
  BASIC2 = 2,
  BASIC3 = 3
};


class Chunk{
	public:
		Octree root;
		int profondeur = 4;
		float taille = pow(2, profondeur);

		Chunk();
		Chunk(int seed, glm::vec3 racine);

		char getCubeType(const glm::vec3 &pos) const;
		void setCubeType(const glm::vec3 &pos, char type);
		void genFlatFloor(Octree &subTree, int etage);
		void genFullCube(Octree &subTree, int etage);
		void genTerrain(Octree &subTree, int etage, float taille, int seed);
		void fillTerrain(Octree &subTree, int etage, float taille, int x, int z, int y);
		void culling(std::vector<float> centres, Octree &subTree, int etage, float taille);
		std::vector<glm::vec3> getAllCoordinates();
		void lighten();

		//void setWorldPosition(glm::vec3 world_position);
};