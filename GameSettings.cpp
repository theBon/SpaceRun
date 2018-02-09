#include "GameSettings.h"
bool GameSettings::leapState;

bool GameSettings::gamePaused;
bool GameSettings::gameReady;
bool GameSettings::gameOver;

short GameSettings::gameSpeed;
long GameSettings::score;

void GameSettings::togglePause() {
	GameSettings::gamePaused = !GameSettings::gamePaused;
}
