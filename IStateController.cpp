#include "IStateController.h"

IStateController::IStateController(){
}

IStateController::IStateController(irr::IEventReceiver * er, View * v){
	eReceiver = er;
	view = v;
	leapListener = nullptr;
}

IStateController::IStateController(irr::IEventReceiver * er, View * v, Leap::Listener * ll){
	eReceiver = er;
	view = v;
	leapListener = ll;
}

IStateController::~IStateController(){
}

Leap::Listener * IStateController::getLeapListener(){
	return leapListener;
}

View* IStateController::getView()
{
	return view;
}

irr::IEventReceiver * IStateController::getReceiver(){
	return eReceiver;
}

void IStateController::update(){
}
