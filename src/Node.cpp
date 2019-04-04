#include "Node.h"

Node::Node(unsigned id)
{
	id_ = id;
}

Node::~Node()
{
}

unsigned Node::getId() const
{
	return id_;
}
