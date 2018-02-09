#include <iostream>
#include "WindowResolution.h"
#include <Leap.h>
#include <irrlicht.h>
#include <irrKlang.h>
#include "LeapMotion.h"
#include "StateMachine.h"
#include "MainMenuLeap.h"
#include "IStateController.h"
#include "MainMenuController.h"
#include "MainMenuReceiver.h"
#include "MainMenuView.h"

using namespace irr;

int main() {
		// Inizializzo le impostazioni del Leap Motion
	LeapMotion::init();
		// Inizializzo il motore grafico irrlicht e l'audio manager irrklang.
		//---
		//---
	IrrlichtDevice *device = 
					createDevice(video::EDT_BURNINGSVIDEO, core::dimension2d<u32>(wres::getWidth(), wres::getHeight()), 1, true);
	if (device == 0)
		return 1;
	video::IVideoDriver* driver = device->getVideoDriver();
	gui::IGUIEnvironment* gui = device->getGUIEnvironment();
	scene::ISceneManager* smgr = device->getSceneManager();
	irrklang::ISoundEngine* snd = irrklang::createIrrKlangDevice();
		//---
		// Modifico il font.
	irr::gui::IGUISkin* skin = gui->getSkin();
	skin->setFont(gui->getFont("bigfont.png"));
	skin->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255,255,255,255));
		//---
		// Inizializza la state machine e le passa come primo stato quello relativo al main menu.
		//---
	StateMachine<IStateController>::init();
	MainMenuLeap* leap = new MainMenuLeap(device);
	MainMenuReceiver* rcv = new MainMenuReceiver(device, gui);
	MainMenuController* mmc = new MainMenuController(rcv, new MainMenuView(gui, smgr, snd), leap);
	leap->setController(mmc);
	rcv->setController(mmc);
		//---
	StateMachine<IStateController>::push(mmc);
		//---
		// GAME LOOP:
	int lastFPS = -1;
	while (device->run()) {
		if (device->isWindowActive())
		{
			// Notifico lo stato del Leap Motion
			if (!LeapMotion::getController()->isConnected())
				GameSettings::leapState = false;
			else
				GameSettings::leapState = true;
			// Metto in funzione il listener del Leap Motion dello state attivo StateMachine<IStateController>::top().
			(LeapMotion::getController())->addListener(*(StateMachine<IStateController>::top())->getLeapListener());
			// Metto in funzione l'event receiver dello state attivo StateMachine<IStateController>::top().
			device->setEventReceiver((StateMachine<IStateController>::top())->getReceiver());
			// Rendo invisibili tutte le root elements e nodes di tutte le viste.
			auto rootElements = gui->getRootGUIElement()->getChildren();
			for (core::list<IGUIElement*>::Iterator it = rootElements.begin(); it != rootElements.end(); ++it) {
				(*it)->setVisible(false);
			}
			auto rootNodes = smgr->getRootSceneNode()->getChildren();
			for (core::list<ISceneNode*>::Iterator it = rootNodes.begin(); it != rootNodes.end(); ++it) {
				(*it)->setVisible(false);
			}
			// Rendo visibile solo la vista in cima allo stack StateMachine<IStateController>::top())->getView().
			(StateMachine<IStateController>::top())->getView()->setVisible(true);
			auto currentState = StateMachine<IStateController>::top();
			// Aggiorno gli elementi dello state.
			(StateMachine<IStateController>::top())->update();

			// Renderizzo tutto ciò che ho disehnato nella view.
			driver->beginScene(true, true, video::SColor(255, 200, 200, 200));
			smgr->drawAll();
			gui->drawAll();
			driver->endScene();
			//---
			int fps = driver->getFPS();
			if (lastFPS != fps)
				lastFPS = fps;
		}
		else
			device->yield();
	}
		// Alla chiusura del software rimuovo il listener dal Leap Motion e l'irrlicht device.
	(LeapMotion::getController())->removeListener(*(StateMachine<IStateController>::top())->getLeapListener());
	device->drop();
	return 0;
}

/*
Ho testato con le funzioni di debug il rendering delle singole view e sembra funzionare tutto.
Cose da fare:
	1) PROVARE SU MONITOR A DIVERSE RISOLUZIONI!!!!!
		(SOPRATTUTTO LA PARTE SU MainMenuLeap.h IN CUI SI DEFINISCONO GLI ATTRIBUTI E SI MAPPA IL LEAP)
*/