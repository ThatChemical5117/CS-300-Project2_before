#include "UserInput.h"


template<typename T>
T getUserInput(const char* message)
{
	std::cout << "No valid function for this type\n";
}


template<>
int getUserInput(const char* message)
{
	std::string userInput;
	
	std::cout << message;

	std::cin >> userInput;
	
	return std::atoi(userInput.c_str());

}

template<>
std::string getUserInput(const char* message)
{
	std::string userInput;
	std::cout << message;
	std::cin >> userInput;

	return userInput;
}
