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
	touchGestureTypes[TG_TOUCH_START] = onTG_TouchStart;
	touchGestureTypes[TG_DOWN] = &ofxPQLabs::onTG_Down;
	touchGestureTypes[TG_MOVE] = &ofxPQLabs::onTG_Move;
	touchGestureTypes[TG_UP] = &ofxPQLabs::onTG_Up;
	
	touchGestureTypes[TG_MOVE_RIGHT] = &ofxPQLabs::onTG_MoveRight;
	touchGestureTypes[TG_MOVE_UP] = &ofxPQLabs::onTG_MoveUp;
	touchGestureTypes[TG_MOVE_LEFT] = &ofxPQLabs::onTG_MoveLeft;
	touchGestureTypes[TG_MOVE_DOWN] = &ofxPQLabs::onTG_MoveDown;


	touchGestureTypes[TG_SECOND_DOWN] = &ofxPQLabs::onTG_SecondDown;
	touchGestureTypes[TG_SECOND_UP] = &ofxPQLabs::onTG_SecondUp;

	touchGestureTypes[TG_SPLIT_START] = &ofxPQLabs::onTG_SplitStart;
	touchGestureTypes[TG_SPLIT_APART] = &ofxPQLabs::onTG_SplitApart;
	touchGestureTypes[TG_SPLIT_CLOSE] = &ofxPQLabs::onTG_SplitClose;
	touchGestureTypes[TG_SPLIT_END] = &ofxPQLabs::onTG_SplitEnd;
	
	
	touchGestureTypes[TG_ROTATE_START] = &ofxPQLabs::onTG_RotateStart;
	touchGestureTypes[TG_ROTATE_ANTICLOCK] = &ofxPQLabs::onTG_RotateCounterClockwise;
	touchGestureTypes[TG_ROTATE_CLOCK] = &ofxPQLabs::onTG_RotateClockwise;
	touchGestureTypes[TG_ROTATE_END] = &ofxPQLabs::onTG_RotateEnd;
	

	touchGestureTypes[TG_NEAR_PARREL_DOWN] = &ofxPQLabs::onTG_NearParallelDown;
	touchGestureTypes[TG_NEAR_PARREL_MOVE] = &ofxPQLabs::onTG_NearParallelMove;
	touchGestureTypes[TG_NEAR_PARREL_UP] = &ofxPQLabs::onTG_NearParallelUp;
	touchGestureTypes[TG_NEAR_PARREL_CLICK] = &ofxPQLabs::onTG_NearParallelClick;
	touchGestureTypes[TG_NEAR_PARREL_DB_CLICK] = &ofxPQLabs::onTG_NearParallelDoubleClick;
	

	touchGestureTypes[TG_NEAR_PARREL_MOVE_RIGHT] = &ofxPQLabs::onTG_NearParallelMoveRight;
	touchGestureTypes[TG_NEAR_PARREL_MOVE_UP] = &ofxPQLabs::onTG_NearParallelMoveUp;
	touchGestureTypes[TG_NEAR_PARREL_MOVE_LEFT] = &ofxPQLabs::onTG_NearParallelMoveLeft;
	touchGestureTypes[TG_NEAR_PARREL_MOVE_DOWN] = &ofxPQLabs::onTG_NearParallelMoveDown;
	

	touchGestureTypes[TG_MULTI_DOWN] = &ofxPQLabs::onTG_MultiDown;
	touchGestureTypes[TG_MULTI_MOVE] = &ofxPQLabs::onTG_MultiMove;
	touchGestureTypes[TG_MULTI_UP] = &ofxPQLabs::onTG_MultiUp;
	
	

	touchGestureTypes[TG_MULTI_MOVE_RIGHT] = &ofxPQLabs::onTG_MultiMoveRight;
	touchGestureTypes[TG_MULTI_MOVE_UP] = &ofxPQLabs::onTG_MultiMoveUp;
	touchGestureTypes[TG_MULTI_MOVE_LEFT] = &ofxPQLabs::onTG_MultiMoveLeft;
	touchGestureTypes[TG_MULTI_MOVE_DOWN] = &ofxPQLabs::onTG_MultiMoveDown;
	

	
	touchGestureTypes[TG_TOUCH_END] = &ofxPQLabs::onTG_TouchEnd;
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

void ofxPQLabs:: onTG_TouchStart(const TouchGesture & tg, void * call_object)
{
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs:: onTG_TouchStart");
	TouchEventData event(tg);
	ofxPQLabs* labsInstance = static_cast<ofxPQLabs*>(call_object);
	ofNotifyEvent(labsInstance->touchEventDataEventDispatcher, event);
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


void ofxPQLabs:: onTG_Down(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Single Touch start " 
		<< " Finger 1 X :" << tg.params[0]
		<< " Finger 1 Y :" << tg.params[1]
	<< endl;
	
	
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_Down " +ss.str());
}

void ofxPQLabs:: onTG_Move(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Single Touch move " 
		<< " Finger 1 X :" << tg.params[0]
		<< " Finger 1 Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_Move " +ss.str());
}

void ofxPQLabs:: onTG_Up(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Single Touch Up " 
		<< " Finger 1 X :" << tg.params[0]
		<< " Finger 1 Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_Up " +ss.str());
}

#pragma mark Gesture Callbacks: Directional Moves 
void ofxPQLabs:: onTG_MoveRight(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Move Right " 
	<< " Finger 1 X :" << tg.params[0]
	<< " Finger 1 Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_MoveRight " +ss.str());
}

void ofxPQLabs:: onTG_MoveUp(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Move Up " 
	<< " Finger 1 X :" << tg.params[0]
	<< " Finger 1 Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_MoveUp " +ss.str());
}

void ofxPQLabs:: onTG_MoveLeft(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Move Left " 
	<< " Finger 1 X :" << tg.params[0]
	<< " Finger 1 Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_MoveLeft " +ss.str());
}

void ofxPQLabs:: onTG_MoveDown(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Move Down " 
	<< " Finger 1 X :" << tg.params[0]
	<< " Finger 1 Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_MoveDown " +ss.str());
}

#pragma mark Gesture Callbacks: Second Down 
void ofxPQLabs:: onTG_SecondDown(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	
	ss << "  Second Finger Down " 
		<< " New Finger X :" << tg.params[0]
		<< " New Finger Y :" << tg.params[1]
		<< " Original Finger X :" << tg.params[2]
		<< " Original Finger Y :" << tg.params[3]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_SecondDown " +ss.str());
}

void ofxPQLabs:: onTG_SecondUp(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Second Finger Up " 
		<< " Second Finger X :" << tg.params[0]
		<< " Second Finger Y :" << tg.params[1]
		<< " Original Finger X :" << tg.params[2]
		<< " Original Finger Y :" << tg.params[3]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_SecondUp " +ss.str());
}


#pragma mark Gesture Callbacks: Split
void ofxPQLabs:: onTG_SplitStart(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Zoom start " 
		<< " Finger 1 X :" << tg.params[0]
		<< " Finger 1 Y :" << tg.params[1]
		<< " Finger 2 X :" << tg.params[2]
		<< " Finger 2 Y :" << tg.params[3]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_SplitStart " +ss.str());
}


void ofxPQLabs:: onTG_SplitApart(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Zoom Happening distance increase by " 
		<< "Delta in pixels: "<< tg.params[0]
		<< " Difference Ratio :" << tg.params[1]
		<< " Finger 1 X :" << tg.params[2]
		<< " Finger 1 Y :" << tg.params[3]
		<< " Finger 2 X :" << tg.params[4]
		<< " Finger 2 Y :" << tg.params[5]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_SplitApart " +ss.str());
}

void ofxPQLabs:: onTG_SplitClose(const TouchGesture & tg, void * call_object)
{
	//	params[0] indicate the delta distance in pixels. params[1] indicate the delta ratio to the last distance of the two fingers.(params[2],params[3]) and (params[4],params[5]) is the positions of the two points.

	stringstream ss;
	ss << "  Pinch Happening distance decreased by " 
		<< "Delta in pixels: "<< tg.params[0]
		<< " Difference Ratio :" << tg.params[1]
		<< " Finger 1 X :" << tg.params[2]
		<< " Finger 1 Y :" << tg.params[3]
		<< " Finger 2 X :" << tg.params[4]
		<< " Finger 2 Y :" << tg.params[5]
	<< endl;
	
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_SplitClose " +ss.str());
}

void ofxPQLabs:: onTG_SplitEnd(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Pinch End  " 
		<< " Finger 1 X :" << tg.params[0]
		<< " Finger 1 Y :" << tg.params[1]
		<< " Finger 2 X :" << tg.params[2]
		<< " Finger 2 Y :" << tg.params[3]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_SplitEnd " +ss.str());
}




#pragma mark Gesture Callbacks: Rotate
void ofxPQLabs:: onTG_RotateStart(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Rotate Start  " 
		<< " Anchor Finger X :" << tg.params[0]
		<< " Anchor Finger Y :" << tg.params[1]
		<< " Rotating Finger X :" << tg.params[2]
		<< " Rotating Finger Y :" << tg.params[3]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_RotateStart " +ss.str());
	//listener->onRotateStart(tg);
}

void ofxPQLabs:: onTG_RotateCounterClockwise(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Rotating CounterClockwise  "
		<< " Radians :" << tg.params[0]
		<< " Anchor Finger X :" << tg.params[1]
		<< " Anchor Finger Y :" << tg.params[2]
		<< " Rotating Finger X :" << tg.params[3]
		<< " Rotating Finger Y :" << tg.params[4]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_RotateCounterClockwise " +ss.str());
}

void ofxPQLabs:: onTG_RotateClockwise(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Rotating Clockwise  "
		<< " Radians :" << tg.params[0]
		<< " Anchor Finger X :" << tg.params[1]
		<< " Anchor Finger Y :" << tg.params[2]
		<< " Rotating Finger X :" << tg.params[3]
		<< " Rotating Finger Y :" << tg.params[4]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_RotateClockwise " +ss.str());
}

void ofxPQLabs:: onTG_RotateEnd(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Rotate End  " 
		<< " Anchor Finger X :" << tg.params[0]
		<< " Anchor Finger Y :" << tg.params[1]
		<< " Rotating Finger X :" << tg.params[2]
		<< " Rotating Finger Y :" << tg.params[3]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_RotateEnd " +ss.str());
}



#pragma mark Gesture Callbacks: Near Parallel 
void ofxPQLabs:: onTG_NearParallelDown(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Near Parallel " 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
		<< " Finger 1 X :" << tg.params[2]
		<< " Finger 1 Y :" << tg.params[3]
		<< " Finger 2 X :" << tg.params[4]
		<< " Finger 2 Y :" << tg.params[5]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_NearParallelDown " +ss.str());
}

void ofxPQLabs:: onTG_NearParallelMove(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Near Parallel Move" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
		<< " Finger 1 X :" << tg.params[2]
		<< " Finger 1 Y :" << tg.params[3]
		<< " Finger 2 X :" << tg.params[4]
		<< " Finger 2 Y :" << tg.params[5]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_NearParallelMove " +ss.str());
}

void ofxPQLabs:: onTG_NearParallelUp(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Near Parallel Up" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
		<< " Finger 1 X :" << tg.params[2]
		<< " Finger 1 Y :" << tg.params[3]
		<< " Finger 2 X :" << tg.params[4]
		<< " Finger 2 Y :" << tg.params[5]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_NearParallelUp " +ss.str());
}

void ofxPQLabs:: onTG_NearParallelClick(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Near Parallel Click" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_NearParallelClick " +ss.str());
}

void ofxPQLabs:: onTG_NearParallelDoubleClick(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Near Parallel Double Click" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_NearParallelDoubleClick " +ss.str());
}

#pragma mark Gesture Callbacks: Near Parallel Directional Move 
void ofxPQLabs:: onTG_NearParallelMoveRight(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Near Parallel Move Right" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_NearParallelMoveRight " +ss.str());
}

void ofxPQLabs:: onTG_NearParallelMoveUp(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Near Parallel Move Up" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_NearParallelMoveUp " +ss.str());
}

void ofxPQLabs:: onTG_NearParallelMoveLeft(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << " Near Parallel Move Left" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_NearParallelMoveLeft " +ss.str());
}

void ofxPQLabs:: onTG_NearParallelMoveDown(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Near Parallel Move Down" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_NearParallelMoveDown " +ss.str());
}

#pragma mark Gesture Callbacks: Multi 

void ofxPQLabs:: onTG_MultiDown(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Multi Down (+3 fingers)" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_MultiDown " +ss.str());
}

void ofxPQLabs:: onTG_MultiMove(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Multi Move (+3 fingers)" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_MultiMove " +ss.str());
}

void ofxPQLabs:: onTG_MultiUp(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Multi Up (+3 fingers)" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_MultiUp " +ss.str());
}

#pragma mark Gesture Callbacks: Multi Directional Move 
void ofxPQLabs:: onTG_MultiMoveRight(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Multi Move Right (+3 fingers)" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_MultiMoveRight " +ss.str());
}

void ofxPQLabs:: onTG_MultiMoveUp(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Multi Move Up (+3 fingers)" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_MultiMoveUp " +ss.str());
}

void ofxPQLabs:: onTG_MultiMoveLeft(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Multi Move Left (+3 fingers)" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_MultiMoveLeft " +ss.str());
}

void ofxPQLabs:: onTG_MultiMoveDown(const TouchGesture & tg, void * call_object)
{
	stringstream ss;
	ss << "  Multi Move Down (+3 fingers)" 
		<< " Middle Position X: "<< tg.params[0]
		<< " Middle Position Y :" << tg.params[1]
	<< endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_MultiMoveDown " +ss.str());
}

#pragma mark Gesture Callbacks: END
// onTG_TouchEnd: to clear what need to clear
void ofxPQLabs:: onTG_TouchEnd(const TouchGesture & tg,void * call_object)
{
	stringstream ss;
	ss << "  all the fingers is leaving and there is no fingers on the screen." << endl;
	ofLog(OF_LOG_VERBOSE,  "ofxPQLabs::onTG_TouchEnd " +ss.str());
}