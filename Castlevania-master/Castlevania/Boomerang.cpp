#include "Boomerang.h"
#include"define.h"
#include"PlayScene.h"
void Boomerang::Render()
{
	if (isDestroy)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
}

void Boomerang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + BOOMERANG_BBOX_WIDTH;
	b = t + BOOMERANG_BBOX_HEIGHT;
}

void Boomerang::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (vx = nx)
	{
		if (nx > 0)
		{
			this->vx = BOOMERANG_VX;
		}
		else
		{
			this->vx = -BOOMERANG_VX;
		}
		boomerang_range--;
	}
	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if (x < cam.x+10 || x>cam.x + SCREENSIZE::WIDTH - BOOMERANG_BBOX_WIDTH || boomerang_range <= 0)
		{
			this->vx = -vx;
		}
	}
	SubWeapon::Update(dt, scene, colliable_objects);



}
