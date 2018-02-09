#include "MainMenuView.h"

MainMenuView::MainMenuView(){
}

MainMenuView::~MainMenuView(){
}

irrklang::ISound * MainMenuView::getBgm(){
	return MainMenuView::bgm;
}

ITexture* MainMenuView::getAlertTexture(int i){
	return alerttxt[i];
}

IGUIImage* MainMenuView::getAlertImage(){
	return alertimage;
}

void MainMenuView::restore(){
	bgm = soundengine->play2D("bgm000.ogg", false, true);
	bgm->setIsPaused(false);
}

void MainMenuView::setupScene() {
	auto drv = gui->getVideoDriver();

	long w = wres::getWidth();
	long h = wres::getHeight();

	bgm = soundengine->play2D("bgm000.ogg", false, true);
	bgm->setIsPaused(false);

	irr::video::ITexture* texture = drv->getTexture("mainmenu.jpg");
	irr::gui::IGUIImage* image = gui->addImage(irr::core::rect<irr::s32>(0,0, w, h),
												rootElement,
												rootElement->getID() + 1
												);
	image->setImage(texture);
	image->setScaleImage(true);
	drv->removeTexture(texture);

	alerttxt[0] = drv->getTexture("alert0.png");
	alerttxt[1] = drv->getTexture("alert1.png");
	alertimage = gui->addImage(irr::core::rect<irr::s32>(w - 100, 0, w, 100), rootElement, rootElement->getID() + 4);
	alertimage->setScaleImage(true);

	auto title = gui->addImage(irr::core::recti(w/2 - w/5 , h/3, w, h), rootElement, rootElement->getID() + 2);
	title->setImage(drv->getTexture("spacerun.png"));

	auto NGameButton =
		gui->addButton(irr::core::rect<irr::s32>(w/2 - buttonWidth/2, h/2 ,
												 w/2 + buttonWidth/2, h/2 + buttonHeight),
						rootElement,						// elemento padre
						rootElement->getID() + 2,		    // id
						L"Gioca", L"Inizia una nuova partita");
	auto ExitButton =
		gui->addButton(irr::core::rect<irr::s32>(NGameButton->getAbsolutePosition().UpperLeftCorner.X, 
											NGameButton->getAbsolutePosition().UpperLeftCorner.Y + buttonHeight + verticalPadding,
											NGameButton->getAbsolutePosition().LowerRightCorner.X,
											NGameButton->getAbsolutePosition().LowerRightCorner.Y + buttonHeight + verticalPadding),
						rootElement,						// elemento padre
						rootElement->getID() + 3,		    // id
						L"Esci", L"Chiudi l'applicazione");
}