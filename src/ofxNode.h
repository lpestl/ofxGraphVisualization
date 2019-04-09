#pragma once

#include "ofRectangle.h"
#include "ofxTrueTypeFontUC.h"
#include "ofVec2f.h"
#include "Node.h"

//class ofRectangle;
//class ofxTrueTypeFontUC;

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
	void update();
	void draw(bool isNameVisible = false);

	void setPosition(ofVec2f newPos);
	ofVec2f getPosition() const;

	void setSpeed(ofVec2f newSpeed);
	ofVec2f getSpeed() const;

	void setRadius(float radius);
	float getRadius() const;
private:
	ofRectangle boundRect_;
	ofVec2f position_;
	ofVec2f speed_;
	float radius_;

	ofxTrueTypeFontUC tahomaFont_;
};

