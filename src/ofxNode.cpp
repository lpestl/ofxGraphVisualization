#include "ofxNode.h"
#include <random>
#include "ofxTweener.h"

void ofxNode::setup(std::shared_ptr<ofRectangle> boundRect, std::shared_ptr<ofxTrueTypeFontUC> font)
{
	captureFont_ = font;
	boundRect_ = boundRect;

	position_.set(ofRandom(boundRect_->getMinX(), boundRect_->getMaxX()), ofRandom(boundRect_->getMinY(), boundRect_->getMaxY())/*xRange(generator), yRange(generator)*/);
	speed_.set(0, 0);
}

void ofxNode::update()
{
	updatePosition();
}

void ofxNode::draw(bool isNameVisible)
{
	ofDrawCircle(position_.x, position_.y, radius_);

	if (isNameVisible)
	{
		ofPushStyle();
		ofSetColor(ofColor::black);

		const auto capture = ofToString(id_);

		if ((captureFont_ != nullptr) && (captureFont_->isLoaded()))
		{
			const auto textRect = captureFont_->getStringBoundingBox(capture, position_.x, position_.y);

			captureFont_->drawString(ofToString(id_), position_.x - textRect.width / 2, position_.y + textRect.height / 2);
		}
		else
		{
			ofDrawBitmapString(capture, position_.x, position_.y);
		}
		ofPopStyle();
	}
}

void ofxNode::setPosition(ofVec2f newPos)
{
	if (boundRect_->inside(newPos))
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
	targetRadius_ = radius;
	//radius_ = radius;
	Tweener.addTween(radius_, targetRadius_, 0.5);
}

float ofxNode::getRadius() const
{
	return radius_;
}

float ofxNode::getTargetRadius() const
{
	return targetRadius_;
}

void ofxNode::updatePosition()
{
	if (!((speed_.x == 0) && (speed_.y == 0))) {
		const auto deltaTime = ofGetLastFrameTime();
		ofVec2f deltaPos(speed_.x * deltaTime, speed_.y * deltaTime);

		if (!boundRect_->inside(position_.x + deltaPos.x, position_.y))
		{
			if ((position_.x + deltaPos.x) < boundRect_->getMinX())
			{
				position_.x = boundRect_->getMinX() - position_.x - deltaPos.x + boundRect_->getMinX();
				speed_.x = speed_.x * -1;
			}

			if ((position_.x + deltaPos.x) >= boundRect_->getMaxX())
			{
				position_.x = boundRect_->getMaxX() - position_.x - deltaPos.x + boundRect_->getMaxX();
				speed_.x = speed_.x * -1;
			}
		}
		else
			position_.x += deltaPos.x;

		if (!boundRect_->inside(position_.x, position_.y + deltaPos.y))
		{
			if ((position_.y + deltaPos.y) < boundRect_->getMinY())
			{
				position_.y = boundRect_->getMinY() - position_.y - deltaPos.y + boundRect_->getMinY();
				speed_.y = speed_.y * -1;
			}

			if ((position_.y + deltaPos.y) >= boundRect_->getMaxY())
			{
				position_.y = boundRect_->getMaxY() - position_.y - deltaPos.y + boundRect_->getMaxY();
				speed_.y = speed_.y * -1;
			}
		}
		else
			position_.y += deltaPos.y;
	}
}
