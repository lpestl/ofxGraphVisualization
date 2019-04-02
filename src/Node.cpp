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

size_t Node::getEdgesNumber() const
{
	return edges_.size();
}

void Node::addEdge(const Node* dstNode)
{
	//auto contains = false;

	//for (auto && edge : edges_)
	//{
	//	if (edge.s)
	//}
}

void Node::deleteEdge(const Node* dstNode)
{
	//for (size_t i = 0; i < edges_.size(); ++i)
	//{
	//	if ()
	//}
}
