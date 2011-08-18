#ifndef OF_PQ_LABS_LISTENER_H
#define OF_PQ_LABS_LISTENER_H

#include "ofxPQLabs.h"

class ofxPQLabsListener {
public:
	
	virtual void onTG_Default(const TouchGesture & tg, void * call_object) = 0;
};

#endif