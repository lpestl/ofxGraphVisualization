#include "Edge.h"

Edge::Edge(unsigned id, std::shared_ptr<Node> srcNode, std::shared_ptr<Node> dstNode, int weight)
{
	id_ = id;

	sourceNode_ = srcNode;
	destNode_ = dstNode;

	weight_ = weight;
}


Edge::~Edge()
{
}

unsigned Edge::getId() const
{
	return id_;
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

void Edge::setWeight(int new_weight)
{
	weight_ = new_weight;
}
