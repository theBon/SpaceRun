#include "View.h"
#include <iostream>
View::View(){
}

View::View(IGUIEnvironment* e, ISceneManager* s, ISoundEngine* se){
	gui = e;
	scenemanager = s;
	soundengine = se;
		/* Crea il root element della gui per la vista, e ne imposta le dimensioni pari a quelle della risoluzione dello schermo
			in modo da rendere visibile tutti gli elementi gui della scena */
	rootElement = gui->addTab(irr::core::rect<irr::s32>(0, 0, wres::getWidth(), wres::getHeight()), gui->getRootGUIElement(), 100);
	/*auto button = gui->addButton(irr::core::rect<irr::s32>(10, 240, 110, 240 + 32), rootElement, 101, L"Quit", L"Exits Program");*/
		/* Crea il root node per la vista, tutti i nodi della scena sono suoi figli. */
	rootNode = scenemanager->addEmptySceneNode(scenemanager->getRootSceneNode(), 100);
}

View::~View(){
}

IGUIElement * View::getRootElement(){
	return rootElement;
}

ISceneNode * View::getRootNode(){
	return rootNode;
}

IGUIEnvironment * View::getGUIEnvironment(){
	return gui;
}

ISceneManager * View::getSceneManager(){
	return scenemanager;
}

ISoundEngine * View::getSoundEngine(){
	return soundengine;
}

void View::setVisible(bool b){
	rootElement->setVisible(b);
	rootNode->setVisible(b);
}

void View::setupScene(){
}
