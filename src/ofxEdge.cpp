#include "ofxEdge.h"
#include "ofxNode.h"
#include "of3dUtils.h"

void ofxEdge::setup(std::shared_ptr<ofxTrueTypeFontUC> font)
{
	captureFont_ = font;
}

void ofxEdge::update()
{
	const auto srcNode = std::dynamic_pointer_cast<ofxNode>(sourceNode_);
	const auto dstNode = std::dynamic_pointer_cast<ofxNode>(destNode_);

	float len = std::sqrt((dstNode->getPosition().x - srcNode->getPosition().x) * (dstNode->getPosition().x - srcNode->getPosition().x) + (dstNode->getPosition().y - srcNode->getPosition().y) * (dstNode->getPosition().y - srcNode->getPosition().y));
	float cos_a = (dstNode->getPosition().y - srcNode->getPosition().y) / len;
	float sin_a = (dstNode->getPosition().x - srcNode->getPosition().x) / len;

	from_point_.set(srcNode->getPosition().x + cos_a * 5, srcNode->getPosition().y - sin_a * 5);
	to_point_.set(dstNode->getPosition().x + cos_a * 5, dstNode->getPosition().y - sin_a * 5);
}

void ofxEdge::draw(bool isWeightVisible)
{
	const auto srcNode = std::dynamic_pointer_cast<ofxNode>(sourceNode_);
	const auto dstNode = std::dynamic_pointer_cast<ofxNode>(destNode_);

	ofPushMatrix();
	ofTranslate(from_point_);
	
	float len = std::sqrt((dstNode->getPosition().x - srcNode->getPosition().x) * (dstNode->getPosition().x - srcNode->getPosition().x) + (dstNode->getPosition().y - srcNode->getPosition().y) * (dstNode->getPosition().y - srcNode->getPosition().y));

	ofSetLineWidth(len / (len - dstNode->getRadius()));
	ofScale((len - dstNode->getRadius()) / len);
	ofDrawArrow(ofVec3f(0), ofVec3f(to_point_.x - from_point_.x, to_point_.y - from_point_.y), 5);

	ofPopMatrix();

	if (isWeightVisible)
	{
		ofPushStyle();
		ofSetColor(ofColor::black);
		const auto len = ofVec2f(to_point_.x - from_point_.x, to_point_.y - from_point_.y);
		if ((captureFont_ != nullptr) && (captureFont_->isLoaded()))
			captureFont_->drawString(ofToString(weight_), from_point_.x + len.x / 3 * 2, from_point_.y + len.y / 3 * 2);
		else
			ofDrawBitmapString(ofToString(weight_), from_point_.x + len.x / 3 * 2, from_point_.y + len.y / 3 * 2);
		ofPopStyle();
	}
}
