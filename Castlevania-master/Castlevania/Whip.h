#pragma once
#include"GameObject.h"


#define WHIP_STATE_NORMAL      0
#define WHIP_STATE_CHAIN       1
#define WHIP_STATE_MORNINGSTAR 2

#define WHIP_ANI_NORMAL      0
#define WHIP_ANI_CHAIN       1
#define WHIP_ANI_MORNINGSTAR 2

#define WHIP_BBOX_NORMAL_WIDTH 55
#define WHIP_BBOX_NORMAL_HEIGHT 15

#define WHIP_BBOX_CHAIN_WIDTH 55
#define WHIP_BBOX_CHAIN_HEIGHT 15

#define WHIP_BBOX_MORNINGSTAR_WIDTH 85
#define WHIP_BBOX_MORNINGSTAR_HEIGHT 15

class Whip:public CGameObject
{
private:
	int state = 0;
	unsigned int damege;
	bool collideOneTime = false;
	bool hitObject = false;
	int current_ani;
	int lastFrame;
public:
	Whip() {
		AddAnimation("WHIP_ANI_NORMAL");
		AddAnimation("WHIP_ANI_CHAIN");
		AddAnimation("WHIP_ANI_MORNINGSTAR");
	}
	void ResetWhip();
	
	virtual void Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetNxDirection(int nx) {
		this->nx=nx;
	}
	int getCurrentAni();
	void UpLevel();
	bool CheckLastFrame();
	
};

