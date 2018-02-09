#include "GameLeap.h"

GameLeap::GameLeap(){
}

GameLeap::GameLeap(IrrlichtDevice * dev){
	device = dev;
	cursor = device->getCursorControl();
}

GameLeap::~GameLeap(){
}

void GameLeap::onFrame(const Leap::Controller & controller){
		// Ricroda che se il leap motion non è collegato, questo metodo non viene eseguito.
		// Se si è in gioco si traccia la posizione del palmo della mano.
	if (!GameSettings::gameOver){
		auto hands = controller.frame().hands();
		Leap::InteractionBox iBox = controller.frame().interactionBox();
		Leap::Vector leapPoint = hands.frontmost().stabilizedPalmPosition();

		Leap::Vector normalizedPoint = iBox.normalizePoint(leapPoint, false);
		int x_app = normalizedPoint.x * wres::getWidth();
		int y_app = (1 - normalizedPoint.y) * wres::getHeight();
			// Prima di muovere il cursore controlla se il Leap Motion ha trovato la mano.
		if (hands.count() > 0 &&
			hands.frontmost().palmVelocity().x < 0.1 && hands.frontmost().palmVelocity().x > 0.1 &&
			hands.frontmost().palmVelocity().y < 0.1 && hands.frontmost().palmVelocity().y > 0.1) {
			cursor->setPosition(x_app, y_app);
		}
	}
		// Se non si è in gioco si traccia la posizione del dito.
	else {
		Leap::InteractionBox iBox = controller.frame().interactionBox();
		Leap::Pointable pointable = controller.frame().pointables().frontmost();
		Leap::Vector leapPoint = pointable.stabilizedTipPosition();

		Leap::Vector normalizedPoint = iBox.normalizePoint(leapPoint, false);
		int x_app = normalizedPoint.x * wres::getWidth();
		int y_app = (1 - normalizedPoint.y) * wres::getHeight();
			// Prima di muovere il cursore controlla se il Leap Motion ha trovato delle dita.
		if (controller.frame().fingers().count() > 0)
			cursor->setPosition(x_app, y_app);
	}
		// Controlla che sia stato chiamato il setController dopo la costruzione dell'oggetto di classe.
	if (thisController)
		recognizeButtonClick();
}

void GameLeap::recognizeButtonClick(){
	// Se il controller attivo è un'istanza di MainMenuController.
	if (static_cast<GameController*>(thisController)) {
		// Se il messaggio (arrivato dal receiver) del controller è 2, ovvero ci si trova sopra ad un gui element
		if (((GameController*)thisController)->getMessage() == 2) {
			Leap::GestureList glist = (LeapMotion::getController())->frame().gestures();
			// Elemento su cui si trova il cursore.
			if (thisContViewGuiEnv) {
				IGUIElement* hoveredElem = thisContViewGuiEnv->getHovered();
				// Ciclo nell'array di gestures create dall'sdk e cerco se il leap controller ha intercettato uno screen tap:
				for (int g = 0; g < glist.count(); g++) {
					Leap::Gesture gesture = glist[g];
					// Se trovo uno screen tap:
					if (gesture.type() == Leap::Gesture::TYPE_SCREEN_TAP) {
						// Creo un evento a mano, di tipo button click e dico che è stato azionato dall'elemento su cui mi trovo.
						SEvent* ev = new SEvent();
						ev->EventType = irr::EEVENT_TYPE::EET_GUI_EVENT;
						ev->GUIEvent.EventType = irr::gui::EGET_BUTTON_CLICKED;
						ev->GUIEvent.Caller = hoveredElem;
						/* Richiamo il metodo che gestisce gli eventi (chiamata ricorsiva) passando come evento quello appena
						creato. In questo modo entrerò nel ramo che gestisce il button click e avrò simulato il click del
						mouse con il leap controller. */
						((GameReceiver*)(device->getEventReceiver()))->OnEvent(*ev);
					}
				}
			}

		}
		// Se il messaggio (arrivato dal receiver) del controller è 1
		else if (((GameController*)thisController)->getMessage() == 1) {

		}
	}
}

void GameLeap::setController(IStateController * c){
	thisController = c;
	thisContViewGuiEnv = thisController->getView()->getGUIEnvironment();
}

ICursorControl * GameLeap::getCursor(){
	return cursor;
}
