#include "CSVLoader.h"
#include <filesystem>
#include <iostream>
#include <sstream>

// Constructor with filepath
CSVLoader::CSVLoader(std::string t_filePath)
	:m_filePath(t_filePath)
{}

// Split a CSV line into a vector of strings
std::vector<std::string> CSVLoader::splitWithDelimiter(const std::string& t_string, const char t_delimiter)
{
	// result holder
	std::vector<std::string> splitString;

	// string stream
	std::stringstream sstream(t_string);

	// sub-string line
	std::string substr;

	// loop through the line using the delimiter to cut the string
	while (getline(sstream, substr, t_delimiter))
	{
		// Find all characters that are not white space
		if (substr.find_first_not_of(" \t\n\v\f\r") != std::string::npos && !substr.empty())
		{
			// cut white space
			if (substr.find('\r') != std::string::npos)
			{
				substr.erase(substr.find('\r'));
			}

			// push a string of just characters to the result vector
			splitString.push_back(substr);
		}
	}
		
	// return the result
	return splitString;
}

// Function checks the if the file is valid
bool CSVLoader::validateFile()
{
	// Get the current path
	std::filesystem::path path = std::filesystem::current_path();

	// append the file path
	path.append(m_filePath);

	// File checks
	if (!std::filesystem::exists(path))
	{
		std::cout << "Cannot open: " << m_filePath << "\nCannot find" << std::endl;
		return false;
	}
	
	if (std::filesystem::is_directory(path))
	{
		std::cout << "Cannot open: " << m_filePath << "\nis not a file" << std::endl;
		return false;
	} 

	if (path.extension() != ".csv")
	{
		std::cout << "Invalid file format: " << path.extension() << std::endl;
		std::cout << "Expected .csv" << std::endl;

		return false;
	}

	return true;
}
