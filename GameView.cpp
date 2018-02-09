#include "GameView.h"

GameView::GameView(){
}

GameView::~GameView(){
}

ShipNode * GameView::getShip(){
	return shipnode;
}

IMeshSceneNode * GameView::getShipNode(){
	return shipnode->getNode();
}

GameRoad * GameView::getRoad(){
	return road;
}

ICameraSceneNode * GameView::getCamera(){
	return camera;
}

ISceneNode * GameView::getSkybox(){
	return skybox;
}

ISound * GameView::getBgm(){
	return bgm;
}

vector<IGUIButton*> GameView::getButtons(){
	return buttons;
}

IGUIImage * GameView::getGameoverImg(){
	return gameover;
}

IGUIStaticText * GameView::getScore(){
	return score;
}

ITexture * GameView::getAlertTexture(int i){
	return alerttxt[i];
}

IGUIImage * GameView::getAlertImage(){
	return alertimage;
}

void GameView::setupScene() {
	auto driver = gui->getVideoDriver();
	bgm = soundengine->play2D("bgm001.ogg", true, true);
	bgm->setIsPaused(false);

	GameSettings::gamePaused = false;
	GameSettings::gameReady = true;
	GameSettings::gameOver = false;
	GameSettings::gameSpeed = 3;
	GameSettings::score = 0;

	long w = wres::getWidth();
	long h = wres::getHeight();

	gameover = gui->addImage(irr::core::recti(w / 2 - w / 5, h / 3, w, h), rootElement, rootElement->getID() + 5);
	gameover->setImage(driver->getTexture("gameover.png"));
	gameover->setVisible(false);

	alerttxt[0] = driver->getTexture("alert0.png");
	alerttxt[1] = driver->getTexture("alert1.png");
	alertimage = gui->addImage(irr::core::rect<irr::s32>(w - 100, 0, w, 100), rootElement, rootElement->getID() + 4);
	alertimage->setScaleImage(true);

	irr::core::stringw str = L"Score: ";
	str += GameSettings::score;
	score = gui->addStaticText(str.c_str(), irr::core::recti(0, 0, w / 2, h / 5), false, false, 
									rootElement, rootElement->getID() + 8);

	auto popButton =
		gui->addButton(irr::core::rect<irr::s32>(w/2 - buttonWidth/2, h/100 + h/2, 
												w/2 + buttonWidth/2, h/100 + buttonHeight + h/2),
					rootElement,						// elemento padre
					rootElement->getID() + 7,		    // id
					L"Riprova"
		);
	auto restartButton = 
		gui->addButton(irr::core::rect<irr::s32>(w/2 - buttonWidth/2, h/50 + buttonHeight + h/2,
												w/2 + buttonWidth/2, h/50 + 2*buttonHeight + h/2),
					rootElement,						// elemento padre
					rootElement->getID() + 6,		    // id
					L"Menu"
		);
	auto exitButton =
		gui->addButton(irr::core::rect<irr::s32>(w/2 - buttonWidth/2, 3*h/100 + 2*buttonHeight + h/2,
												w/2 + buttonWidth/2, 3*h/100 + 3*buttonHeight + h/2),
			rootElement,						// elemento padre
			rootElement->getID() + 4,		    // id
			L"Esci"
		);
	buttons.push_back(popButton);
	buttons.push_back(restartButton);
	buttons.push_back(exitButton);
	for (IGUIButton* b : buttons) {
		b->setVisible(false);
		b->setEnabled(false);
	}
		// Creo l'astronave.
	shipnode = new ShipNode(scenemanager, "Spaceship.3ds", rootNode, 3, core::vector3df(0, 0, -50), core::vector3df(0, 10, 0));
		// Creo una camera figlia del rootnode della view.
	camera = scenemanager->addCameraSceneNode(rootNode);
	camera->setPosition(core::vector3df(0, 0, 0));
	camera->setID(rootNode->getID() + 1);
		// La camera è rivolta verso il centro della spaceship.
	camera->setTarget(shipnode->getNode()->getTransformedBoundingBox().getCenter());

		// Aggiungo una fonte di luce che coincide con la posizione iniziale della mycamera
	scenemanager->addLightSceneNode(rootNode, 
									camera->getPosition(),
									video::SColorf(1, 1, 0, 0.4), 
									105,
									rootNode->getID() + 2

	);

	auto sky = scenemanager->addBillboardSceneNode(rootNode, irr::core::dimension2df(2700,1650), vector3df(-100,0,-1000));
	sky->setMaterialTexture(0, driver->getTexture("space.jpg"));
	sky->setMaterialFlag(video::EMF_LIGHTING, false);
	/*
	skybox = scenemanager->addSkyBoxSceneNode(driver->getTexture("space.jpg"),
		driver->getTexture("space.jpg"),
		driver->getTexture("space.jpg"),
		driver->getTexture("space.jpg"),
		driver->getTexture("space.jpg"),
		driver->getTexture("space.jpg")
	);
	skybox->setParent(rootNode);
	skybox->setID(rootNode->getID() + 4);
	skybox->getMaterial(0).TextureLayer[0].BilinearFilter = false;
	skybox->setRotation(vector3df(0,100,0));
	skybox->setScale(vector3df(1, 1, 1));*/
		// costruisce la road.
	setupRoad();
}

void GameView::setupRoad(){
	auto driver = gui->getVideoDriver();

	GameObstacle_Vertical* o1   = new GameObstacle_Vertical("box.obj", rootNode, vector3df(20, 0, -100), vector3df(0,0,0));
	GameObstacle_Vertical* o2   = new GameObstacle_Vertical("box.obj", rootNode, vector3df(-30, 0, -100), vector3df(0,0,0));
	GameObstacle_Horizontal* o3 = new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, 15, -90), vector3df(0, 0, 0));
	GameObstacle_Horizontal* o4 = new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, -15, -90), vector3df(0, 0, 0));
	GameObstacle_Vertical* o5   = new GameObstacle_Vertical("box.obj", rootNode, vector3df(20, 0, -100), vector3df(0, 0, 0));
	GameObstacle_Vertical* o6   = new GameObstacle_Vertical("box.obj", rootNode, vector3df(-30, 0, -100), vector3df(0, 0, 0));
	GameObstacle_Horizontal* o7 = new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, 15, -90), vector3df(0, 0, 0));
	GameObstacle_Horizontal* o8 = new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, -15, -90), vector3df(0, 0, 0));

	GameTile* t1 = new GameTile();
	GameTile* t2 = new GameTile();
	GameTile* t3 = new GameTile();
	GameTile* t4 = new GameTile();
	GameTile* t0 = new GameTile();

	t1->addObstacle(o1); t2->addObstacle(o3); 
	t1->addObstacle(o2); t2->addObstacle(o4);
	t3->addObstacle(o5); t3->addObstacle(o6);
	t4->addObstacle(o7); t4->addObstacle(o8);

	deque<GameTile*> q; q.push_back(t0); q.push_back(t1); q.push_back(t2); q.push_back(t3); q.push_back(t4);
	road = new GameRoad(q);

		// Aggiungo alla scena tutti gli ostacoli che ho inserito nella strada.
	int ti = -1;
	for (auto tile : road->getTileList()) {
		ti++;
		for (auto obs : tile->getObstacles()) {
			obs->addToScene(scenemanager, tile, ti);
			obs->setScale();
			obs->setTexture(driver);
			obs->setMaterialProperty();
		}
	}
}