#include "Dagger.h"

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
	if (isDestroy)
	{
		return;
	}
	vx = nx > 0 ? this->vx = DAGGER_VX : this->vx = -DAGGER_VX;

	SubWeapon::Update(dt, scene, colliable_objects);



}
