#pragma once

#include "Edge.h"
#include "ofxTrueTypeFontUC.h"

class ofxEdge : public Edge
{
public:
	explicit ofxEdge(std::shared_ptr<Node>& srcNode, std::shared_ptr<Node>& dstNode, int weight)
		: Edge(srcNode, dstNode, weight)
	{
	}

	void setup();
	//void update();
	void draw(bool isWeightVisible = false);

private:
	ofxTrueTypeFontUC font_;
};

