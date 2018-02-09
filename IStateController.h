#ifndef __ISTATECONTROLLER_HEADER__
#define __ISTATECONTROLLER_HEADER__

#include <Leap.h>
#include <irrlicht.h>
#include "View.h"
#include "StateMachine.h"

class IStateController
{
protected:
	Leap::Listener* leapListener;		// Listener che controlla il sensore del Leap Motion.
	irr::IEventReceiver* eReceiver;		// Listener che controlla gli input dell'utente.
	
	View* view;							// Vista associata al controller.
public:
	IStateController();
	/* er: IEventReceiver che risponderà agli input dell'utente.
	   v: vista associata al controller.
	*/
	IStateController(irr::IEventReceiver* er, View* v);
	IStateController(irr::IEventReceiver* er, View* v, Leap::Listener* ll);
	~IStateController();

	Leap::Listener* getLeapListener();
	View* getView();
	irr::IEventReceiver* getReceiver();

	virtual void update();
};

#endif

