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
	Graph(const Graph& graph);
	virtual ~Graph();

	void init(std::string path_to_file);
	void init(unsigned nodesCount, unsigned edgesCount);
	void clear();

	void addNode(unsigned id);
	void deleteNode(unsigned id);

	void addEdge(unsigned from, unsigned to, int weight);
	virtual void deleteEdge(unsigned from, unsigned to);

	size_t getInEdgesCount(unsigned node_id);
	size_t getOutEdgesCount(unsigned node_id);

	// TODO: Methods
	int getNodesCount() const;
	int getMaxEdgesCount() const;
	int getCurrEdgesCount();

	float getNetworkDensity();

protected:
	virtual void createNodeInstance(unsigned id);
	virtual void createEdgeInstance(unsigned from, unsigned to, int weight);

	std::map<unsigned, std::shared_ptr<Node>> nodes_;
	std::map<unsigned, std::map<unsigned, std::shared_ptr<Edge>>> adjacency_matrix_;
};
