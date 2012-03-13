/*
 *  ofxPQLabsEventTypes.h
 *
 *  Created by Jason Van Cleave on 8/18/11.
 *
 */

#include "PQMTClient.h"
#include "ofMain.h"


struct TouchPointEvent
{
	TouchPointEvent(TouchPoint tp)
	{
		touchPoint = tp;
	}
	TouchPoint touchPoint;
	
};
	
struct SingleTouchGestureEvent
{
//TYPES
//	TG_TOUCH_START
//	TG_DOWN
//	TG_MOVE
//	TG_UP
	SingleTouchGestureEvent(TouchGesture tg)
	{
		touchGesture = tg;
		point = ofPoint(tg.params[0], tg.params[1]);
	}
	TouchGesture touchGesture;
	ofPoint point;
	
};

struct SingleTouchMoveEvent
{
//	TYPES
//	TG_MOVE_RIGHT
//	TG_MOVE_UP
//	TG_MOVE_LEFT
//	TG_MOVE_RIGHT
	SingleTouchMoveEvent(TouchGesture tg)
	{
		touchGesture = tg;
		point = ofPoint(tg.params[0], tg.params[1]);
	}
	TouchGesture touchGesture;
	ofPoint point;
	
};

struct SecondTouchEvent
{
//	TYPES
//	TG_SECOND_DOWN
//	TG_SECOND_UP
	SecondTouchEvent(TouchGesture tg)
	{
		touchGesture = tg;
		point1 = newFinger = ofPoint(tg.params[0], tg.params[1]);
		point2 = originalFinger = ofPoint(tg.params[2], tg.params[3]);
		
		stringstream ss;
		ss << "  Second Finger Down " 
		<< " New Finger X :" << tg.params[0]
		<< " New Finger Y :" << tg.params[1]
		<< " Original Finger X :" << tg.params[2]
		<< " Original Finger Y :" << tg.params[3]
		<< endl;
		ofLog(OF_LOG_VERBOSE,  "SecondTouchEvent " +ss.str());
	}
	TouchGesture touchGesture;
	ofPoint point1;
	ofPoint point2;
	ofPoint newFinger;
	ofPoint originalFinger;
	
	

};
	

struct SplitEvent 
{
//	TYPES
//	TG_SPLIT_START
//	TG_SPLIT_END
	SplitEvent(TouchGesture tg)
	{
		touchGesture = tg;
		point1 = finger1 = ofPoint(tg.params[0], tg.params[1]);
		point2 = finger2 = ofPoint(tg.params[2], tg.params[3]);
		
		stringstream ss;
		ss << "  SplitEvent " 
			<< " Finger 1 X :" << tg.params[0]
			<< " Finger 1 Y :" << tg.params[1]
			<< " Finger 2 X :" << tg.params[2]
			<< " Finger 2 Y :" << tg.params[3]
		<< endl;
		ofLog(OF_LOG_VERBOSE, ss.str());
	};
	TouchGesture touchGesture;
	ofPoint finger1;
	ofPoint finger2;
	ofPoint point1;
	ofPoint point2;
	
};

struct SplitMoveEvent 
{
//	TYPES
//	TG_SPLIT_APART
//	TG_SPLIT_CLOSE
	SplitMoveEvent(TouchGesture tg)
	{
		touchGesture = tg;
		delta = tg.params[0];
		differenceRatio = tg.params[1];
		point1 = finger1 = ofPoint(tg.params[2], tg.params[3]);
		point2 = finger2 = ofPoint(tg.params[4], tg.params[5]);
		
		stringstream ss;
		ss << "  SplitMoveEvent " 
		<< "Delta in pixels: "<< tg.params[0]
		<< " Difference Ratio :" << tg.params[1]
		<< " Finger 1 X :" << tg.params[2]
		<< " Finger 1 Y :" << tg.params[3]
		<< " Finger 2 X :" << tg.params[4]
		<< " Finger 2 Y :" << tg.params[5]
		<< endl;
		ofLog(OF_LOG_VERBOSE,  ss.str());
	};
	TouchGesture touchGesture;
	float delta;
	float differenceRatio;
	ofPoint finger1;
	ofPoint finger2;
	ofPoint point1;
	ofPoint point2;
	
};

	
struct RotateEvent 
{
//	TYPES
//	TG_ROTATE_START
//	TG_ROTATE_END
	RotateEvent(TouchGesture tg)
	{
		touchGesture = tg;
		point1 = anchorFinger = ofPoint(tg.params[0], tg.params[1]);
		point2 = rotatingFinger = ofPoint(tg.params[2], tg.params[3]);
		
		stringstream ss;
		ss << "  RotateEvent  " 
			<< " Anchor Finger X :" << tg.params[0]
			<< " Anchor Finger Y :" << tg.params[1]
			<< " Rotating Finger X :" << tg.params[2]
			<< " Rotating Finger Y :" << tg.params[3]
			<< endl;
		ofLog(OF_LOG_VERBOSE, ss.str());
	};
	TouchGesture touchGesture;
	ofPoint anchorFinger;
	ofPoint rotatingFinger;
	ofPoint point1;
	ofPoint point2;

};


struct RotatingEvent 
{
	RotatingEvent(TouchGesture tg)
	{
		// TYPES
		// TG_ROTATE_ANTICLOCK
		// TG_ROTATE_CLOCK
		touchGesture = tg;
		radians = tg.params[0];
		degrees = ofRadToDeg(radians);
		point1 = anchorFinger = ofPoint(tg.params[1], tg.params[2]);
		point2 = rotatingFinger = ofPoint(tg.params[3], tg.params[4]);
		stringstream ss;
		ss << "  RotatingEvent "
			<< " Radians :" << tg.params[0]
			<< " Anchor Finger X :" << tg.params[1]
			<< " Anchor Finger Y :" << tg.params[2]
			<< " Rotating Finger X :" << tg.params[3]
			<< " Rotating Finger Y :" << tg.params[4]
		<< endl;
		ofLog(OF_LOG_VERBOSE, ss.str());
	};
	TouchGesture touchGesture;
	float radians;
	float degrees;
	ofPoint anchorFinger;
	ofPoint rotatingFinger;
	ofPoint point1;
	ofPoint point2;
	
};

struct ParallelEvent 
{
//	TYPES
//	TG_NEAR_PARALLEL_DOWN
//	TG_NEAR_PARALLEL_MOVE
//	TG_NEAR_PARALLEL_UP
	ParallelEvent(TouchGesture tg)
	{
		touchGesture = tg;
		middlePosition = ofPoint(tg.params[0], tg.params[1]);
		point1 = finger1 = ofPoint(tg.params[2], tg.params[3]);
		point2 = finger2 = ofPoint(tg.params[4], tg.params[5]);
		stringstream ss;
		ss << "  Near Parallel Down" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
		<< " Finger 1 X :" << tg.params[2]
		<< " Finger 1 Y :" << tg.params[3]
		<< " Finger 2 X :" << tg.params[4]
		<< " Finger 2 Y :" << tg.params[5]
		<< endl;
		ofLog(OF_LOG_VERBOSE,  ss.str());
	};
	TouchGesture touchGesture;

	ofPoint middlePosition;
	ofPoint finger1;
	ofPoint finger2;
	ofPoint point1;
	ofPoint point2;
};



struct ParallelClickEvent
{
	//	TYPES
	//	TG_NEAR_PARALLEL_CLICK
	//	TG_NEAR_PARALLEL_DB_CLICK
	
	ParallelClickEvent(TouchGesture tg)
	{
		touchGesture = tg;
		middlePosition = ofPoint(tg.params[0], tg.params[1]);
		stringstream ss;
		ss << "  ParallelClickEvent" 
			<< " Middle Position X: "<< tg.params[0]
			<< " Middle Position Y :" << tg.params[1]
		<< endl;
		ofLog(OF_LOG_VERBOSE, ss.str());
	};
	TouchGesture touchGesture;
	ofPoint middlePosition;
};

struct ParallelMoveEvent 
{
	//	TYPES
	//	TG_NEAR_PARALLEL_MOVE_RIGHT
	//	TG_NEAR_PARALLEL_MOVE_LEFT
	//	TG_NEAR_PARALLEL_MOVE_UP
	//	TG_NEAR_PARALLEL_MOVE_DOWN
	
	ParallelMoveEvent(TouchGesture tg)
	{
		touchGesture = tg;
		middlePosition = ofPoint(tg.params[0], tg.params[1]);
		stringstream ss;
		ss << "  ParallelMoveEvent" 
			<< " Middle Position X: "<< tg.params[0]
			<< " Middle Position Y :" << tg.params[1]
		<< endl;
		ofLog(OF_LOG_VERBOSE, ss.str());
	};
	TouchGesture touchGesture;
	ofPoint middlePosition;
};

struct MultiEvent 
{
//	TYPES
//	TG_MULTI_DOWN
//	TG_MULTI_UP
//	TG_MULTI_MOVE
	MultiEvent(TouchGesture tg)
	{
		touchGesture = tg;
		middlePosition = ofPoint(tg.params[0], tg.params[1]);
		stringstream ss;
		ss << "  MultiEvent (+3 fingers)" 
			<< " Middle Position X: "<< tg.params[0]
			<< " Middle Position Y :" << tg.params[1]
		<< endl;
		ofLog(OF_LOG_VERBOSE, ss.str());
	};
	TouchGesture touchGesture;
	
	ofPoint middlePosition;
};

struct MultiMoveEvent 
{
	//	TYPES
	//	TG_MULTI_MOVE_RIGHT
	//	TG_MULTI_MOVE_LEFT
	//	TG_MULTI_MOVE_DOWN
	//	TG_MULTI_MOVE_UP
	MultiMoveEvent(TouchGesture tg)
	{
		touchGesture = tg;
		middlePosition = ofPoint(tg.params[0], tg.params[1]);
		stringstream ss;
		ss << "  MultiMoveEvent(+3 fingers)" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
		<< endl;
		ofLog(OF_LOG_VERBOSE, ss.str());
	};
	TouchGesture touchGesture;
	
	ofPoint middlePosition;
};

struct GestureClearEvent 
{
	GestureClearEvent(TouchGesture tg)
	{
		touchGesture = tg;
		stringstream ss;
		ss << "GestureClearEvent "
			<< "  All fingers are leaving" 
		<< endl;
		ofLog(OF_LOG_VERBOSE, ss.str());
		
	}
	TouchGesture touchGesture;
};

struct BigTouchEvent 
{
//	TYPES
//	TG_BIG_UP
//	TG_BIG_MOVE
//	TG_BIG_DOWN
	BigTouchEvent(TouchGesture tg)
	{
		touchGesture = tg;
		fistPosition = ofPoint(tg.params[0], tg.params[1]);
		stringstream ss;
		ss << "BigTouchEvent "
			<< "  Fist size object" 
			<< " fistPosition X: "<< tg.params[0]
			<< " fistPosition Y :" << tg.params[1]
		<< endl;
		ofLog(OF_LOG_VERBOSE, ss.str());
		
	}
	TouchGesture touchGesture;
	ofPoint fistPosition;
};
