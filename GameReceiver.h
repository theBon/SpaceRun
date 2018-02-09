#ifndef __GAMERECEIVER_HEADER__
#define __GAMERECEIVER_HEADER__

#include <irrlicht.h>
#include "IStateController.h"
#include "MainMenuLeap.h"
#include "GameLeap.h"
#include "GameController.h"
#include "StateMachine.h"
#include "GameSettings.h"

using irr::s32;
using irr::EET_GUI_EVENT;
using irr::IEventReceiver;
using irr::SEvent;
using irr::IrrlichtDevice;
using irr::gui::IGUIButton;

class GameReceiver : public IEventReceiver
{
	IrrlichtDevice* dv;
	IGUIEnvironment* gu;
	IStateController* thisController;
		// flag che comunica se un elemento della gui è sotto il cursore.
	int buttonHovered;
public:
	GameReceiver();
	GameReceiver(IrrlichtDevice* device, IGUIEnvironment* gui) : dv(device), gu(gui) {
		buttonHovered = 1;
	}
	~GameReceiver();

	virtual bool OnEvent(const SEvent& event);
	void setController(IStateController* c);
};

#endif
