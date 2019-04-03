#pragma once

#include "Node.h"

class Node;

class Edge
{
public:
	Edge(Node* srcNode, Node* dstNode, int weight);
	~Edge();	

	unsigned getSourceNodeId() const;
	unsigned getDestNodeId() const;
	int getWeight() const;
private:
	Node*	sourceNode_;
	Node*	destNode_;
	int		weight_;
};

