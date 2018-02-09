#include "GameObstacle.h"

GameObstacle::GameObstacle(){
}

GameObstacle::GameObstacle(path p, ISceneNode * prnt, vector3df rpos, vector3df rot = vector3df(0,0,0)){
	meshPath = p;
	parent = prnt;
	relativePosition = rpos;
	rotation = rot;
	scale = vector3df(1, 1, 1);
	texturePath = "";
}

GameObstacle::~GameObstacle(){
}

ISceneNode * GameObstacle::getNode(){
	return node;
}

vector3df GameObstacle::getRelativePosition(){
	return relativePosition;
}

void GameObstacle::setTile(GameTile * t){
	thisTile = t;
}

void GameObstacle::addToScene(ISceneManager* smng, GameTile* tile, int index){
	thisTile = tile;
	node = smng->addMeshSceneNode(smng->getMesh(meshPath), 
							parent, 
							parent->getID() + 15, 
							vector3df(relativePosition.X, relativePosition.Y, relativePosition.Z - index * thisTile->getDepth()), 
							rotation);
}

void GameObstacle::moveForward(int speed){
	if (node)
		node->setPosition(vector3df(node->getAbsolutePosition().X,
									node->getAbsolutePosition().Y,
									node->getAbsolutePosition().Z + speed));
}

void GameObstacle::setScale(){
	node->setScale(scale);
}

void GameObstacle::setTexture(irr::video::IVideoDriver* driver){
	node->setMaterialTexture(0, driver->getTexture(texturePath));
}

void GameObstacle::setMaterialProperty(){
	for (int i = 0; i < node->getMaterialCount(); i++) {
		node->getMaterial(i).Lighting = false;
		node->getMaterial(i).TextureLayer[0].AnisotropicFilter = true;
	}
}
