#include "Heart.h"

void Heart::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + HEART_WIDTH;
	b = y + HEART_HEIGHT;
}
void Heart::Render()
{
	if (isDestroy || wait_time)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
	//RenderBoundingBox();
}
