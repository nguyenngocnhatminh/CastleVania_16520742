#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include"Scene.h"
#include "Sprites.h"
#include"Animations.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define ID_TEX_SPRITE_BBOX_RED -101
#define ID_TEX_SPRITE_BBOX_BLUE -102

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;

struct CellIndex {
	int x;
	int y;
	CellIndex(int x, int y) :x(x), y(y) {};
};

struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
public:
	
	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;	 

	//int state;

	DWORD dt; 

	vector<LPANIMATION> animations;
	bool isDestroy = false;
	bool setDestroy = false;

	bool isEnemy;
	int EnemyID;

	CellIndex cellIndex = { -1,-1 };
	bool isActiveObject;	//active trong grid

public: 
	void Destroy() { this->isDestroy = true; }
	bool IsDestroy() { return isDestroy; }
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	void SetDestroy() {
		this->setDestroy = true;
	}
	void SetIsEnemy() { this->isEnemy = true; }
	bool IsEnemy() { return this->isEnemy; }
	//int GetState() { return this->state; }

	void SetCellIndex(CellIndex index)
	{
		this->cellIndex = index;
	}

	void SetCellIndex(int cellX, int cellY)
	{
		CellIndex index = { cellX,cellY };
		this->cellIndex = index;
	}

	CellIndex GetCellIndex()
	{
		return this->cellIndex;
	}

	void SetActive()
	{
		this->isActiveObject = true;
	}

	bool CheckActive()
	{
		return this->isActiveObject;
	}

	void RenderBoundingBox();

	void RenderBoundingBox(RECT rectX);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);


	// kiểm tra object hiện tại có đang va chạm với object a hay không
	bool isColliding(LPGAMEOBJECT a);
	// thuat toan xu ly va cham AABB
	bool AABB(float l, float t, float r, float b, float l1, float t1, float r1, float b1);




	void AddAnimation(string aniId);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	//virtual void SetState(int state) { this->state = state; }


	~CGameObject();
};

