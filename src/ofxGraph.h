#pragma once
#include <map>
#include "Node.h"
#include <memory>
#include "Edge.h"
#include <vector>

class ofxGraph
{
public:
	void setup();
	void update();
	void draw();

//	bool initFromFile(std::string fileName);
//
//	bool addNode(unsigned id);
//	bool deleteNode(unsigned id);
//
//	bool addEdge(unsigned from_id, unsigned to_id, int weight);
//	bool deleteEdge(unsigned from_id, unsigned to_id);
//
//	size_t getNodesNumber();
//	size_t getInEdgesNumber(unsigned id);
//	size_t getOutEdgesNumber(unsigned id);
//	size_t getEdgesNumber(unsigned id, bool mergeBothDirEdge = false);
//
//	std::vector<std::vector<std::shared_ptr<Edge>>> getAdjacencyMatrix();
//	std::vector<std::shared_ptr<Edge>> getEdgesList();
//private:
//	std::map<unsigned, std::shared_ptr<Node>> nodes_;
//	// TODO: All the edges in one heap. Maybe they should be divided into incoming and outgoing?
//	std::map<unsigned, std::vector<std::shared_ptr<Edge>>> edges_;
};
