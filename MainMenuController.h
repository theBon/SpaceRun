#ifndef __MAINMENUCONTROLLER_HEADER__
#define __MAINMENUCONTROLLER_HEADER__

#include "IStateController.h"
#include "MainMenuLeap.h"
#include "MainMenuView.h"

class MainMenuController : public IStateController
{
	// Parametro utilizzato per lo scambio di messaggi tra LeapListener e IEventReceiver.
	int message;
public:
	MainMenuController();
	/* er: IEventReceiver che risponderà agli input dell'utente.
	v: vista associata al controller.
	*/
	MainMenuController(irr::IEventReceiver* er, View* v) : IStateController(er, v) {}
	MainMenuController(irr::IEventReceiver* er, View* v, Leap::Listener* ll) : IStateController(er, v, ll) {}
	~MainMenuController();

	int getMessage();
	void takeData(int flag);

	virtual void update();
};

#endif