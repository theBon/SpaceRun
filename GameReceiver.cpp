#include "GameReceiver.h"
#include "GameView.h"
#include "MainMenuView.h"

GameReceiver::GameReceiver(){
}

GameReceiver::~GameReceiver(){
}

bool GameReceiver::OnEvent(const SEvent & event){
		// Se viene premuto 'spazio' il gioco va in pausa.
	if (event.EventType == EET_KEY_INPUT_EVENT) {
		if (event.KeyInput.Key == KEY_SPACE && event.KeyInput.PressedDown) {
			GameSettings::togglePause();
			return true;
		}
	}

	if (event.EventType == EET_GUI_EVENT)
	{
		// Id dell'elemento che scatena l'evento.
		s32 id = event.GUIEvent.Caller->getID();
		//---
		// Se viene premuto un bottone:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
			// Controlla l'id dell'elemento (bottone, in questo caso) e agisce di conseguenza.
			switch (id) {
				// ESCI
				case 104:
					dv->closeDevice();
					return true;
					break;
				// RITORNA AL MENU PRINCIPALE
				case 106: {
						// stoppo la musica ed elimino il suo puntatore.
					if (static_cast<GameController*>(thisController)) {
						auto bgm = ((GameView*)(thisController->getView()))->getBgm();
						if (bgm) {
							bgm->stop();
							bgm->drop();
						}
					}
						// Rimuove il listener del gioco dal Leap Controller per poter poi utilizzare quello del main menu.
					(LeapMotion::getController())->removeListener
													(*(StateMachine<IStateController>::top())->getLeapListener());
						// Rimuove il Game controller dalla state machine.
					StateMachine<IStateController>::pop();
						// Aggiunge al Leap Controller il listener del Main Menu
					MainMenuLeap* mml = new MainMenuLeap(dv);
					LeapMotion::getController()->addListener(*mml);
						// Ripristina la musica del main menu.
					((MainMenuView*)(StateMachine<IStateController>::top()->getView()))->restore();
					return true;
					break;
				}
				// RIPROVA
				case 107:
						// stoppo la musica ed elimino il suo puntatore.
					if (static_cast<GameController*>(thisController)) {
						auto bgm = ((GameView*)(thisController->getView()))->getBgm();
						if (bgm) {
							bgm->stop();
							bgm->drop();
						}
					}
						// Crea un nuovo GameController con tutte le sue componenti per poterlo aggiungere alla state machine.
					GameReceiver* rcv = new GameReceiver(dv, gu);
					GameLeap* leap = new GameLeap(dv);
					GameController* gc = new GameController(rcv,
															new GameView(gu, 
																		dv->getSceneManager(),
																		thisController->getView()->getSoundEngine()),
															leap);
						// Rimuove il listener del gioco dal Leap Controller per poter poi utilizzare quello nuovo.
					(LeapMotion::getController())->removeListener
													(*(StateMachine<IStateController>::top())->getLeapListener());
						// Rimuove il vecchio game controller dalla state machine.
					StateMachine<IStateController>::pop();
						// Aggiunge il nuovo game controller alla state machine.
					StateMachine<IStateController>::push(gc);
					rcv->setController(gc);
					leap->setController(gc);
					return true;
					break;
			}
		}
		// Se si è entrati col cursore in un elemento.
		else if (event.GUIEvent.EventType == irr::gui::EGET_ELEMENT_HOVERED) {
			// Se è un bottone
			if (dynamic_cast<irr::gui::IGUIButton*>(event.GUIEvent.Caller)) {
				if(event.GUIEvent.Caller->getID() != 105)
						// Setta il flag ad un valore positivo.
					buttonHovered = 2;
				// Se il controller attivo è un'istanza di GameController.
				if (static_cast<GameController*>(thisController))
					// Passa il valore 2 al controller..
					((GameController*)thisController)->takeData(buttonHovered);
			}
		}
		// Se si è usciti col cursore da un elemento.
		else if (event.GUIEvent.EventType == irr::gui::EGET_ELEMENT_LEFT) {
			// Se è un bottone
			if (dynamic_cast<irr::gui::IGUIButton*>(event.GUIEvent.Caller)) {
				if (event.GUIEvent.Caller->getID() != 105)
					// Setta il flag ad un valore negativo.
					buttonHovered = 1;
				// Se il controller attivo è un'istanza di GameController.
				if (static_cast<GameController*>(thisController))
					// Passa il valore 1 al controller..
					((GameController*)thisController)->takeData(buttonHovered);
			}
		}

	}
	return false;
}

void GameReceiver::setController(IStateController * c){
	thisController = c;
}
