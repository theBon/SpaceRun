#ifndef __GAMEOBSTACLE_HEADER__
#define __GAMEOBSTACLE_HEADER__

#include "GameTile.h"
#include <irrlicht.h>

using irr::scene::ISceneManager;
using irr::scene::IMeshSceneNode;
using irr::scene::ISceneNode;
using irr::core::vector3df;
using irr::video::ITexture;
using irr::io::path;

class GameObstacle
{
protected:
	IMeshSceneNode* node;
	ISceneNode* parent;
	GameTile* thisTile;
	vector3df relativePosition;
	vector3df rotation;
	vector3df scale;
	path meshPath;
	path texturePath;
public:
	GameObstacle();
	GameObstacle(path p, ISceneNode* prnt, vector3df rpos, vector3df rot);
	~GameObstacle();

	ISceneNode* getNode();
	vector3df getRelativePosition();
	void setTile(GameTile* t);
	void addToScene(ISceneManager* smng, GameTile* tile, int index);
	void moveForward(int speed);

	virtual void setScale();
	virtual void setTexture(irr::video::IVideoDriver* driver);
	virtual void setMaterialProperty();
};

#endif