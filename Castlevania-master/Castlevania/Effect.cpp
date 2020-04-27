#include "Effect.h"

void Effect::Render()
{
	RenderBoundingBox();
}

void Effect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}
void Effect::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (isDestroy)
	{
		return;
	}

	if (lifetime != 0 && GetTickCount() - lifetime > EFFECT_LIFE_TIME)
	{
		this->isDestroy = true;
	}
}