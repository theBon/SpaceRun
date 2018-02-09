#ifndef __RANDOMTILEGENERATOR_HEADER__
#define __RANDOMTILEGENERATOR_HEADER__

#include <cstdlib>
#include <irrlicht.h>
#include <initializer_list>
#include <vector>
#include "GameTile.h"
#include "GameObstacle.h"
#include "GameObstacle_Vertical.h"
#include "GameObstacle_Horizontal.h"

class RandomTileGenerator
{
	static GameTile* tile;
public:
	static GameTile* getTile();
	static void generate(ISceneNode* rootNode, irr::video::IVideoDriver* d);
private:
	static void createTile(std::vector<GameObstacle*> vec, irr::video::IVideoDriver* d);
};

#endif