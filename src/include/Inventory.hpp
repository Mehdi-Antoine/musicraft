#pragma once
#include <map>
#include <vector>

class Inventory {
private:
	std::map<char, int> m_list;
	std::vector<char> m_type_list;
	std::vector<int> m_nb_list;
	int m_nb_max_items = 8;
	int m_current_index;
	int m_max_size;
public:
	Inventory();
	~Inventory();

	bool isEmpty() const;
	int getNumberCubes() const;
	int getCurrentIndex() const;
	void nextIndex();
	void prevIndex();

	void addCube(char cube);

	bool removeCube(char &result,int index);
	bool removeCurrentCube(char &result);

	void show() const;


	/* data */
};