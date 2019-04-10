#include "ofxGraph.h"
#include "ofxNode.h"
#include "ofxEdge.h"

void ofxGraph::setup(ofRectangle boundRect)
{
	boundRect_ = std::make_shared<ofRectangle>(boundRect);

	nodeCaptureFont_ = std::make_shared<ofxTrueTypeFontUC>();
	edgeCaptureFont_ = std::make_shared<ofxTrueTypeFontUC>();

	nodeCaptureFont_->loadFont("data\\tahoma\\TAHOMABD.ttf", 12);
	edgeCaptureFont_->loadFont("data\\tahoma\\TAHOMABD.ttf", 10);
}

void ofxGraph::update()
{
	for (auto&& linePair : adjacency_matrix_)
	{
		for (auto&& pairEdge : adjacency_matrix_[linePair.first])
		{
			if (pairEdge.second != nullptr)
			{
				auto ofx_edge = std::dynamic_pointer_cast<ofxEdge>(pairEdge.second);
				ofx_edge->update();
			}
		}
	}

	for (auto && node : nodes_)
	{
		auto ofx_node = std::dynamic_pointer_cast<ofxNode>(node.second);
		ofx_node->update();
	}
}

void ofxGraph::draw()
{
	ofSetColor(ofColor::black);
	for (auto && linePair : adjacency_matrix_)
	{
		for (auto && pairEdge : adjacency_matrix_[linePair.first])
		{
			if (pairEdge.second != nullptr) 
			{
				auto ofx_edge = std::dynamic_pointer_cast<ofxEdge>(pairEdge.second);
				ofx_edge->draw(true);
			}
		}
	}

	ofSetColor(ofColor::white);
	for (auto&& node : nodes_)
	{
		auto ofx_node = std::dynamic_pointer_cast<ofxNode>(node.second);
		ofx_node->draw(true);
	}
}

void ofxGraph::deleteEdge(unsigned from, unsigned to)
{
	auto ofx_from_node = std::dynamic_pointer_cast<ofxNode>(nodes_[from]);
	auto ofx_to_node = std::dynamic_pointer_cast<ofxNode>(nodes_[to]);
	
	auto radius = ofx_from_node->getRadius();	
	ofx_from_node->setRadius(radius - 1);

	radius = ofx_to_node->getRadius();
	ofx_to_node->setRadius(radius - 1);

	Graph::deleteEdge(from, to);
}

void ofxGraph::setSpeed(ofVec2f from, ofVec2f to)
{
	for (auto&& node : nodes_)
	{
		auto ofx_node = std::dynamic_pointer_cast<ofxNode>(node.second);
		ofx_node->setSpeed(ofVec2f(ofRandom(from.x, to.x), ofRandom(from.y, to.y)));
	}
}

void ofxGraph::createNodeInstance(unsigned id)
{
	auto newNode = std::make_shared<ofxNode>(id);
	newNode->setup(boundRect_, nodeCaptureFont_);

	nodes_[id] = newNode;
	
}

void ofxGraph::createEdgeInstance(unsigned from, unsigned to, int weight)
{
	auto newEdge = std::make_shared<ofxEdge>(nodes_[from], nodes_[to], weight);
	newEdge->setup(edgeCaptureFont_);
	
	auto ofx_from_node = std::dynamic_pointer_cast<ofxNode>(nodes_[from]);
	ofx_from_node->setRadius(ofx_from_node->getRadius() + 1);
	
	auto ofx_to_node = std::dynamic_pointer_cast<ofxNode>(nodes_[to]);
	ofx_to_node->setRadius(ofx_to_node->getRadius() + 1);

	adjacency_matrix_[from][to] = newEdge;
}
