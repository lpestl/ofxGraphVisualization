#include "Edge.h"

Edge::Edge(std::shared_ptr<Node> srcNode, std::shared_ptr<Node> dstNode, int weight)
{
	sourceNode_ = srcNode;
	destNode_ = dstNode;

	weight_ = weight;
}

Edge::Edge(const Edge& edge, std::shared_ptr<Node> copySrcNode, std::shared_ptr<Node> copyDstNode)
{
	this->weight_ = edge.weight_;
	this->sourceNode_ = copySrcNode;
	this->destNode_ = copyDstNode;
}

Edge::~Edge()
{
}

//unsigned Edge::getId() const
//{
//	return id_;
//}

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
