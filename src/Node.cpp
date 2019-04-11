#include "Node.h"

Node::Node(unsigned id)
{
	id_ = id;
}

Node::Node(const Node& node)
{
	this->id_ = node.id_;
}

Node::~Node()
{
}

unsigned Node::getId() const
{
	return id_;
}
