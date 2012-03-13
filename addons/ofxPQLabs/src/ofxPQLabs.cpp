//+---------------------------------------------------------------------------
//
//  PQLabs.
//
//  Copyright (c) PQLabs.  All rights reserved.
//
//  File:       SDK_ofxPQLabsCode.cpp
//
//  Contents:   Implementation of SDK_ofxPQLabsCode.h
//
//	Date:		2008-12-19
//
//----------------------------------------------------------------------------

#include "ofxPQLabs.h"


ofxPQLabs::ofxPQLabs()
{
	isVerbose = false;
	memset(touchGestureTypes,0, sizeof(touchGestureTypes));
}

ofxPQLabs::~ofxPQLabs()
{
	DisconnectServer();
}


#pragma mark functions
void ofxPQLabs::connect(const char * ipAddress = "127.0.0.1")
{
	int err_code = PQMTE_SUCESS;

	// Initialize Gesture Handlers;
	initializeFunctionsOnTouchGestures();
	
	// set the functions on server callback
	setTouchDataCallbacks();
	
	// connect server
	ofLog(OF_LOG_VERBOSE, "ofxPQLabs::connect Connecting to server...");
	if((err_code = ConnectServer(ipAddress)) != PQMTE_SUCESS)
	{
		
		ofLog(OF_LOG_ERROR, "ofxPQLabs::connect could not connect to server"+ofToString(err_code));
	}else 
	{
		ofLog(OF_LOG_VERBOSE, "ofxPQLabs::connect Connected to server...");
		TouchClientRequest tcq = {0};
		tcq.app_id = GetTrialAppID();
		tcq.type = RQST_RAWDATA_ALL | RQST_GESTURE_ALL;
		if((err_code = SendRequest(tcq)) != PQMTE_SUCESS)
		{
			ofLog(OF_LOG_ERROR, "ofxPQLabs::connect could not send request"+ofToString(err_code));
		}
		//you can set the move_threshold when the tcq.type is RQST_RAWDATA_INSIDE;
		
		if (tcq.type == RQST_RAWDATA_INSIDE)
		{
			int move_threshold = 1;// 1 pixel
			if((err_code = SendThreshold(move_threshold) != PQMTE_SUCESS))
			{
				ofLog(OF_LOG_ERROR, "ofxPQLabs::connect could not send threshold: Error Code: "+ofToString(err_code));
			}

		}
		//get Screen Resolution
		if((err_code = GetServerResolution(onGetServerResolution, NULL)) != PQMTE_SUCESS)
		{
			ofLog(OF_LOG_ERROR, "ofxPQLabs::connect could not get Screen Resolution"+ofToString(err_code));
		}
		//
		// start receiving
		cout << " send request success, start recv." << endl;
	}


}

void ofxPQLabs:: initializeFunctionsOnTouchGestures()
{
	ofLog(OF_LOG_VERBOSE, "ofxPQLabs::initializeFunctionsOnTouchGestures");
	touchGestureTypes[TG_TOUCH_START] = &ofxPQLabs::onSingleTouchGesture;
	touchGestureTypes[TG_DOWN] = &ofxPQLabs::onSingleTouchGesture;
	touchGestureTypes[TG_MOVE] = &ofxPQLabs::onSingleTouchGesture;
	touchGestureTypes[TG_UP] = &ofxPQLabs::onSingleTouchGesture;
	
	touchGestureTypes[TG_MOVE_RIGHT] = &ofxPQLabs::onSingleTouchMove;
	touchGestureTypes[TG_MOVE_UP] = &ofxPQLabs::onSingleTouchMove;
	touchGestureTypes[TG_MOVE_LEFT] = &ofxPQLabs::onSingleTouchMove;
	touchGestureTypes[TG_MOVE_DOWN] = &ofxPQLabs::onSingleTouchMove;

	touchGestureTypes[TG_BIG_UP] = &ofxPQLabs::onBigTouch;
	touchGestureTypes[TG_BIG_DOWN] = &ofxPQLabs::onBigTouch;
	touchGestureTypes[TG_BIG_MOVE] = &ofxPQLabs::onBigTouch;
	
	

	touchGestureTypes[TG_SECOND_DOWN] = &ofxPQLabs::onSecondTouch;
	touchGestureTypes[TG_SECOND_UP] = &ofxPQLabs::onSecondTouch;

	touchGestureTypes[TG_SPLIT_START] = &ofxPQLabs::onSplit;
	touchGestureTypes[TG_SPLIT_END] = &ofxPQLabs::onSplit;
	
	touchGestureTypes[TG_SPLIT_APART] = &ofxPQLabs::onSplitMove;
	touchGestureTypes[TG_SPLIT_CLOSE] = &ofxPQLabs::onSplitMove;
	
	
	touchGestureTypes[TG_ROTATE_START] = &ofxPQLabs::onRotate;
	touchGestureTypes[TG_ROTATE_END] = &ofxPQLabs::onRotate;
	
	touchGestureTypes[TG_ROTATE_ANTICLOCK] = &ofxPQLabs::onRotating;
	touchGestureTypes[TG_ROTATE_CLOCK] = &ofxPQLabs::onRotating;
	
	

	touchGestureTypes[TG_NEAR_PARALLEL_DOWN] = &ofxPQLabs::onParallel;
	touchGestureTypes[TG_NEAR_PARALLEL_MOVE] = &ofxPQLabs::onParallel;
	touchGestureTypes[TG_NEAR_PARALLEL_UP] = &ofxPQLabs::onParallel;
	
	
	touchGestureTypes[TG_NEAR_PARALLEL_CLICK] = &ofxPQLabs::onParallelClick;
	touchGestureTypes[TG_NEAR_PARALLEL_DB_CLICK] = &ofxPQLabs::onParallelClick;
	

	touchGestureTypes[TG_NEAR_PARALLEL_MOVE_RIGHT] = &ofxPQLabs::onParallelMove;
	touchGestureTypes[TG_NEAR_PARALLEL_MOVE_UP] = &ofxPQLabs::onParallelMove;
	touchGestureTypes[TG_NEAR_PARALLEL_MOVE_LEFT] = &ofxPQLabs::onParallelMove;
	touchGestureTypes[TG_NEAR_PARALLEL_MOVE_DOWN] = &ofxPQLabs::onParallelMove;
	

	touchGestureTypes[TG_MULTI_DOWN] = &ofxPQLabs::onMulti;
	touchGestureTypes[TG_MULTI_MOVE] = &ofxPQLabs::onMulti;
	touchGestureTypes[TG_MULTI_UP] = &ofxPQLabs::onMulti;
	
	

	touchGestureTypes[TG_MULTI_MOVE_RIGHT] = &ofxPQLabs::onMultiMove;
	touchGestureTypes[TG_MULTI_MOVE_UP] = &ofxPQLabs::onMultiMove;
	touchGestureTypes[TG_MULTI_MOVE_LEFT] = &ofxPQLabs::onMultiMove;
	touchGestureTypes[TG_MULTI_MOVE_DOWN] = &ofxPQLabs::onMultiMove;
	

	
	touchGestureTypes[TG_TOUCH_END] = &ofxPQLabs::onGesturesClear;
}


void ofxPQLabs::setTouchDataCallbacks()
{
	PFuncOnReceivePointFrame onReceivePointFrameAPI = SetOnReceivePointFrame(&ofxPQLabs::onReceivePointFrame, this);
	PFuncOnReceiveGesture onReceiveGestureAPI = SetOnReceiveGesture(&ofxPQLabs::onReceiveGesture, this);
	PFuncOnServerBreak onServerBreakAPI = SetOnServerBreak(&ofxPQLabs::onServerBreak, NULL);
	PFuncOnReceiveError onReceiveErrorAPI = SetOnReceiveError(&ofxPQLabs::onReceiveError, NULL);
}

void ofxPQLabs:: onReceivePointFrame(int frame_id, int time_stamp, int moving_point_count, const TouchPoint * moving_point_array, void * call_back_object)
{
	ofxPQLabs * connection = static_cast<ofxPQLabs*>(call_back_object);
	const char * tp_event[] = 
	{
		"down",
		"move",
		"up",
	};
	stringstream ss;
	ss << " frame_id:" << frame_id << " time:"  << time_stamp << " ms" << " moving point count:" << moving_point_count;
	ofLog(OF_LOG_VERBOSE,  ofToString(ss));
	for(int i = 0; i < moving_point_count; ++ i)
	{
		TouchPoint tp = moving_point_array[i];
		connection->onTouchPoint(tp);
	}
}

void ofxPQLabs:: onReceiveGesture(const TouchGesture & ges, void * call_back_object)
{
	ofxPQLabs * connection = static_cast<ofxPQLabs*>(call_back_object);
	connection->onTouchGesture(ges);
}

void ofxPQLabs:: onServerBreak(void * param, void * call_back_object)
{
	
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs:: onServerBreak Disconnecting Server");
	DisconnectServer();
}

void ofxPQLabs::onReceiveError(int err_code, void * call_back_object)
{
	switch(err_code)
	{
	case PQMTE_RCV_INVALIDATE_DATA:
		ofLog(OF_LOG_ERROR,  "ofxPQLabs::onReceiveError Invalid data");
		break;
			
	case PQMTE_SERVER_VERSION_OLD:
		ofLog(OF_LOG_ERROR,  "ofxPQLabs::onReceiveError The multi-touch server is old for this client, please update the multi-touch server.");
		break;
			
	default:
		ofLog(OF_LOG_ERROR,  "ofxPQLabs::onReceiveError Socket error, Error Code: " +ofToString(err_code));
	}
}

void ofxPQLabs:: onGetServerResolution(int x, int y, void * call_back_object)
{
	cout << " server resolution:" << x << "," << y << endl;
}

// here, just record the position of point,
//	you can do mouse map like "onTG_Down" etc;
void ofxPQLabs:: onTouchPoint(const TouchPoint & touchPoint)
{
	TouchPointEvent event(touchPoint);
	ofNotifyEvent(touchEventDispatcher, event);
	stringstream ss;
	switch(touchPoint.point_event)
	{
	case TP_DOWN:
		ss << "  point " << touchPoint.id << " come at (" << touchPoint.x << "," << touchPoint.y 
			<< ") width:" << touchPoint.dx << " height:" << touchPoint.dy << endl;
			ofLog(OF_LOG_VERBOSE,  "ofxPQLabs:: onTouchPoint TP_DOWN" +ss.str());
		break;
			
	case TP_MOVE:
		ss << "  point " << touchPoint.id << " move at (" << touchPoint.x << "," << touchPoint.y 
			<< ") width:" << touchPoint.dx << " height:" << touchPoint.dy << endl;
			ofLog(OF_LOG_VERBOSE,  "ofxPQLabs:: onTouchPoint TP_MOVE" +ss.str());
		break;
			
	case TP_UP:
		ss << "  point " << touchPoint.id << " leave at (" << touchPoint.x << "," << touchPoint.y 
			<< ") width:" << touchPoint.dx << " height:" << touchPoint.dy << endl;
			ofLog(OF_LOG_VERBOSE,  "ofxPQLabs:: onTouchPoint TP_UP" +ss.str());
		break;
	}
}

void ofxPQLabs:: onTouchGesture(const TouchGesture & tg)
{
	if(TG_NO_ACTION == tg.type)
		return ;
	onTG_Default(tg, this);
	PFuncOnTouchGesture touchGestureType = touchGestureTypes[tg.type];
	if(touchGestureType != NULL)
	{
		touchGestureType(tg, this);
	}
}

#pragma mark Gesture Callbacks: Basic 

void ofxPQLabs:: onSingleTouchGesture(const TouchGesture & tg, void * call_object)
{
	SingleTouchGestureEvent event(tg);
	ofxPQLabs* labsInstance = static_cast<ofxPQLabs*>(call_object);
	ofNotifyEvent(labsInstance->singleTouchGestureEventDispatcher, event);
}



void ofxPQLabs:: onTG_Default(const TouchGesture & tg,void * call_object) // just show the gesture
{
	
	stringstream ss;
	ss << "Gesture name:"<< GetGestureName(tg) << " Type:" << tg.type << " Param size:" << tg.param_size << " ";
	for(int i = 0; i < tg.param_size; ++ i)
		ss << tg.params[i] << " ";
	ss << endl;
	
	
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_Default: "+ ss.str());
}



#pragma mark Gesture Callbacks: Directional Moves 
void ofxPQLabs:: onSingleTouchMove(const TouchGesture & tg, void * call_object)
{
	SingleTouchMoveEvent event(tg);
	ofxPQLabs* labsInstance = static_cast<ofxPQLabs*>(call_object);
	ofNotifyEvent(labsInstance->singleTouchMoveGestureEventDispatcher, event);
}

#pragma mark Gesture Callbacks: Second Down 
void ofxPQLabs:: onSecondTouch(const TouchGesture & tg, void * call_object)
{
	SecondTouchEvent event(tg);
	ofxPQLabs* labsInstance = static_cast<ofxPQLabs*>(call_object);
	ofNotifyEvent(labsInstance->secondTouchEventDispatcher, event);
}


#pragma mark Gesture Callbacks: Split
void ofxPQLabs:: onSplit(const TouchGesture & tg, void * call_object)
{
	SplitEvent event(tg);
	ofxPQLabs* labsInstance = static_cast<ofxPQLabs*>(call_object);
	ofNotifyEvent(labsInstance->splitEventDispatcher, event);
}


void ofxPQLabs:: onSplitMove(const TouchGesture & tg, void * call_object)
{
	SplitMoveEvent event(tg);
	ofxPQLabs* labsInstance = static_cast<ofxPQLabs*>(call_object);
	ofNotifyEvent(labsInstance->splitMoveEventDispatcher, event);
}


#pragma mark Gesture Callbacks: Rotate
void ofxPQLabs:: onRotate(const TouchGesture & tg, void * call_object)
{
	RotateEvent event(tg);
	ofxPQLabs* labsInstance = static_cast<ofxPQLabs*>(call_object);
	ofNotifyEvent(labsInstance->rotateEventDispatcher, event);
}

void ofxPQLabs:: onRotating(const TouchGesture & tg, void * call_object)
{
	RotatingEvent event(tg);
	ofxPQLabs* labsInstance = static_cast<ofxPQLabs*>(call_object);
	ofNotifyEvent(labsInstance->rotatingEventDispatcher, event);
}



#pragma mark Gesture Callbacks: Near Parallel 
void ofxPQLabs:: onParallel(const TouchGesture & tg, void * call_object)
{
	ParallelEvent event(tg);
	ofxPQLabs* labsInstance = static_cast<ofxPQLabs*>(call_object);
	ofNotifyEvent(labsInstance->parallelEventDispatcher, event);
}


void ofxPQLabs:: onParallelClick(const TouchGesture & tg, void * call_object)
{
	ParallelClickEvent event(tg);
	ofxPQLabs* labsInstance = static_cast<ofxPQLabs*>(call_object);
	ofNotifyEvent(labsInstance->parallelClickEventDispatcher, event);
}



#pragma mark Gesture Callbacks: Near Parallel Directional Move 
void ofxPQLabs:: onParallelMove(const TouchGesture & tg, void * call_object)
{
	ParallelMoveEvent event(tg);
	ofxPQLabs* labsInstance = static_cast<ofxPQLabs*>(call_object);
	ofNotifyEvent(labsInstance->parallelMoveEventDispatcher, event);
}


#pragma mark Gesture Callbacks: Multi 

void ofxPQLabs:: onMulti(const TouchGesture & tg, void * call_object)
{
	MultiEvent event(tg);
	ofxPQLabs* labsInstance = static_cast<ofxPQLabs*>(call_object);
	ofNotifyEvent(labsInstance->multiEventDispatcher, event);
}


#pragma mark Gesture Callbacks: Multi Directional Move 
void ofxPQLabs:: onMultiMove(const TouchGesture & tg, void * call_object)
{
	MultiMoveEvent event(tg);
	ofxPQLabs* labsInstance = static_cast<ofxPQLabs*>(call_object);
	ofNotifyEvent(labsInstance->multiMoveEventDispatcher, event);
}

#pragma mark Gesture Callbacks: Big TouchGesture 
void ofxPQLabs:: onBigTouch(const TouchGesture & tg, void * call_object)
{
	BigTouchEvent event(tg);
	ofxPQLabs* labsInstance = static_cast<ofxPQLabs*>(call_object);
	ofNotifyEvent(labsInstance->bigTouchEventDispatcher, event);
}


#pragma mark Gesture Callbacks: END
// onTG_TouchEnd: to clear what need to clear
void ofxPQLabs:: onGesturesClear(const TouchGesture & tg,void * call_object)
{

	GestureClearEvent event(tg);
	ofxPQLabs* labsInstance = static_cast<ofxPQLabs*>(call_object);
	ofNotifyEvent(labsInstance->gestureClearEventDispatcher, event);
	
}


