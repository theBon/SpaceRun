#include "LeapMotion.h"

Controller* LeapMotion::controller;

void LeapMotion::init(){
	controller = new Controller();
	controller->enableGesture(Leap::Gesture::TYPE_SCREEN_TAP);
	controller->config().setFloat("Gesture.ScreenTap.MinForwardVelocity", 0);
	controller->config().setFloat("Gesture.ScreenTap.MinDistance", 1);
}

Controller* LeapMotion::getController(){
	return controller;
}
