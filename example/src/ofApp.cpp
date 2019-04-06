#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	grapph_.init("data\\edges.csv");

	for (auto && matrix : grapph_.adjacency_matrix_)
	{
		for (auto && value : grapph_.adjacency_matrix_[matrix.first])
		{
			if (value.second == nullptr)
				std::cout << 0 << " ";
			else
				std::cout << value.second.get()->getWeight() << " ";
		}
		std::cout << std::endl;
	}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(131, 219, 231), ofColor(38, 169, 241));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
