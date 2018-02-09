#ifndef __GAMETILE_HEADER__
#define __GAMETILE_HEADER__

#include <vector>
using std::vector;

	// Definisco provvisoriamente GameObstacle, non posso includerne l'header.
class GameObstacle;
class GameTile
{
	vector<GameObstacle*> obstacles;
	const float depth = 150;
	bool deletable;
public:
	GameTile();
	GameTile(vector<GameObstacle*> v);
	~GameTile();

	vector<GameObstacle*> getObstacles();
	int getDepth();
	bool getDeletable();
	void setDeletable(bool b);

	void addObstacle(GameObstacle* obs);
};

#endif
