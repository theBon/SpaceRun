#ifndef __SHIPNODE_HEADER__
#define __SHIPNODE_HEADER__

#include <sstream>
#include <irrlicht.h>
#include "WindowResolution.h"

using irr::core::array;
using irr::core::vector3df;
using irr::scene::IMeshSceneNode;
using irr::scene::ISceneManager;
using irr::scene::ISceneNode;
using irr::gui::ICursorControl;
using irr::scene::IBillboardSceneNode;
using irr::video::ITexture;
using irr::scene::ISceneNodeAnimator;

class ShipNode
{
	IMeshSceneNode* node;
	ISceneNode* parent;
	array<ITexture*> textures;
	ISceneNodeAnimator* expAnimator;
	IBillboardSceneNode* explosion;
	float xpos, ypos, zpos;
	int id;
	bool exploding;
	const int left_padding   = 7;
	const int right_padding  = 100;
	const int top_padding    = 4;
	const int bottom_padding = 4;
public:
	ShipNode();
		/*
		mng: lo sceneMnaager dell'applicazione.
		path: relative path del mesh della ship.
		prnt: nodo genitore.
		i: id della ship nella gerarchia dei nodi.
		pos: posizione iniziale.
		rot: angolazione iniziale.
		*/
	ShipNode(ISceneManager* mng, irr::io::path path, ISceneNode* prnt, int i, vector3df pos, vector3df rot);
	~ShipNode();
		// Restituisce il ISceneNode relativo alla ship.
	IMeshSceneNode* getNode();
	IBillboardSceneNode* getExplosion();
	ISceneNodeAnimator* getExpAnimator();
	bool isExploding();
	void setExploding(bool b);
		// Aggiorna la posizione della ship in funzione della posizione del cursore.
	void updatePosition(ICursorControl* c);
	void startExplodingAnimation(ISceneManager* mng);
private:
	void setupExplosionAnimation(ISceneManager* mng);
};

#endif