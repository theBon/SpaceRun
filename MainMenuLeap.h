#ifndef __MAINMENULEAP_HEADER__
#define __MAINMENULEAP_HEADER__

#include <Leap.h>
#include <irrlicht.h>
#include "LeapMotion.h"
#include "WindowResolution.h"
#include "IStateController.h"
#include "MainMenuController.h"
#include "MainMenuReceiver.h"

using Leap::Listener;
using irr::IrrlichtDevice;
using irr::gui::ICursorControl;
using irr::gui::IGUIElement;
using irr::SEvent;

class MainMenuLeap : public Listener
{
private:
	IStateController* thisController;
	irr::gui::IGUIEnvironment* thisContViewGuiEnv;
	IrrlichtDevice* device;
		// Puntatore al cursore dell'applicazione.
	ICursorControl* cursor;
public:
	MainMenuLeap();
	MainMenuLeap(IrrlichtDevice* dev);
	~MainMenuLeap();

	ICursorControl* getCursor();
	void setController(IStateController* c);
	virtual void onFrame(const Leap::Controller& controller);
	virtual void onDeviceFailure(const Leap::Controller& controller);
private:
	void recognizeButtonClick();
};

#endif