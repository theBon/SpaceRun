#ifndef __VIEW_HEADER__
#define __VIEW_HEADER__

#include <irrlicht.h>
#include <irrKlang.h>
#include "WindowResolution.h"

using irr::gui::IGUIElement;
using irr::scene::ISceneNode;
using irr::gui::IGUIEnvironment;
using irr::scene::ISceneManager;
using irrklang::ISoundEngine;
using irrklang::ISound;

class View
{
protected:
	IGUIEnvironment* gui;
	ISceneManager* scenemanager;
	ISoundEngine* soundengine;
	IGUIElement* rootElement;	// Elemento radice di tutti gli elementi gui della view.
	ISceneNode* rootNode;		// Nodo radice di tutti gli altri nodi della view.
	virtual void setupScene();
public:
	View();
	View(IGUIEnvironment* e, ISceneManager* s, ISoundEngine* se);
	~View();

	/* Puntatore all'elemento gui radice di questa vista. */
	IGUIElement* getRootElement();
	/* Puntatore al nodo radice di questa vista. */
	ISceneNode* getRootNode();
	IGUIEnvironment* getGUIEnvironment();
	ISceneManager* getSceneManager();
	ISoundEngine* getSoundEngine();

	void setVisible(bool b);

};

#endif
