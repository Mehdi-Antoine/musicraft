#pragma once
#include <map>

class Inventory {
private:
	std::map<char, int> m_list;
	char m_current_cube;
	int m_max_size;
public:
	Inventory();
	~Inventory();

	bool isEmpty() const;
	int getNumberCubes() const;
	int getCurrentCube();
	void setCurrentCube(char cube);
	void setNextCurrentCube();
	void setPrevCurrentCube();

	bool addCube(char cube);

	bool removeCube(char cube);
	bool removeCurrentCube();

	void show() const;


	/* data */
};