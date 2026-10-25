#include "Node.h"


Node::Node(Course t_course)
: course { t_course }
{};

Node::Node(Course t_course, unsigned int t_key)
	: course { t_course }, key { t_key }
{};
