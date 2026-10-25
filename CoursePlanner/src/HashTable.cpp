#include "HashTable.h"

inline const unsigned int DEFAULT_SIZE = 79;

HashTable::HashTable()
	: m_nodes(std::vector<Node*>(DEFAULT_SIZE)), m_tableSize(DEFAULT_SIZE)
{}

HashTable::HashTable(unsigned int t_size)
	: m_nodes(std::vector<Node*>(t_size)), m_tableSize(t_size)
{}

HashTable::~HashTable()
{
	for (Node* head: m_nodes)
	{
		Node* currentNode = head;

		while (currentNode != nullptr)
		{
			Node* orphanedNode = currentNode;
			currentNode = orphanedNode->next;

			delete orphanedNode;

		}
	}
}

unsigned int HashTable::hash(int key){
	return key % m_tableSize;
}

void HashTable::Insert(Course t_course) {
	const unsigned int key = hash(atoi(t_course.number.c_str()));

	if (m_nodes.at(key) == nullptr)
	{
		m_nodes.at(key) = new Node(t_course, key);
	} else if (m_nodes.at(key)->key == UINT_MAX)
	{
		m_nodes.at(key)->course = t_course;
		m_nodes.at(key)->key = key;
	} else {
		Node* newNode = new Node(t_course, key);
		newNode->next = m_nodes.at(key)->next;
		m_nodes.at(key)->next = newNode;
	}
}

void HashTable::orphanNode(int key, Node* prev)
{
	Node* orphan = nullptr;

	if (prev != nullptr)
	{
		orphan = prev->next;
		prev->next = orphan->next;
		prev->key = orphan->key;
	}	
	else
	{
		orphan = m_nodes.at(key);
		m_nodes.at(key) = nullptr;
	}

	delete orphan;
};


void HashTable::Remove(std::string t_courseNumber)
{
	const unsigned int key = hash(atoi(t_courseNumber.c_str()));

	if (m_nodes.at(key) == nullptr)
		return;

	if (m_nodes.at(key)->course.number == t_courseNumber)
	{
		orphanNode(key);
	}
	else
	{
		Node* currentNode = m_nodes.at(key)->next;
		Node* prev = m_nodes.at(key);

		while (currentNode != nullptr)
		{
			if (currentNode->course.number == t_courseNumber)
			{
				orphanNode(key, prev);
				return;
			}

			prev = currentNode;
			currentNode = currentNode->next;
		}
	}

}

Course HashTable::Search(std::string t_courseNumber)
{
	Course course;
	unsigned int key = hash(atoi(t_courseNumber.c_str()));

	if (m_nodes.at(key)->course.number == t_courseNumber && m_nodes.at(key)->key != UINT_MAX)
		return m_nodes.at(key)->course;

	Node* currentNode = m_nodes.at(key)->next;
	while (currentNode != nullptr)
	{
		if (currentNode->course.number == t_courseNumber)
			return currentNode->course;

		currentNode = currentNode->next;
	}

	return course;
}

size_t HashTable::Size()
{
	return m_tableSize;
}

// Cast HashTable to a std::vector<Course>
HashTable::operator std::vector<Course>()
{
	// Resulting vector
	std::vector<Course> courseVec;		

	// For each item in the table
	for (unsigned int i = 0; i < m_nodes.size(); i++)
	{
		// set the current node
		Node* currentNode = m_nodes[i];
		
		// Don't do anything if the current node is nullptr
		while(currentNode != nullptr)
		{
			// add the course to vector
			courseVec.push_back(currentNode->course);

			// set the next node
			currentNode = currentNode->next;
		}
	}

	return courseVec;
}


