#ifndef __GAMELEAP_HEADER__
#define __GAMELEAP_HEADER__

#include <Leap.h>
#include <irrlicht.h>
#include "LeapMotion.h"
#include "WindowResolution.h"
#include "GameSettings.h"
#include "IStateController.h"
#include "GameController.h"
#include "GameReceiver.h"

using Leap::Listener;
using irr::IrrlichtDevice;
using irr::gui::ICursorControl;

class GameLeap : public Listener
{
	IStateController* thisController;
	irr::gui::IGUIEnvironment* thisContViewGuiEnv;
	IrrlichtDevice* device;
	ICursorControl* cursor;
public:
	GameLeap();
	GameLeap(IrrlichtDevice* dev);
	~GameLeap();

	void setController(IStateController* c);
	ICursorControl* getCursor();
	virtual void onFrame(const Leap::Controller& controller);
private:
	void recognizeButtonClick();

};
#endif
