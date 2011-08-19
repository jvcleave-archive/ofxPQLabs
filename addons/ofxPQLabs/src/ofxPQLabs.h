//+---------------------------------------------------------------------------
//
//  PQLabs.
//
//  Copyright (c) PQLabs.  All rights reserved.
//
//
//  Contents:   ofxPQLabs code for MultiTouch Clinet SDK APIs.
//
//	Date:		2008-12-19
//
//----------------------------------------------------------------------------

#ifndef OFXPQLabs_
#define OFXPQLabs_

#include "ofMain.h"
#include "PQMTClient.h"
#include "ofxPQLabsEventTypes.h"





class ofxPQLabs{
public:
	ofxPQLabs();
	~ofxPQLabs();
	
	bool isVerbose;
	void log(const string & message);
	void connect(const char * ipAddress);
	ofEvent<SingleTouchGestureEvent> singleTouchGestureEventDispatcher;
	ofEvent<SingleTouchMoveEvent> singleTouchMoveGestureEventDispatcher;
	ofEvent<SecondTouchEvent> secondTouchEventDispatcher;
	ofEvent<SplitEvent> splitEventDispatcher;
	ofEvent<SplitMoveEvent> splitMoveEventDispatcher;

	ofEvent<RotateEvent> rotateEventDispatcher;
	ofEvent<RotatingEvent> rotatingEventDispatcher;
	ofEvent<ParallelEvent> parallelEventDispatcher;
	ofEvent<ParallelMoveEvent> parallelMoveEventDispatcher;
	ofEvent<MultiEvent> multiEventDispatcher;
	ofEvent<MultiMoveEvent> multiMoveEventDispatcher;
	ofEvent<ParallelClickEvent> parallelClickEventDispatcher;
	ofEvent<GestureClearEvent> gestureClearEventDispatcher;

	
	
private:
#pragma mark Callback functions
	// onReceivePointFrame: function to handle when recieve touch point frame
	//	the unmoving touch point won't be sent from server. The new touch point with its pointevent is TP_DOWN
	//	and the leaving touch point with its pointevent will be always sent from server;
	static void onReceivePointFrame(int frame_id,int time_stamp,int moving_point_count,const TouchPoint * moving_point_array, void * call_back_object);
	
	// onReceivePointFrame: function to handle when recieve touch gesture
	static void onReceiveGesture(const TouchGesture & ges, void * call_back_object);
	
	// onServerBreak: function to handle when server break(disconnect or network error)
	static void onServerBreak(void * param, void * call_back_object);
	
	// onReceiveError: function to handle when some errors occur on the process of receiving touch datas.
	static void onReceiveError(int err_code,void * call_back_object);
	//
	static void onGetServerResolution(int x, int y, void * call_back_object);
#pragma mark END Callback functions
	
	// functions to handle TouchGestures, attention the means of the params
	void initializeFunctionsOnTouchGestures();
	
	// set the call back functions while reciving touch data;
	void setTouchDataCallbacks();

	void onTouchPoint(const TouchPoint & touchPoint);
	
	void onTouchGesture(const TouchGesture & tg);
	//

	//here use function pointer table to handle the different gesture type;
	
	//Some below are combined until I decide they are better broken up again :/
	typedef void (*PFuncOnTouchGesture)(const TouchGesture & tg, void * call_object);
	static void onTG_Default(const TouchGesture & tg,void * call_object); // just show the gesture

	static void onSingleTouchGesture(const TouchGesture & tg,void * call_object);
	static void onSingleTouchMove(const TouchGesture & tg,void * call_object);
	
	static void onSecondTouch(const TouchGesture & tg,void * call_object);

	static void onSplit(const TouchGesture & tg,void * call_object);
	static void onSplitMove(const TouchGesture & tg,void * call_object);

	static void onRotate(const TouchGesture & tg,void * call_object);
	static void onRotating(const TouchGesture & tg,void * call_object);

	static void onParallel(const TouchGesture & tg,void * call_object);
	static void onParallelClick(const TouchGesture & tg,void * call_object);
	static void onParallelMove(const TouchGesture & tg,void * call_object);
	
	static void onMulti(const TouchGesture & tg,void * call_object);
	static void onMultiMove(const TouchGesture & tg,void * call_object);
	
	// onTG_TouchEnd: to clear what need to clear;
	static void onGesturesClear(const TouchGesture & tg,void * call_object);
	
	
	//
	
private:
	PFuncOnTouchGesture touchGestureTypes[TG_TOUCH_END + 1];

// sample code end
////////////////////////////////////assistant functions /////////////////////////////////

////////////////////////////////////assistant functions /////////////////////////////////
};
#endif // end of header

