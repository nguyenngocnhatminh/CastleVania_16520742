#pragma once
#include "Whip.h"

class SimonProperties
{
	int whipLevel;
	int currentSubWeapon;
	int heart;
	int hp;
	int score;
public:
	SimonProperties()
	{
		this->whipLevel = 0;
		this->currentSubWeapon = 0;
		this->heart = 0;
		this->hp = 10;
		this->score = 0;
	};
	void SetProperties(int whip, int currentSub, int heart, int hp, int score)
	{
		this->whipLevel = whip;
		this->currentSubWeapon = currentSub;
		
		this->heart = heart;
		this->hp = hp;
		this->score = score;
	}

	int GetWhip() { return this->whipLevel; }
	int GetCurrentSub() { return this->currentSubWeapon; }
	int GetHeart() { return this->heart; }
	int GetHp() { return this->hp; }
	int GetScore() { return this->score; }
};

