#include "Course.h"

// Default constructor
Course::Course()
	:number { "" }, name { "" }, prerequisites { std::vector<std::string>() }
{}

// Constructor with values
Course::Course(std::string t_number, std::string t_name, std::vector<std::string> t_prerequisites)
	:number { t_number }, name { t_name }, prerequisites { t_prerequisites }
{}

// return if the course is empty ( when there is no course number )
bool Course::isEmpty()
{
	return number.empty();
}

// print course and it's prerequisites with << operator
std::ostream& operator<<(std::ostream& os, const Course& course)
{

	os << course.number << ": " << course.name;

	return os;
};
