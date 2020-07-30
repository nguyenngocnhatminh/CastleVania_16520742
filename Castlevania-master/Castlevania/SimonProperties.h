#pragma once
#include "Whip.h"

class SimonProperties
{
	int whipLevel;
	int currentSubWeapon;
	int heart;
	int hp;
	int score;
	int shootstate;
public:
	SimonProperties()
	{
		this->whipLevel = 0;
		this->currentSubWeapon = 0;
		this->heart = 0;
		this->hp = 16;
		this->score = 0;
		this->shootstate = 0;
	};
	void SetProperties(int whip, int currentSub, int heart, int hp, int score,int shootstate)
	{
		this->whipLevel = whip;
		this->currentSubWeapon = currentSub;
		
		this->heart = heart;
		this->hp = hp;
		this->score = score;
		this->shootstate = shootstate;
	}

	int GetWhip() { return this->whipLevel; }
	int GetCurrentSub() { return this->currentSubWeapon; }
	int GetHeart() { return this->heart; }
	int GetHp() { return this->hp; }
	int GetScore() { return this->score; }
	int GetShootstate() { return this->shootstate; }
};

