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
#include "ofxPQLabsListener.h"






class ofxPQLabs{
public:
	ofxPQLabs();
	~ofxPQLabs();
	// Init: the entry of sample codes;
	//		demonstrate: ConnectServer, SendRequest etc;
	void connect(const char * ipAddress);
	void setListener(ofxPQLabsListener* _listener);
	ofxPQLabsListener* listener;
	
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
	typedef void (*PFuncOnTouchGesture)(const TouchGesture & tg, void * call_object);
	static void onTG_Default(const TouchGesture & tg,void * call_object); // just show the gesture

	static void onTG_TouchStart(const TouchGesture & tg,void * call_object);
	static void onTG_Down(const TouchGesture & tg,void * call_object);
	static void onTG_Move(const TouchGesture & tg,void * call_object);
	static void onTG_Up(const TouchGesture & tg,void * call_object);

	//
	static void onTG_MoveRight(const TouchGesture & tg,void * call_object);
	static void onTG_MoveUp(const TouchGesture & tg,void * call_object);
	static void onTG_MoveLeft(const TouchGesture & tg,void * call_object);
	static void onTG_MoveDown(const TouchGesture & tg,void * call_object);
	
	
	static void onTG_SecondDown(const TouchGesture & tg,void * call_object);
	static void onTG_SecondUp(const TouchGesture & tg,void * call_object);

	//
	static void onTG_SplitStart(const TouchGesture & tg,void * call_object);
	static void onTG_SplitApart(const TouchGesture & tg,void * call_object);
	static void onTG_SplitClose(const TouchGesture & tg,void * call_object);
	static void onTG_SplitEnd(const TouchGesture & tg,void * call_object);
	
	//
	static void onTG_RotateStart(const TouchGesture & tg,void * call_object);
	static void onTG_RotateCounterClockwise(const TouchGesture & tg,void * call_object);
	static void onTG_RotateClockwise(const TouchGesture & tg,void * call_object);
	static void onTG_RotateEnd(const TouchGesture & tg,void * call_object);

	static void onTG_NearParallelDown(const TouchGesture & tg,void * call_object);
	static void onTG_NearParallelMove(const TouchGesture & tg,void * call_object);
	static void onTG_NearParallelUp(const TouchGesture & tg,void * call_object);
	static void onTG_NearParallelClick(const TouchGesture & tg,void * call_object);
	static void onTG_NearParallelDoubleClick(const TouchGesture & tg,void * call_object);
	

	static void onTG_NearParallelMoveRight(const TouchGesture & tg,void * call_object);
	static void onTG_NearParallelMoveUp(const TouchGesture & tg,void * call_object);
	static void onTG_NearParallelMoveLeft(const TouchGesture & tg,void * call_object);
	static void onTG_NearParallelMoveDown(const TouchGesture & tg,void * call_object);
	
	static void onTG_MultiDown(const TouchGesture & tg,void * call_object);
	static void onTG_MultiMove(const TouchGesture & tg,void * call_object);
	static void onTG_MultiUp(const TouchGesture & tg,void * call_object);

	static void onTG_MultiMoveRight(const TouchGesture & tg,void * call_object);
	static void onTG_MultiMoveUp(const TouchGesture & tg,void * call_object);
	static void onTG_MultiMoveLeft(const TouchGesture & tg,void * call_object);
	static void onTG_MultiMoveDown(const TouchGesture & tg,void * call_object);
	
	// onTG_TouchEnd: to clear what need to clear;
	static void onTG_TouchEnd(const TouchGesture & tg,void * call_object);
	
	
	//
	
private:
	PFuncOnTouchGesture touchGestureTypes[TG_TOUCH_END + 1];

// sample code end
////////////////////////////////////assistant functions /////////////////////////////////

////////////////////////////////////assistant functions /////////////////////////////////
};
#endif // end of header

