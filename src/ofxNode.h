#pragma once

#include "ofMain.h"
#include "Node.h"
#include "ofVec2f.h"

class ofRectangle;

class ofxNode : public Node
{
public:
	explicit ofxNode(unsigned id) : Node(id),
		boundRect_(0,0,0,0),
		position_(0,0),
		speed_(0,0),
		radius_(10)
	{	}

	void setup(ofRectangle boundRect);
	void update() override;
	void draw() override;

private:
	ofRectangle boundRect_;
	ofVec2f position_;
	ofVec2f speed_;
	float radius_;
};

