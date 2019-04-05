#pragma once

#include "Node.h"
#include <memory>

class Node;

class Edge
{
public:
	Edge(std::shared_ptr<Node> srcNode, std::shared_ptr<Node> dstNode, int weight);
	~Edge();	

	unsigned getId() const;
	unsigned getSourceNodeId() const;
	unsigned getDestNodeId() const;

	int getWeight() const;
	void setWeight(int new_weight);

private:
	std::shared_ptr<Node>	sourceNode_;
	std::shared_ptr<Node>	destNode_;
	int		weight_;
};

