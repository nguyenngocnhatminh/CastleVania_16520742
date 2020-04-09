#include "knife.h"
#include"Torch.h"
#include"Simon.h"

void knife::Render()
{
	animations[0]->Render(nx, x, y);
	RenderBoundingBox();
}

void knife::Update(DWORD dt, Scene* scene,vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroy)
	{
		return;
	}
	if (this->SetDestroy)
	{
		this->isDestroy = true;
		return;
	}

	CGameObject::Update(dt,scene);
	if (nx > 0) this->vx = KNIFE_SPEED_X;
	else if (nx < 0)this->vx = -KNIFE_SPEED_X;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Torch*>(e->obj))
			{
				Torch* torch = dynamic_cast<Torch*>(e->obj);
				if (!torch->isDestroy)
				{
					torch->SetDestroy();
				}
				this->SetDestroy();
			}
		}
	}

}