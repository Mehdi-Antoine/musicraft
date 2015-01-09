#pragma once
#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <iostream>
#include <vector>
#include "Octree.hpp"
#include "PerlinNoise.hpp"

#define SIZE 4

enum CubeType{ 
  EMPTY = 0,
  BASIC1 = 1,
  BASIC2 = 2,
  BASIC3 = 3
};


class Chunk{
	public:
		Octree root;
		int profondeur = 2;
		float taille = pow(2, profondeur-1);

		Chunk();
		Chunk(PerlinNoise &noise, glm::vec3 pos);

		char getCubeType(const glm::vec3 &pos) const;
		void setCubeType(const glm::vec3 &pos, char type);
		void genFlatFloor(Octree &subTree, int etage);
		void genFullCube(Octree &subTree, int etage);
		void genTerrain(Octree &subTree, int etage, float taille, PerlinNoise &noise);
		void fillTerrain(Octree &subTree, int etage, float taille, int x, int z, int y);
		void culling(std::vector<float> centres, Octree &subTree, int etage, float taille);
		void getAllCoordinates(std::vector<glm::vec3> &centres, std::vector<glm::vec3> &color);
		void genAllCoordinates();
		void lighten();

		static glm::vec3 getColorFromType(char cube_type);
};