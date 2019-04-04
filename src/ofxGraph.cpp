#include "ofxGraph.h"

void ofxGraph::setup()
{
}

void ofxGraph::update()
{
}

void ofxGraph::draw()
{
}

bool ofxGraph::initFromFile(std::string fileName)
{
	// default
	return false;
}

bool ofxGraph::addNode(unsigned id)
{
	// default
	return false;
}

bool ofxGraph::deleteNode(unsigned id)
{
	// default
	return false;
}

bool ofxGraph::addEdge(unsigned from_id, unsigned to_id, int weight)
{
	// default
	return false;
}

bool ofxGraph::deleteEdge(unsigned from_id, unsigned to_id)
{
	// default
	return false;
}

size_t ofxGraph::getNodesNumber()
{
}

size_t ofxGraph::getInEdgesNumber(unsigned id)
{
}

size_t ofxGraph::getOutEdgesNumber(unsigned id)
{
}

size_t ofxGraph::getEdgesNumber(unsigned id)
{
}

std::vector<std::vector<bool>> ofxGraph::getAdjacencyMatrix()
{
}

std::vector<std::shared_ptr<Edge>> ofxGraph::getEdgesList()
{
}
