#include "GameRoad.h"

GameRoad::GameRoad(){
}

GameRoad::GameRoad(GameTile * tile){
	push(tile);
	currentTile = 0;
}

GameRoad::GameRoad(deque<GameTile*> q){
	tileList = q;
	dimension = tileList.size();
	currentTile = 0;
}

GameRoad::~GameRoad(){
}

void GameRoad::push(GameTile* tile){
	tileList.push_back(tile);
}

void GameRoad::pop(){
		// Mi salvo il puntatore al tile per deallocarlo dopo averlo rimosso dalla road.
	GameTile* frontTile = tileList.front();
	tileList.pop_front();
	delete frontTile;
}

deque<GameTile*> GameRoad::getTileList(){
	return tileList;
}
