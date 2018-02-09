#include "MainMenuController.h"

MainMenuController::MainMenuController(){
}

MainMenuController::~MainMenuController(){
}

int MainMenuController::getMessage(){
	return message;
}

void MainMenuController::takeData(int flag){
	message = flag;
}

void MainMenuController::update(){
	auto cursor = ((MainMenuLeap*)leapListener)->getCursor();
	cursor->setVisible(true);
	auto mmv = ((MainMenuView*)view);
	mmv->getAlertImage()->setImage(mmv->getAlertTexture(GameSettings::leapState));
}

