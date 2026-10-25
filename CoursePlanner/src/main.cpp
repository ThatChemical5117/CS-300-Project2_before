#include <iostream>
#include "HashTable.h"
#include "CSVHashLoader.h"
#include "UserInput.h"


// Switch all characters in a string to upper case
std::string toUpperCase(std::string string)
{
	// result string
	std::string newString;

	// for each character in the string
	for (char c: string)
	{
		// add a character to the result string that is uppercase
		newString.push_back(toupper(c));
	}

	// return
	return newString;
}

// print out a course
void searchCourse(HashTable& t_courses)
{
	// Make user input all uppercase
	std::string userString = toUpperCase(getUserInput<std::string>("What course do you want to know more about? "));

	// Search for the course
	Course course = t_courses.Search(userString);

	// if not empty
	if (!course.isEmpty())
	{
		// display the course and it's prerequisites
		std::cout << course << std::endl;
		std::cout << std::endl;
		if (!course.prerequisites.empty())
		{
			std::cout << "Prerequisite: ";
			for (std::string prerequisite: course.prerequisites)
			{
				std::cout << prerequisite;
				if (prerequisite != course.prerequisites.back())
				{
					std::cout << ", ";
				}
			}

			std::cout << std::endl;
		}
	} else
	{
		// print that we could not find a course
		std::cout << "Could not find course: " << userString << std::endl;
	};
}

// Print out menu
//
void displayMenu()
{
	std::cout << "1) Load Data Structure" << std::endl;
	std::cout << "2) Print course list" << std::endl;
	std::cout << "3) Print course" << std::endl;
	std::cout << "9) Exit program" << std::endl;
}

//====================================================================================================
// Display structure sorted
//====================================================================================================

// Quicksort partition
int partition(std::vector<Course>& courses, unsigned int begin, unsigned int end) {
    //set low and high equal to begin and end
	int low = begin;
	int high = end;

    // Calculate the middle element as middlePoint (int)
    // Set Pivot as middlePoint element title to compare (string)  
	int midpoint = low + (high - low) / 2;
	Course pivot = courses.at(midpoint);
  
	bool done = false;
	while (!done)
	{
		// while the bid at position low is less than the pivot bid value
		while(courses.at(low).number.compare(pivot.number) < 0)
		{
			// increment low
			low+=1;
		}

		// While pivot is less than the bid at position high
		while(pivot.number.compare(courses.at(high).number) < 0)
		{
			// decrement low
			high-=1;
		};

		// End  the loop when low and high are the same ( 0 or 1 )
		if (low >= high)
		{
			done = true;
		} else
		{
			// Swap the current bids at low and high
			Course temp = courses.at(low);
			courses.at(low) = courses.at(high);
			courses.at(high) = temp;

			// Updated indexes
			low += 1;
			high -= 1;
		}
	}

	// return high
	return high;
}

// Quicksort implementation
// Note: From vector sorting assignment
void quickSort(std::vector<Course>& courses, unsigned int begin, unsigned int end) {
    //set mid equal to 0
	int mid = 0;

    /* Base case: If there are 1 or zero bids to sort,
     partition is already sorted otherwise if begin is greater
     than or equal to end then return*/
	if ( begin >= end)
	{
		return;
	}

    /* Partition bids into low and high such that
     midpoint is location of last element in low */
	mid = partition(courses,begin, end);
     
    // recursively sort low partition (begin to mid)
	quickSort(courses, begin, mid);

    // recursively sort high partition (mid+1 to end)
	quickSort(courses, mid +1, end);

}

// Display the structure sorted
void displayDataStructure(HashTable& t_courses)
{
	// Convert the HashTable to a vector of courses
	std::vector<Course> courses = static_cast<std::vector<Course>>(t_courses);

	// sort
	quickSort(courses, 0, courses.size() - 1);

	// Formating
	std::cout << "Here is a sample schedule: " << std::endl << std::endl;

	// display all courses
	for (Course course: courses)
	{
		std::cout << course << std::endl;
	}
}


int main(int argc, char** argv)
{
	HashTable courses;
	std::string file;
	bool programShouldClose = false;

	// Check for a file argument, set a default if missing
	if (argc < 2 )
	{
		file = "CS 300 ABCU_Advising_Program_Input.csv";	
	} else
	{
		file = argv[1];
	}

	// New hash loader
	CSVHashLoader loader(file, courses);

	std::cout << "Welcome to the course planner." << std::endl << std::endl;

	// main loop
	while (!programShouldClose)
	{
		// print menu
		displayMenu();
		std::cout << std::endl;

		// get user input
		int userInput = getUserInput<int>("What would you like to do? ");
	
		// Make decision
		switch(userInput)
		{
			case 1: // load hash table
				loader.load();
				break;
			case 2: // display data structure 
				displayDataStructure(courses);
				break;
			case 3: // search for a course
				searchCourse(courses);
				break;
			case 9: // exit program
				programShouldClose = true;
				break;
			default: // invalid input
				std::cout << userInput << " is not a vaild option." << std::endl;
		}

		std::cout << std::endl;

	}

	// exit message
	std::cout << "Thank you for using the course planner!" << std::endl;

}
