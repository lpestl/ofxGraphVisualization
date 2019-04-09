#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	grapph_.setup(ofRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight()));
	grapph_.init("data\\edges.csv");
	index_ = 6;
}

//--------------------------------------------------------------
void ofApp::update(){
	//node_->update();
	grapph_.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(131, 219, 231), ofColor(38, 169, 241));

	//node_->draw();
	grapph_.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//grapph_.addNode(++index_);
	grapph_.setSpeed(ofVec2f(-100, -100), ofVec2f(100, 100));
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
