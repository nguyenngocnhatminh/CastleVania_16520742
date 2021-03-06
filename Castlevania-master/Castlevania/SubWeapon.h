#pragma once
#include"GameObject.h"


class SubWeapon :public CGameObject
{
protected:
	float height;
	float width;
	bool is_touchable_ground;
	int heart_cost;
	int dame = 1;
	bool collideOneTime = false;
	bool hitObject = false;
	bool isDameBoss = false;
public:

	virtual void Render() {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetNx(int nx) { this->nx = nx; }
	float GetHeight() { return this->height; }
	float GetWidth() { return this->width; }
	virtual void SetHeight() {};
	virtual void SetWidth() {};
	void SetHeartCost(int x);
	int GetHeartCotst();
	void SetDame(int x);
	int GetDame();
	void SetCollideOneTime()
	{
		this->collideOneTime = false;
	}
	bool GetCollideOneTime()
	{
		return this->collideOneTime;
	}
};

