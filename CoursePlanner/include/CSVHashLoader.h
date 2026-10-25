#pragma once

// Implements a CSVLoader object and 
// provides the specific functionality required to create
// this specific implementation of HashTable

#include "CSVLoader.h"
#include "Course.h"
#include "HashTable.h"

class CSVHashLoader: public CSVLoader
{
private:
	HashTable& m_loadTarget;
public:
	CSVHashLoader(std::string t_fileName, HashTable& t_target);

	void load() override;
private:
	Course parseLine(std::string t_line);
	void checkPrerequisites();

};
