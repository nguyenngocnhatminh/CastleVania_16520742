#pragma once
#include"GameObject.h"
class SubWeapon:public CGameObject
{
protected:
	unsigned int dame;
	unsigned int heartCost;
	
public:
	SubWeapon();
	void SetNx(int nx)
	{
		this->nx = nx;
	}
	virtual void GetSpriteBox(float& width, float& height);
	unsigned int GetDame() {
		return this->dame;
	}
	unsigned int GetHeartCost()
	{
		return this->heartCost;
	}
};

