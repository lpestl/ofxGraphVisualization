#pragma once
#include "Node.h"

class Edge
{
public:
	Edge(Node * srcNode, Node * dstNode, int weight);
	~Edge();	
private:
	Node *	sourceNode_;
	Node *	destNode_;
	int		weight_;
};

