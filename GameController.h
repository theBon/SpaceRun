#ifndef __GAMECONTROLLER_HEADER__
#define __GAMECONTROLLER_HEADER__

#include "IStateController.h"
#include "GameView.h"
#include "GameLeap.h"
#include <irrlicht.h>
#include "GameSettings.h"
#include "RandomTileGenerator.h"
#include "WindowResolution.h"

class GameController : public IStateController
{
	// Parametro utilizzato per lo scambio di messaggi tra LeapListener e IEventReceiver.
	int message;
public:
	GameController();
	/* er: IEventReceiver che risponderà agli input dell'utente.
	v: vista associata al controller.
	*/
	GameController(irr::IEventReceiver* er, View* v) : IStateController(er, v) {}
	GameController(irr::IEventReceiver* er, View* v, Leap::Listener* ll) : IStateController(er, v, ll) {}

	~GameController();
	virtual void update();

	int getMessage();
	void takeData(int flag);

private:
	void updateSpeed();
	void updateRoad(GameView* view);
	void gameOver(GameView* view);
};

#endif