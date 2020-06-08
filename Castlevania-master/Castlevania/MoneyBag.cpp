#include "MoneyBag.h"
#include"Ground.h"
void MoneyBag::Render()
{
	int ani = 0;
	switch (state)
	{
	case MONEYBAG_RED:
		ani = MONEYBAG_RED;
		break;
	case MONEYBAG_BLUE:
		ani = MONEYBAG_BLUE;
		break;
	case MONEYBAG_WHITE:
		ani = MONEYBAG_WHITE;
		break;
	case MONEYBAG_COLORFUL:
		ani = MONEYBAG_COLORFUL;
		break;
	}
	animations[ani]->Render(0, x, y);
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

void MoneyBag::SetState(int state)
{
	this->state = state;
	switch (this->state)
	{
	case MONEYBAG_RED:
		this->SetScore(MONEYBAG_RED_SCORE);
		break;
	case MONEYBAG_BLUE:
		this->SetScore(MONEYBAG_BLUE_SCORE);
		break;
	case MONEYBAG_WHITE:
		this->SetScore(MONEYBAG_WHITE_SCORE);
		break;
	case MONEYBAG_COLORFUL:
		this->SetScore(MONEYBAG_COLOR_SCORE);
		break;
	}
}

int MoneyBag::GetState()
{
	return this->state;
}