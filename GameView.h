#ifndef __GAMEMENUVIEW_HEADER__
#define __GAMEMENUVIEW_HEADER__

#include <vector>
#include "View.h"
#include <irrlicht.h>
#include <irrKlang.h>
#include "ShipNode.h"
#include "GameRoad.h"
#include "GameObstacle.h"
#include "GameObstacle_Vertical.h"
#include "GameObstacle_Horizontal.h"
#include "GameSettings.h"

using namespace irr;
using irr::gui::IGUIButton;
using irr::gui::IGUIImage;
using irr::gui::IGUIStaticText;
using irr::scene::ISceneNode;
using irr::scene::IMeshSceneNode;
using irr::scene::ICameraSceneNode;
using irr::scene::ISceneNodeAnimatorCollisionResponse;
using irrklang::ISound;

class GameView : public View
{
	const int buttonWidth = 300;
	const int buttonHeight = 100;
	vector<IGUIButton*> buttons;
	IGUIStaticText* score;
	IGUIImage* gameover;
	ISceneNode* skybox;
	ShipNode* shipnode;
	ICameraSceneNode* camera;
	GameRoad* road;
	ISound* bgm;
	ITexture* alerttxt[2];
	IGUIImage* alertimage;
protected:
	void setupScene();
	void setupRoad();
public:
	IMeshSceneNode* box;
	GameView();
	GameView(IGUIEnvironment* e, ISceneManager* s, ISoundEngine* se) : View(e, s, se) {
		setupScene();
	}
	~GameView();

	ShipNode* getShip();
	IMeshSceneNode* getShipNode();
	GameRoad* getRoad();
	ICameraSceneNode* getCamera();
	ISceneNode* getSkybox();
	ISound* getBgm();
	vector<IGUIButton*> getButtons();
	IGUIImage* getGameoverImg();
	IGUIStaticText* getScore();
	ITexture* getAlertTexture(int i);
	IGUIImage* getAlertImage();

};

#endif
