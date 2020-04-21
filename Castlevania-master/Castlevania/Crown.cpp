#include "Crown.h"
#include"Ground.h"
void Crown::Render()
{
	animations[0]->Render(0, x, y);
}

void Crown::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 32;
	b = y + 30;
}

void Crown::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, scene);
	if (GetIsHidden() == true)
	{
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
	else
		Item::Update(dt, scene, coObjects);
}
