#pragma once
#include "Node.h"
#include <vector>


class HashTable
{
private:
	
	std::vector<Node*> m_nodes;
	unsigned int m_tableSize;

public:
	HashTable();
	HashTable(unsigned int t_size);
	~HashTable();
	void Insert(Course t_course);
	void Remove(std::string t_courseNumber);
	Course Search(std::string t_courseNumber);
	size_t Size();

	operator std::vector<Course>();
private:
	unsigned int hash(int key);
	void orphanNode(int key, Node* prev = nullptr);
};
