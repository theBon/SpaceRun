#include "MainMenuReceiver.h"
#include "MainMenuView.h"

MainMenuReceiver::MainMenuReceiver(){
}

MainMenuReceiver::~MainMenuReceiver(){
}

int MainMenuReceiver::isButtonHovered(){
	return buttonHovered;
}

void MainMenuReceiver::setController(IStateController * c){
	thisController = c;
}

bool MainMenuReceiver::OnEvent(const SEvent& event) {
	if (thisController) {
		if (event.EventType == EET_GUI_EVENT)
		{
			// Id dell'elemento che scatena l'evento.
			s32 id = event.GUIEvent.Caller->getID();
			//---
			// Se viene premuto un bottone:
			if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
				// Controlla l'id dell'elemento (bottone, in questo caso) e agisce di conseguenza.
				//ESCI
				switch (id) {
				case 103: {
					dv->closeDevice();
					return true;
					break;
				}
				//GIOCA
				case 102: {
					if (static_cast<MainMenuController*>(thisController)) {
							// Mette in pausa la musica del main menu.
						auto bgm = ((MainMenuView*)(thisController->getView()))->getBgm();
						if (bgm) 
							bgm->setIsPaused(true);
					}
						// Rimuove il listener del Main Menu dal Leap Controller per poter poi utilizzare quello del gioco.
					(LeapMotion::getController())->removeListener
													(*(StateMachine<IStateController>::top())->getLeapListener());
						// Crea un nuovo GameController con tutte le sue componenti per poterlo aggiungere alla state machine.
					GameReceiver* rcv = new GameReceiver(dv, gu);
					GameLeap* leap = new GameLeap(dv);
					GameController* gc = new GameController(rcv,
															new GameView(gu, dv->getSceneManager(),
																			thisController->getView()->getSoundEngine()),
															leap);
						// Aggiunge il nuovo Game Controller alla state machine.
					StateMachine<IStateController>::push(gc);
					rcv->setController(gc);
					leap->setController(gc);
					return true;
					break;
				}
				}
			}
			// Se si è entrati col cursore in un elemento.
			else if (event.GUIEvent.EventType == irr::gui::EGET_ELEMENT_HOVERED) {
				// Se è un bottone
				if (dynamic_cast<irr::gui::IGUIButton*>(event.GUIEvent.Caller)) {
					// Setta il flag ad un valore positivo.
					buttonHovered = 2;
					// Se il controller attivo è un'istanza di MainMenuController.
					if (static_cast<MainMenuController*>(thisController))
						// Passa il valore 2 al controller..
						((MainMenuController*)thisController)->takeData(buttonHovered);
				}
			}
			// Se si è usciti col cursore da un elemento.
			else if (event.GUIEvent.EventType == irr::gui::EGET_ELEMENT_LEFT) {
				// Se è un bottone
				if (dynamic_cast<irr::gui::IGUIButton*>(event.GUIEvent.Caller)) {
					// Setta il flag ad un valore negativo.
					buttonHovered = 1;
					// Se il controller attivo è un'istanza di MainMenuController.
					if (static_cast<MainMenuController*>(thisController))
						// Passa il valore 1 al controller..
						((MainMenuController*)thisController)->takeData(buttonHovered);
				}
			}
		}
	}
	return false;
} // onEvent