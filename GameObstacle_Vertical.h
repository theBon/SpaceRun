#ifndef __GAMEOBSTACLEVERTICAL_HEADER__
#define __GAMEOBSTACLEVERTICAL_HEADER__

#include "GameObstacle.h"

class GameObstacle_Vertical : public GameObstacle
{
public:
	GameObstacle_Vertical(path p, ISceneNode* prnt, vector3df rpos, vector3df rot) 
		: GameObstacle(p, prnt, rpos, rot) {
		setParams();
	}
	~GameObstacle_Vertical();
private:
	void setParams();
};

#endif