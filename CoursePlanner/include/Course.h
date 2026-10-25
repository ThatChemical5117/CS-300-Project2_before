#pragma once
#include <ostream>
#include <string>
#include <vector>

struct Course{
	std::string number;
	std::string name;
	std::vector<std::string> prerequisites;

	Course();
	Course(std::string t_number, std::string t_name, std::vector<std::string> t_prerequisites);
	bool  isEmpty();

};


std::ostream& operator<<(std::ostream& os, const Course& course);
