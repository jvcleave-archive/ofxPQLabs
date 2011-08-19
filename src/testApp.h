#pragma once

#include "ofMain.h"
#include "ofxPQLabs.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		ofxPQLabs connection;
	void onSingleTouchGestureEvent(SingleTouchGestureEvent & event);
	void onSingleTouchMoveEvent(SingleTouchMoveEvent & event);

	void onRotateEvent(RotateEvent & event);
	void onRotatingEvent(RotatingEvent & event);

	void onSecondTouchEvent(SecondTouchEvent & event);
	
	void onSplitEvent(SplitEvent & event);
	void onSplitMoveEvent(SplitMoveEvent & event);
	
	void onParallelEvent(ParallelEvent & event);
	void onParallelClickEvent(ParallelClickEvent & event);
	void onParallelMoveEvent(ParallelMoveEvent & event);
	
	void onMultiEvent(MultiEvent & event);
	void onMultiMoveEvent(MultiMoveEvent & event);
	
	void onGestureClearEvent(GestureClearEvent & event);
};
