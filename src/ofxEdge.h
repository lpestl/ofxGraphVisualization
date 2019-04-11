#pragma once

#include "Edge.h"
#include "ofxTrueTypeFontUC.h"

class ofxEdge : public Edge
{
public:
	explicit ofxEdge(std::shared_ptr<Node>& srcNode, std::shared_ptr<Node>& dstNode, int weight)
		: Edge(srcNode, dstNode, weight),
		from_point_(0, 0),
		to_point_(0, 0)
	{
	}

	void setup(std::shared_ptr<ofxTrueTypeFontUC> font);
	void update();
	void draw(bool isWeightVisible = false);

private:
	ofVec2f from_point_;
	ofVec2f to_point_;
	std::shared_ptr<ofxTrueTypeFontUC> captureFont_;
};

