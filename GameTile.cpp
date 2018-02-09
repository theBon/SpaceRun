#include "GameTile.h"

GameTile::GameTile(){
	deletable = false;
}

GameTile::GameTile(vector<GameObstacle*> v){
	deletable = false;
	obstacles = v;
}

GameTile::~GameTile(){
	obstacles.clear();
}

vector<GameObstacle*> GameTile::getObstacles(){
	return obstacles;
}

int GameTile::getDepth(){
	return depth;
}

bool GameTile::getDeletable(){
	return deletable;
}

void GameTile::setDeletable(bool b){
	deletable = b;
}

void GameTile::addObstacle(GameObstacle* obs){
	obstacles.push_back(obs);
}
