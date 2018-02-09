#ifndef __MAINMENURECEIVER_HEADER__
#define __MAINMENURECEIVER_HEADER__

#include <irrlicht.h>
#include "LeapMotion.h"
#include "IStateController.h"
#include "MainMenuController.h"
#include "GameController.h"
#include "GameReceiver.h"
#include "GameView.h"
#include "GameLeap.h"
#include "StateMachine.h"

using irr::s32;
using irr::EET_GUI_EVENT;
using irr::IrrlichtDevice;
using irr::gui::IGUIEnvironment;
using irr::IEventReceiver;
using irr::SEvent;

class MainMenuReceiver : public IEventReceiver
{
private:
	IStateController* thisController;
	IrrlichtDevice* dv;
	IGUIEnvironment* gu;
		// flag che comunica se un elemento della gui è sotto il cursore.
	int buttonHovered = 1;
public:
	MainMenuReceiver();
	MainMenuReceiver(IrrlichtDevice* device, IGUIEnvironment* gui) : dv(device), gu(gui) { }
	~MainMenuReceiver();

	int isButtonHovered();
	void setController(IStateController* c);
	virtual bool OnEvent(const SEvent& event);
private:
};

#endif