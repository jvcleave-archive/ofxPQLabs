#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetLogLevel(OF_LOG_VERBOSE);
	connection.setListener(this);
	connection.connect("127.0.0.1");
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

void testApp::onTG_Default(const TouchGesture & tg,void * call_object) // just show the gesture
{
	
	stringstream ss;
	ss << "Gesture name:"<< GetGestureName(tg) << " Type:" << tg.type << " Param size:" << tg.param_size << " ";
	for(int i = 0; i < tg.param_size; ++ i)
		ss << tg.params[i] << " ";
	ss << endl;
	
	
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_Default: "+ ofToString(ss));
}