#pragma once
#include "Graph.h"
#include "ofRectangle.h"

class ofxGraph : public Graph
{
public:
	void setup(ofRectangle boundRect);
	void update();
	void draw();

protected:
	void createNodeInstance(unsigned id) override;
	void createEdgeInstance(unsigned from, unsigned to, int weight) override;

	ofRectangle boundRect_;
};
