#include "ofxNode.h"
#include <random>

void ofxNode::setup(ofRectangle boundRect)
{
	boundRect_ = boundRect;

	std::default_random_engine generator;

	std::uniform_int_distribution<int> xRange(static_cast<int>(boundRect_.getMinX()), static_cast<int>(boundRect_.getMaxX()));
	std::uniform_int_distribution<int> yRange(static_cast<int>(boundRect_.getMinY()), static_cast<int>(boundRect_.getMaxY()));
	std::uniform_real_distribution<float> speedRange(-100., 100.);

	position_.set(xRange(generator), yRange(generator));
	speed_.set(speedRange(generator), speedRange(generator));
}

void ofxNode::update()
{
	const auto deltaTime = ofGetLastFrameTime();
	ofVec2f deltaPos(speed_.x * deltaTime, speed_.y * deltaTime);

	if (!boundRect_.inside(position_.x + deltaPos.x, position_.y))
	{
		if ((position_.x + deltaPos.x) < boundRect_.getMinX())
		{
			position_.x = boundRect_.getMinX() - position_.x - deltaPos.x + boundRect_.getMinX();
			speed_.x = speed_.x * -1;
		}

		if ((position_.x + deltaPos.x) >= boundRect_.getMaxX())
		{
			position_.x = boundRect_.getMaxX() - position_.x - deltaPos.x + boundRect_.getMaxX();
			speed_.x = speed_.x * -1;
		}
	}
	else
		position_.x += deltaPos.x;

	if (!boundRect_.inside(position_.x, position_.y + deltaPos.y))
	{
		if ((position_.y + deltaPos.y) < boundRect_.getMinY())
		{
			position_.y = boundRect_.getMinY() - position_.y - deltaPos.y + boundRect_.getMinY();
			speed_.y = speed_.y * -1;
		}

		if ((position_.y + deltaPos.y) >= boundRect_.getMaxY())
		{
			position_.y = boundRect_.getMaxY() - position_.y - deltaPos.y + boundRect_.getMaxY();
			speed_.y = speed_.y * -1;
		}
	}
	else
		position_.y += deltaPos.y;
}

void ofxNode::draw()
{
	ofDrawCircle(position_.x, position_.y, radius_);
}
