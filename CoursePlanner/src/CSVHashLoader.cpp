#include "CSVHashLoader.h"
#include <iostream>
#include <fstream>

// Constructor start with a filename and target data structure
CSVHashLoader::CSVHashLoader(std::string t_fileName, HashTable& t_target)
	: CSVLoader(t_fileName), m_loadTarget { t_target }
{}

// define load function
void CSVHashLoader::load()
{
	// Use validate file function from parent
	if (!validateFile())
		return;

	// open a file stream
	std::ifstream ifstream(m_filePath);

	// Check that file is open
	if (!ifstream.is_open())
	{
		std::cout << "Failed to open file: " << m_filePath << std::endl;
		return;
	}

	// Loop through file and use line variable to store current line
	std::string line;
	while(getline(ifstream, line))
	{
		Course course = parseLine(line); // Create a course with parse line

		// make sure the course is not empty
		if (!course.isEmpty())
			m_loadTarget.Insert(course); // insert the course
	}

	// Close the file
	ifstream.close();

	// Make sure that all class prerequisites were loaded
	checkPrerequisites();
}

// take a CSV file line and parse into a Course object
Course CSVHashLoader::parseLine(std::string t_line)
{
	// Split a line with , as a delimiter
	std::vector<std::string> arguments = splitWithDelimiter(t_line, ',');

	// Initialize empty string vector
	std::vector<std::string> prerequisites;

	// Check that there are at least 2 values in the line
	if (arguments.size() < 2 )
	{
		std::cout << "Line size is too small (" << arguments.size() << ")" << std::endl;
		std::cout << "Expected at least size 2" << std::endl;
		return Course(); // empty course
	}

	// if there are course prerequisites
	for (unsigned int i = 2; i < arguments.size(); i++)
	{
		// add them to the prerequisite vector
		prerequisites.push_back(arguments.at(i));
	}
	
	// return a course
	return Course(arguments.at(0), arguments.at(1), prerequisites);
};

void CSVHashLoader::checkPrerequisites()
{
	// Static case the Hash table into a vector of Courses
	std::vector<Course> courses = static_cast<std::vector<Course>>(m_loadTarget);

	// Loop through the vector
	for (Course& course: courses)
	{
		// Loop through the prerequisite strings
		for (std::string prerequisite: course.prerequisites)
		{
			// remove if the courses in prerequisites don't exist 
			if (m_loadTarget.Search(prerequisite).isEmpty())
			{
				std::cout << "Couldn't find course: " << prerequisite << std::endl;
				m_loadTarget.Remove(course.number); // remove the course 
				continue;
			}
		}
	};
};
