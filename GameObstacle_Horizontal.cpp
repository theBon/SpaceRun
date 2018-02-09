#include "GameObstacle_Horizontal.h"

GameObstacle_Horizontal::~GameObstacle_Horizontal(){
}

void GameObstacle_Horizontal::setParams() {
	scale = vector3df(96, 24, 12);
	texturePath = "metal002.jpg";
}