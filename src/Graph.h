#pragma once
#include <map>
#include "Node.h"
#include "Edge.h"
#include <memory>
#include <vector>

class Graph
{
public:
	Graph();
	~Graph();

	void init(std::string path_to_file);

	void addNode(unsigned id);
	void deleteNode(unsigned id);

	void addEdge(unsigned from, unsigned to, int weight);
	void deleteEdge(unsigned from, unsigned to);

	size_t getInEdgesCount(unsigned node_id);
	size_t getOutEdgesCount(unsigned node_id);
//private:
	std::map<unsigned, std::shared_ptr<Node>> nodes_;
	std::map<unsigned, std::map<unsigned, std::shared_ptr<Edge>>> adjacency_matrix_;
};
