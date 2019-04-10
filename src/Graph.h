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
	virtual ~Graph();

	void init(std::string path_to_file);

	void addNode(unsigned id);
	void deleteNode(unsigned id);

	void addEdge(unsigned from, unsigned to, int weight);
	virtual void deleteEdge(unsigned from, unsigned to);

	size_t getInEdgesCount(unsigned node_id);
	size_t getOutEdgesCount(unsigned node_id);

	// TODO: Methods
	// Количество вершин
	int getNodesCount() const;
	// Количество всего возможных рёбер
	int getMaxEdgesCount() const;
	// Количество наблюдаемых рёбер (в данный момент)
	int getCurrEdgesCount();
	// Подсчет сетевой плотности
	float getNetworkDensity();

protected:
	virtual void createNodeInstance(unsigned id);
	virtual void createEdgeInstance(unsigned from, unsigned to, int weight);

	std::map<unsigned, std::shared_ptr<Node>> nodes_;
	std::map<unsigned, std::map<unsigned, std::shared_ptr<Edge>>> adjacency_matrix_;
};
