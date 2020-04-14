#include "MoneyBag.h"
#include"Ground.h"
void MoneyBag::Render()
{
	animations[0]->Render(0, x, y);
}

void MoneyBag::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 31;
	b = y + 30;
}

void MoneyBag::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, scene);
	vy = -0.1f;


	bool isCollideGround = false;
	for (std::size_t i = 0; i < coObjects->size(); i++) {
		{
			if (dynamic_cast<Ground*>(coObjects->at(i)))
			{
				Ground* f = dynamic_cast<Ground*> (coObjects->at(i));
				if (this->isColliding(f)) {
					isCollideGround = true;
				}
			}

		}
	}

	if (!isCollideGround)
	{
		vy = 0;
		vx = 0;
	}
	y += dy;
}