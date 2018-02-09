#include "GameController.h"

GameController::GameController(){
}

GameController::~GameController(){
}

int GameController::getMessage() {
	return message;
}

void GameController::takeData(int flag) {
	message = flag;
}

void GameController::update(){
	updateSpeed();
	auto cursor = ((GameLeap*)leapListener)->getCursor();
	if(!GameSettings::gameOver)
		cursor->setVisible(false);
	if (static_cast<GameView*>(view)) {
		auto v = ((GameView*)view);
		v->getAlertImage()->setImage(v->getAlertTexture(GameSettings::leapState));

		if (!GameSettings::gamePaused && !GameSettings::gameOver) {
			// Muovo la ship attarverso il cursore.
			auto ship = v->getShip();
			ship->updatePosition(cursor);

			if (GameSettings::gameReady) {
				auto shipbox = v->getShipNode()->getTransformedBoundingBox();
				// Ciclo su ogni tile nella road .
				auto road = v->getRoad();
				for (auto tile : road->getTileList()) {
					// Ciclo su ogni obstacle nel dato tile.
					for (auto o : tile->getObstacles()) {
						auto box = o->getNode()->getTransformedBoundingBox();
						// Faccio avanzare gli obstacles verso la spaceship se non collidono.
						if (!box.intersectsWithBox(shipbox)) {
							o->moveForward(GameSettings::gameSpeed);
							GameSettings::score += GameSettings::gameSpeed;
						}
						else {
							ship->setExploding(true);
						}
						if(box.getCenter().Z > shipbox.getCenter().Z)
							o->getNode()->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
						// Setto un flag a true se gli obstacles di un dato tile arrivano dietro la camera.
						if (box.getCenter().Z > -20)
							tile->setDeletable(true);
					}
					// Se il dato tile ha il flag su true viene rimosso dalla road con tutti i suoi obstacles e ne inserisco uno casuale.
					if (tile->getDeletable()) {
						updateRoad(v);
					}
				}
			}
			irr::core::stringw str = L"Score: ";
			str += GameSettings::score;
			v->getScore()->setText(str.c_str());

			if (ship->isExploding()) {
				gameOver(v);
			}
		}
	}
}

void GameController::updateSpeed(){
	if (GameSettings::score > 200000) {
		GameSettings::gameSpeed = 7;
	}
	else if (GameSettings::score > 100000) {
		GameSettings::gameSpeed = 6;
	}
	else if (GameSettings::score > 40000) {
		GameSettings::gameSpeed = 5;
	}
	else if (GameSettings::score > 15000) {
		GameSettings::gameSpeed = 4;
	}
}

void GameController::updateRoad(GameView* view) {
	auto driver = view->getSceneManager()->getVideoDriver();

	auto road = view->getRoad();
	GameTile* temp = road->getTileList().front();
	for (GameObstacle* o : temp->getObstacles())
		o->getNode()->remove();
	road->pop();

	RandomTileGenerator::generate(view->getRootNode(), driver);
	GameTile* randomTile = RandomTileGenerator::getTile();
	for (auto o : randomTile->getObstacles()) {
		o->addToScene(view->getSceneManager(), randomTile, road->getTileList().size() - 1);
		o->setScale();
		o->setTexture(driver);
		o->setMaterialProperty();
	}
	road->push(randomTile);
}

void GameController::gameOver(GameView* view){
	auto ship = view->getShip();
	view->getSoundEngine()->play2D("explosion.ogg");
	ship->startExplodingAnimation(view->getSceneManager());
	ship->setExploding(false);
	ship->getNode()->setVisible(false);
	GameSettings::gameOver = true;
	ship->getNode()->remove();
	ship->getExpAnimator()->drop();
	if (!view->getButtons().empty()) {
		for (auto button : view->getButtons()) {
			button->setVisible(true);
			button->setEnabled(true);
		}
	}
	view->getGameoverImg()->setVisible(true);
	((GameLeap*)leapListener)->getCursor()->setVisible(true);
}

/*

1- Aggiungere sul game leap una gesture che possa richiamare sul receiver la pausa.
3- Creare dei figli di obstacles che includano operazioni sul mesh.
4- Creare un ready... go! sul game state.

*/