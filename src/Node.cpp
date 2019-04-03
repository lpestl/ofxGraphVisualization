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

bool Node::addEdge(Node* dstNode)
{
	//auto contains = false;

	//for (auto && edge : edges_)
	//{
	//	if ((edge->getSourceNodeId() == dstNode->getId()) || (edge->getDestNodeId() == dstNode->getId()))
	//	{
	//		contains = true;
	//		break;
	//	}
	//}

	//if (contains)
	//	// TODO: Only if edge two direction/no direction
	//	return false;
	//
	//edges_.push_back(new Edge(this, dstNode, 1));
	return false;
}

void Node::deleteEdge(Node* dstNode)
{
	//for (size_t i = 0; i < edges_.size(); ++i)
	//{
	//	if ()
	//}
}
