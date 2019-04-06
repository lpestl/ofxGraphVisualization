#include "ofxGraph.h"
#include "ofxNode.h"
#include "ofxEdge.h"

void ofxGraph::setup(ofRectangle boundRect)
{
	boundRect_ = boundRect;
}

void ofxGraph::update()
{
	for (auto && node : nodes_)
	{
		auto ofx_node = std::dynamic_pointer_cast<ofxNode>(node.second);
		ofx_node->update();
	}
}

void ofxGraph::draw()
{
	for (auto&& node : nodes_)
	{
		auto ofx_node = std::dynamic_pointer_cast<ofxNode>(node.second);
		ofx_node->draw();
	}
}

void ofxGraph::createNodeInstance(unsigned id)
{
	auto newNode = std::make_shared<ofxNode>(id);
	newNode->setup(boundRect_);

	nodes_[id] = newNode;
	
}

void ofxGraph::createEdgeInstance(unsigned from, unsigned to, int weight)
{
	adjacency_matrix_[from][to] = nullptr; //std::make_shared<ofxEdge>(nodes_[from], nodes_[to], weight);
}
