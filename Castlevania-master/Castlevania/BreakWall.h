#pragma once
#include"GameObject.h"

#define BREAKWALL_BBOX_WIDTH 32
#define BREAKWALL_BBOX_HEIGHT 32
#define BREAKWALL_STATE_NORMAL 0
#define BREAKWALL_STATE_BREAK 1

#define BREAKWALL_ANI_NORMAL 0
#define BREAKWALL_ANI_BREAK 1

class BreakWall:public CGameObject
{
	int state;
	int Item = 0;
public:
	BreakWall()
	{
		state = BREAKWALL_STATE_NORMAL;
		AddAnimation("BRICK_ANI_NORMAL");
		AddAnimation("BRICK_ANI_BREAKING");
	};
	~BreakWall();
	void SetItem(int Item) {
		this->Item = Item;
	}
	void SetState(int state)
	{
		this->state = state;
	}
	int GetItem() { return this->Item; }
	virtual void Render();
	virtual void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void GetBoundingBox(float& l, float&t, float& r, float& b);
};

