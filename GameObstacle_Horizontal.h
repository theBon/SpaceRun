#ifndef __GAMEOBSTACLEHORIZONTAL_HEADER__
#define __GAMEOBSTACLEHORIZONTAL_HEADER__

#include "GameObstacle.h"

class GameObstacle_Horizontal : public GameObstacle
{
public:
	GameObstacle_Horizontal(path p, ISceneNode* prnt, vector3df rpos, vector3df rot)
		: GameObstacle(p, prnt, rpos, rot) {
		setParams();
	}
	~GameObstacle_Horizontal();
private:
	void setParams();

};

#endif