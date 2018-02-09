#ifndef __LEAPMOTION_HEADER__
#define __LEAPMOTION_HEADER__

#include <Leap.h>
#include "GameSettings.h"

using Leap::Controller;

class LeapMotion
{
	static Controller* controller;
public:
	static void init();
	static Controller* getController();
};

#endif
