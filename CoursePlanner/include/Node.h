#pragma once
#include "Course.h"
#include <climits>

struct Node{
	Course course;
	unsigned int key = UINT_MAX;
	Node* next;

	Node() = default;

	Node(Course t_course);
	Node(Course t_course, unsigned int t_key);
};
