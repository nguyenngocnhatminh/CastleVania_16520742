#pragma once
#include"GameObject.h"

#define BRIDGE_BBOX_WIDTH  66
#define BRIDGE_BBOX_HEIGHT 20

#define BRIDGE_VX 0.05F

class Bridge :public CGameObject
{
protected:
public:
	Bridge() :CGameObject() {
		vx = BRIDGE_VX;
		AddAnimation("BRIDGE_ANI");	//0	
	}
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

