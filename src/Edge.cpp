#include "Edge.h"

Edge::Edge(Node * srcNode, Node * dstNode, int weight)
{
	sourceNode_ = srcNode;
	destNode_ = dstNode;

	weight_ = weight;
}

Edge::~Edge()
{
}
