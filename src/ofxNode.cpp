#include "ofxNode.h"
#include <random>

void ofxNode::setup(ofRectangle boundRect)
{
	tahomaFont_.loadFont("data\\tahoma\\TAHOMABD.ttf", 12);

	boundRect_ = boundRect;

	/*std::default_random_engine generator(ofGetElapsedTimeMicros());

	std::uniform_int_distribution<int> xRange(static_cast<int>(boundRect_.getMinX()), static_cast<int>(boundRect_.getMaxX()));
	std::uniform_int_distribution<int> yRange(static_cast<int>(boundRect_.getMinY()), static_cast<int>(boundRect_.getMaxY()));
	std::uniform_real_distribution<float> speedRange(-100., 100.);*/
	position_.set(ofRandom(boundRect_.getMinX(), boundRect_.getMaxX()), ofRandom(boundRect_.getMinY(), boundRect_.getMaxY())/*xRange(generator), yRange(generator)*/);
	speed_.set(0, 0/*speedRange(generator), speedRange(generator)*/);
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

	//cout << id_ << " : " << position_.x << "; " << position_.y << std::endl;
}

void ofxNode::draw(bool isNameVisible)
{
	ofDrawCircle(position_.x, position_.y, radius_);

	if (isNameVisible)
	{
		ofPushStyle();

		const auto capture = ofToString(id_);
		const auto textRect = tahomaFont_.getStringBoundingBox(capture, position_.x, position_.y);

		ofSetColor(ofColor::black);
		tahomaFont_.drawString(ofToString(id_), position_.x - textRect.width / 2, position_.y + textRect.height / 2);

		ofPopStyle();
	}
}

void ofxNode::setPosition(ofVec2f newPos)
{
	if (boundRect_.inside(newPos))
	{
		position_.set(newPos);
	}
}

ofVec2f ofxNode::getPosition() const
{
	return position_;
}

void ofxNode::setSpeed(ofVec2f newSpeed)
{
	speed_.set(newSpeed);
}

ofVec2f ofxNode::getSpeed() const
{
	return speed_;
}

void ofxNode::setRadius(float radius)
{
	radius_ = radius;
}

float ofxNode::getRadius() const
{
	return radius_;
}
