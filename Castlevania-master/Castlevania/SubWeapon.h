#pragma once
#include"GameObject.h"


class SubWeapon :public CGameObject
{
protected:
public:

	virtual void Render() {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetNx(int nx) { this->nx = nx; }

};

