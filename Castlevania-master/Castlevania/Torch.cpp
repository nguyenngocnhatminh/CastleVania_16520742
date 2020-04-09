#include "Torch.h"

void Torch::Render()
{
	if (!isDestroy)
	{
		animations[0]->Render(0, x, y);
	}
	RenderBoundingBox();
}

void Torch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isDestroy == false)
	{
		l = x;
		t = y;
		r = x + 32;
		b = y + 64;
	}
}
void Torch::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	if(this->isDestroy)
	{
		return;
	}
	if (this->setDestroy)
	{
		isDestroy = true;
	}
}