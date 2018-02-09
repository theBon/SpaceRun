#include "RandomTileGenerator.h"

GameTile* RandomTileGenerator::tile;

GameTile * RandomTileGenerator::getTile(){
	return tile;
}

void RandomTileGenerator::generate(ISceneNode* rootNode, irr::video::IVideoDriver* d){
	int r = rand() % 10;
	std::vector<GameObstacle*> v;
	switch (r) {
	case 0:
		v = {
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, -5, -90), vector3df(0, 0, 0)),
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, -20, -90), vector3df(0, 0, 0))
		};
		createTile(v, d);
		break;
	case 1:
		v = {
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, -5, -90), vector3df(0, 0, 0)),
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, -20, -90), vector3df(0, 0, 0))
		};
		createTile(v, d);
		break;
	case 2:
		v = {
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, -5, -90), vector3df(0, 0, 0)),
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, -20, -90), vector3df(0, 0, 0))
		};
		createTile(v, d);
		break;
	case 3:
		v = {
			new GameObstacle_Vertical("box.obj", rootNode, vector3df(20, 0, -100), vector3df(0, 0, 0)),
			new GameObstacle_Vertical("box.obj", rootNode, vector3df(-30, 0, -100), vector3df(0, 0, 0))
		};
		createTile(v, d);
		break;
	case 4:
		v = {
			new GameObstacle_Vertical("box.obj", rootNode, vector3df(20, 0, -100), vector3df(0, 0, 0)),
			new GameObstacle_Vertical("box.obj", rootNode, vector3df(-30, 0, -100), vector3df(0, 0, 0))
		};
		createTile(v, d);
		break;
	case 5:
		v = {
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, 15, -90), vector3df(0, 0, 0)),
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, 0, -90), vector3df(0, 0, 0))
		};
		createTile(v, d);
		break;
	case 6:
		v = {
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, 15, -90), vector3df(0, 0, 0)),
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, 0, -90), vector3df(0, 0, 0))
		};
		createTile(v, d);
		break;
	case 7:
		v = {
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, 15, -90), vector3df(0, 0, 0)),
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, 0, -90), vector3df(0, 0, 0))
		};
		createTile(v, d);
		break;
	case 8:
		v = {
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, 15, -90), vector3df(0, 0, 0)),
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, -15, -90), vector3df(0, 0, 0))
		};
		createTile(v, d);
		break;
	case 9:
		v = {
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, 15, -90), vector3df(0, 0, 0)),
			new GameObstacle_Horizontal("box.obj", rootNode, vector3df(-5, -15, -90), vector3df(0, 0, 0))
		};
		createTile(v, d);
		break;
	}
}

void RandomTileGenerator::createTile(std::vector<GameObstacle*> vec, irr::video::IVideoDriver* d){
	tile = new GameTile(vec);
}
