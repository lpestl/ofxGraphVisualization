#include "ofxEdge.h"
#include "ofxNode.h"

void ofxEdge::setup()
{
	font_.loadFont("data\\tahoma\\TAHOMABD.ttf", 10);

}

//void ofxEdge::update()
//{
//}

void ofxEdge::draw(bool isWeightVisible)
{
	const auto srcNode = std::dynamic_pointer_cast<ofxNode>(sourceNode_);
	const auto dstNode = std::dynamic_pointer_cast<ofxNode>(destNode_);

	if (srcNode != nullptr && dstNode != nullptr)
	{
		auto startPoint = srcNode->getPosition();
		auto endPoint = dstNode->getPosition();
		ofDrawLine(startPoint, endPoint);

		if (isWeightVisible)
		{
			ofPushStyle();
			ofSetColor(ofColor::black);
			const auto len = ofVec2f(endPoint.x - startPoint.x, endPoint.y - startPoint.y);
			font_.drawString(ofToString(weight_), startPoint.x + len.x / 3 * 2, startPoint.y + len.y / 3 * 2);
			ofPopStyle();
		}
	}
}
