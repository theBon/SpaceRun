#ifndef __GAMESETTINGS_HEADER__
#define __GAMESETTINGS_HEADER__

class GameSettings
{
public:
	static bool leapState;

	static bool gamePaused;
	static bool gameReady;
	static bool gameOver;

	static short gameSpeed;
	static long score;

	static void togglePause();
};

#endif
