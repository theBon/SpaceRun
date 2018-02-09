#ifndef __GAMEROAD_HEADER__
#define __GAMEROAD_HEADER__

#include "GameTile.h"
#include <deque>

using std::deque;

class GameRoad
{
	deque<GameTile*> tileList;
	int dimension;
	int currentTile;
	float zspeed;
	const float initialZposition = -100;
public:
	GameRoad();
	GameRoad(GameTile* tile);
	GameRoad(deque<GameTile*> q);
	~GameRoad();

	void push(GameTile* tile);
	void pop();
	deque<GameTile*> getTileList();
};

#endif