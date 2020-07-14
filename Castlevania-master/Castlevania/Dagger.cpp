#include "Dagger.h"
#include"PlayScene.h"
#include "define.h"
void Dagger::Render()
{
	if (isDestroy)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
}

void Dagger::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + DAGGER_BBOX_WIDTH;
	b = t + DAGGER_BBOX_HEIGHT;
}

void Dagger::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	vx = nx > 0 ? this->vx = DAGGER_VX : this->vx = -DAGGER_VX;

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if (x<cam.x || x>cam.x + SCREENSIZE::WIDTH)
		{
			this->isDestroy = true;
		}
	}

	SubWeapon::Update(dt, scene, colliable_objects);



}
