#include "Edge.h"

Edge::Edge(Node* srcNode, Node* dstNode, int weight)
{
	sourceNode_ = srcNode;
	destNode_ = dstNode;

	weight_ = weight;
}

Edge::~Edge()
{
}

unsigned Edge::getSourceNodeId() const
{
	return sourceNode_->getId();
}

unsigned Edge::getDestNodeId() const
{
	return destNode_->getId();
}

int Edge::getWeight() const
{
	return weight_;
}
