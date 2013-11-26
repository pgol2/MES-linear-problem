#include "Node.h"


Node::Node(void)
{
}
Node::Node(double l, double NodeTemp, int NodeBc) {
	x = l;
	t = NodeTemp;
	bc = NodeBc;
}

Node::~Node(void)
{
}
