#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	//
	connection.connect("127.0.0.1");
	ofAddListener(connection.singleTouchGestureEventDispatcher, this, &testApp::onSingleTouchGestureEvent);
	ofAddListener(connection.singleTouchMoveGestureEventDispatcher, this, &testApp::onSingleTouchMoveEvent);
	ofAddListener(connection.bigTouchEventDispatcher, this, &testApp::onBigTouchEvent);
	ofAddListener(connection.rotateEventDispatcher, this, &testApp::onRotateEvent);
	ofAddListener(connection.rotatingEventDispatcher, this, &testApp::onRotatingEvent);
	ofAddListener(connection.secondTouchEventDispatcher, this, &testApp::onSecondTouchEvent);
	ofAddListener(connection.splitEventDispatcher, this, &testApp::onSplitEvent);
	ofAddListener(connection.splitMoveEventDispatcher, this, &testApp::onSplitMoveEvent);
	ofAddListener(connection.parallelEventDispatcher, this, &testApp::onParallelEvent);
	ofAddListener(connection.parallelClickEventDispatcher, this, &testApp::onParallelClickEvent);
	ofAddListener(connection.parallelMoveEventDispatcher, this, &testApp::onParallelMoveEvent);
	ofAddListener(connection.multiEventDispatcher, this, &testApp::onMultiEvent);
	ofAddListener(connection.multiMoveEventDispatcher, this, &testApp::onMultiMoveEvent);
	ofAddListener(connection.gestureClearEventDispatcher, this, &testApp::onGestureClearEvent);
	
	ofAddListener(connection.touchEventDispatcher, this, &testApp::onTouchPoint);

}
void testApp::onTouchPoint(TouchPointEvent & event)
{
	
	stringstream ss;
	 ss << "testApp::onTouchPoint: " 
		<< "touchPoint.id: " << event.touchPoint.id
		<< " touchPoint.x: " << event.touchPoint.x
		<< " touchPoint.y: " << event.touchPoint.y
		<< " touchPoint.dx: " << event.touchPoint.dx
		<< " touchPoint.dy: " << event.touchPoint.dy
	<< endl;
	
	cout << ss.str() << endl;
	
}
void testApp::onSingleTouchGestureEvent(SingleTouchGestureEvent & event)
{
	cout << "testApp::onSingleTouchGestureEvent: " << endl;
}


void testApp::onSingleTouchMoveEvent(SingleTouchMoveEvent & event)
{
	cout << "testApp::onSingleTouchMoveEvent: " << endl;
}

void testApp::onBigTouchEvent(BigTouchEvent & event)
{
	cout << "testApp::onBigTouchEvent: " << endl;
}

void testApp::onRotateEvent(RotateEvent & event)
{
	cout << "testApp::onRotateEvent: " << endl;
}
				   
void testApp::onRotatingEvent(RotatingEvent & event)
{
	cout << "testApp::onRotatingEvent: " << endl;
}

void testApp::onSecondTouchEvent(SecondTouchEvent & event)
{
	cout << "testApp::onSecondTouchEvent: " << endl;
}
				   
void testApp::onSplitEvent(SplitEvent & event)
{
	cout << "testApp::onSplitEvent: " << endl;
}
				   
void testApp::onSplitMoveEvent(SplitMoveEvent & event)
{
	cout << "testApp::onSplitMoveEvent: " << endl;
}
				   
void testApp::onParallelEvent(ParallelEvent & event)
{
	cout << "testApp::onParallelEvent: " << endl;
}
				   
void testApp::onParallelClickEvent(ParallelClickEvent & event)
{
	cout << "testApp::onParallelClickEvent: " << endl;
}
				   
void testApp::onParallelMoveEvent(ParallelMoveEvent & event)
{
	cout << "testApp::onParallelMoveEvent: " << endl;
}
				   
void testApp::onMultiEvent(MultiEvent & event)
{
	cout << "testApp::onMultiEvent: " << endl;
}
				   
void testApp::onMultiMoveEvent(MultiMoveEvent & event)
{
	cout << "testApp::onMultiMoveEvent: " << endl;
}

void testApp::onGestureClearEvent(GestureClearEvent & event)
{
	cout << "testApp::onGestureClearEvent: " << endl;
}
				   

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 'v')
	{
		ofSetLogLevel(OF_LOG_VERBOSE);
	}
	if (key =='s') 
	{
		ofSetLogLevel(OF_LOG_SILENT);
	}
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

