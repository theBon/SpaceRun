#include "GameObstacle_Vertical.h"

GameObstacle_Vertical::~GameObstacle_Vertical(){
}

void GameObstacle_Vertical::setParams(){
	scale = vector3df(32, 96, 12);
	texturePath = "metal002.jpg";
}
