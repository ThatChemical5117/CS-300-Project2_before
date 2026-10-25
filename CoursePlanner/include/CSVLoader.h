#pragma once
#include <string>
#include <vector>

// This class was made to seperate out generic CSV loading functionality from
// specific data structure creation. 

class CSVLoader
{
public:
	// Constructor
	CSVLoader(std::string t_filePath);

protected:
	std::string m_filePath; // Internal file path

	// Performs checks on the provide file
	bool validateFile();
	
	// Splits lines using a delimiter , this is often a comma for CSV
	std::vector<std::string> splitWithDelimiter(const std::string& t_string, const char t_delimiter);

	// Provide a load interface
	virtual void load() = 0;
};
