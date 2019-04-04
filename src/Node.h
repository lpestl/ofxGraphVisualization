#pragma once

#include <vector>
#include "Edge.h"
#include <memory>

class Edge;

class Node
{
public:
	Node(unsigned id);
	~Node();

	unsigned getId() const;
	size_t getEdgesNumber() const;
	bool addEdge(std::shared_ptr<Node> dstNode);
	void deleteEdge(std::shared_ptr<Node> dstNode);
	//void deleteEdge(int index);
private:
	unsigned id_;
	// TODO: It is necessary to implement universal logic with edges. 
	// TODO: You need to add the ability to work with directional edges (incoming / outgoing) 
	// TODO: and usual (without direction / in both directions).
	std::vector<std::shared_ptr<Edge>> edges_;
};

