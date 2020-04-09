#include "Effect.h"

void Effect::Render()
{
	if (!isDestroy)
	{
		animations[Spark_Effect]->Render(0, x, y);
	}
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

	if (life_time != 0 && GetTickCount() - life_time > EFFECT_LIFE_TIME)
	{
		this->isDestroy = true;
	}
}