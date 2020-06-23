#pragma once
#include"Game.h"
class CGame;
class PlayScene;
class Hub
{
	CGame* Game;
	PlayScene* scene;
	int score;
	int playerHP;
	int playerHeart;
	static int BossHP;
	int gameTime;
	int currentWeapon;
	int state;
	RECT bound;
	std::string _UIinfo;
public:
	static void SetBossHP(int hp)
	{
		BossHP = hp;
	}
	void Update();
	void Render();
	Hub(PlayScene* scene);
	~Hub();
};

