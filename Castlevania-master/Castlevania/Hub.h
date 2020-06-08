#pragma once
#include "Game.h"
class Hub
{
	CGame* Game;
	PlayScene* Scene;
	int score;
	int playerHP;
	int playerHeart;
	int BossHP;
	int gameTime;
	int currentWeapon;
	int state;
	RECT bound;
	std::string _UIinfo;
};

