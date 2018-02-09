#ifndef __MAINMENUVIEW_HEADER__
#define __MAINMENUVIEW_HEADER__

#include "View.h"
#include <irrKlang.h>

using irr::video::ITexture;
using irr::gui::IGUIImage;

class MainMenuView : public View
{
	const int buttonWidth = 300;
	const int buttonHeight = 100;
	const int verticalPadding = 50;
	ITexture* alerttxt[2];
	IGUIImage* alertimage;
protected:
	irrklang::ISound* bgm;
	void setupScene();
public:
	MainMenuView(IGUIEnvironment* e, ISceneManager* s, ISoundEngine* se) : View(e, s, se) {
		setupScene();
	}
	MainMenuView();
	~MainMenuView();

	irrklang::ISound* getBgm();
	ITexture* getAlertTexture(int i);
	IGUIImage* getAlertImage();

	void restore();
};

#endif

