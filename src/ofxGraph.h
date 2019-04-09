#pragma once

#include "Graph.h"
#include "ofRectangle.h"

class ofVec2f;

class ofxGraph : public Graph
{
public:
	void setup(ofRectangle boundRect);
	void update();
	void draw();

	void deleteEdge(unsigned from, unsigned to) override;
	void setSpeed(ofVec2f from, ofVec2f to);
private:
	void createNodeInstance(unsigned id) override;
	void createEdgeInstance(unsigned from, unsigned to, int weight) override;

	ofRectangle boundRect_;
};
