#include "ofxGraph.h"
#include "ofxNode.h"
#include "ofxEdge.h"
#include <random>

void ofxGraph::setup(ofRectangle boundRect)
{
	boundRect_ = std::make_shared<ofRectangle>(boundRect);

	nodeCaptureFont_ = std::make_shared<ofxTrueTypeFontUC>();
	edgeCaptureFont_ = std::make_shared<ofxTrueTypeFontUC>();

	nodeCaptureFont_->loadFont("data\\fonts\\TAHOMABD.ttf", 12);
	edgeCaptureFont_->loadFont("data\\fonts\\TAHOMABD.ttf", 10);
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
				ofx_edge->draw(edgeCaptureShowed_);
			}
		}
	}

	ofSetColor(ofColor::white);
	for (auto&& node : nodes_)
	{
		auto ofx_node = std::dynamic_pointer_cast<ofxNode>(node.second);
		ofx_node->draw(nodeCaptureShowed_);
	}
}

void ofxGraph::deleteEdge(unsigned from, unsigned to)
{
	auto ofx_from_node = std::dynamic_pointer_cast<ofxNode>(nodes_[from]);
	auto ofx_to_node = std::dynamic_pointer_cast<ofxNode>(nodes_[to]);

	if ((ofx_from_node == nullptr) || (ofx_to_node == nullptr))
		return;

	if (adjacency_matrix_[from][to] != nullptr) 
	{
		auto radius = ofx_from_node->getTargetRadius();
		ofx_from_node->setRadius(radius - 1);

		radius = ofx_to_node->getTargetRadius();
		ofx_to_node->setRadius(radius - 1);

		Graph::deleteEdge(from, to);
	}	
}

void ofxGraph::setSpeed(ofVec2f from, ofVec2f to)
{
	for (auto&& node : nodes_)
	{
		auto ofx_node = std::dynamic_pointer_cast<ofxNode>(node.second);
		ofx_node->setSpeed(ofVec2f(ofRandom(from.x, to.x), ofRandom(from.y, to.y)));
	}
}

void ofxGraph::showNodeCapture()
{
	nodeCaptureShowed_ = true;
}

void ofxGraph::hideNodeCapture()
{
	nodeCaptureShowed_ = false;
}

void ofxGraph::showEdgeCapture()
{
	edgeCaptureShowed_ = true;
}

void ofxGraph::hideEdgeCapture()
{
	edgeCaptureShowed_ = false;
}

void ofxGraph::updateRandomEdge()
{
	auto edgeCount = getCurrEdgesCount();
	int isAddingEdge = ofRandom(2);

	if (edgeCount == 0)
		isAddingEdge = 1;
	if (edgeCount >= getMaxEdgesCount())
		isAddingEdge = 0;


	std::vector<unsigned> from;
	std::vector<unsigned> to;
	for (auto && node : nodes_)
	{
		from.push_back(node.second->getId());
		to.push_back(node.second->getId());
	}

	//bool done = false;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(from.begin(), from.end(), std::default_random_engine(seed));
	std::shuffle(to.begin(), to.end(), std::default_random_engine(seed));

	if (isAddingEdge)
	{
		bool isAdded = false;
		for (auto && fromValue : from)
		{
			for (auto && toValue : to)
			{
				if ((fromValue != toValue) && (adjacency_matrix_[fromValue][toValue] == nullptr))
				{
					addEdge(fromValue, toValue, 1);
					isAdded = true;
					break;
				}
			}

			if (isAdded)
				break;
		}
	} else
	{
		bool isDeleted = false;
		for (auto&& fromValue : from)
		{
			for (auto&& toValue : to)
			{
				if (/*(fromValue != toValue) &&*/ (adjacency_matrix_[fromValue][toValue] != nullptr))
				{
					deleteEdge(fromValue, toValue);
					isDeleted = true;
					break;
				}
			}

			if (isDeleted)
				break;
		}
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
	ofx_from_node->setRadius(ofx_from_node->getTargetRadius() + 1);
	
	auto ofx_to_node = std::dynamic_pointer_cast<ofxNode>(nodes_[to]);
	ofx_to_node->setRadius(ofx_to_node->getTargetRadius() + 1);

	adjacency_matrix_[from][to] = newEdge;
}
