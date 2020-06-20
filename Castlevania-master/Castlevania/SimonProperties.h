#pragma once
#include "Whip.h"

class SimonProperties
{
	int state;
	Whip* whip;
	int currentSubWeapon;
	bool isOnStair;
	int heart;
	int hp;
	int score;
public:
	SimonProperties()
	{
		this->state = 0;
		this->whip = new Whip();
		this->currentSubWeapon = 0;
		this->isOnStair = false;
		this->heart = 0;
		this->hp = 10;
		this->score = 0;
	};
	void SetProperties(int state, Whip* whip, int currentSub, bool isOnStair, int heart, int hp, int score)
	{
		this->isOnStair = isOnStair;
		if (this->isOnStair == false)
		{
			this->state = 0;
		}
		else {
			this->state = state;
		}
		this->whip = whip;
		this->currentSubWeapon = currentSub;
		
		this->heart = heart;
		this->hp = hp;
		this->score = score;
	}

	int GetState() { return this->state; }
	Whip* GetWhip() { return this->whip; }
	int GetCurrentSub() { return this->currentSubWeapon; }
	bool GetisOnStair() { return this->isOnStair; }
	int GetHeart() { return this->heart; }
	int GetHp() { return this->hp; }
	int GetScore() { return this->score; }
};

