#include "HolyWater.h"
#include"Ground.h"
#include"Simon.h"
#include "Enemy.h"
#include "define.h"
#include "BreakWall.h"
#include "Effect.h"
#include "EffectCollection.h"
#include "Item.h"
#include "ItemCollection.h"
void HolyWater::Render()
{
	int ani;
	if (state == HOLYWATER_STATE_JAR)
	{
		ani = HOLYWATER_ANI_JAR;
	}
	else
	{
		ani = HOLYWATER_ANI_BURNING;
	}
	animations[ani]->Render(nx,x, y);
	RenderBoundingBox();
}

void HolyWater::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->setDestroy == true)
	{
		this->Destroy();
	}
	if (vy != 0)
	{
		vy += HOLYWATER_GRAVITY * dt;
	}
	if (this->state == HOLYWATER_ANI_JAR)
	{
		if (nx > 0)
		{
			this->vx = HOLYWATER_FALLING_VX;
		}
		else if (nx < 0)
		{
			this->vx = -HOLYWATER_FALLING_VX;
		}
	}

	CGameObject::Update(dt,scene);

	if (this->burning_start == 0)
	{
		if (this->state == HOLYWATER_STATE_BURNING)
		{
			this->burning_start = GetTickCount64();
		}

	}
	else if (GetTickCount64() - burning_start > HOLYWATER_BURNING_TIME) {
		this->Destroy();
	}

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if (x<cam.x || x>cam.x + SCREENSIZE::WIDTH || y < cam.y || y > cam.y + SCREENSIZE::HEIGHT)
		{
			this->isDestroy = true;
		}

	}

	if (isDestroy)
	{
		if (dynamic_cast<PlayScene*>(scene))
		{
			PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
			if (pScene->GetSimon()->EqualShot())
			{
				pScene->GetSimon()->UpCurrentShoot();
			}
		}
		return;
	}

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		// turn off collision when die 

		CalcPotentialCollisions(coObjects, coEvents);


		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;


			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			x += min_tx * dx + nx * 0.4f;
			if (ny <= 0)
				y += min_ty * dy + ny * 0.4f;

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<Ground*>(e->obj)) {
					if (e->ny <= 0)
					{
						this->SetState(HOLYWATER_STATE_BURNING);
					}
					
				}
				if (dynamic_cast<BreakWall*>(e->obj)) {
					this->SetState(HOLYWATER_STATE_BURNING);
				}
				else if (dynamic_cast<Enemy*>(e->obj)) {
					Enemy* z = dynamic_cast<Enemy*>(e->obj);
					if (!z->isDestroy)
					{
						if (state == HOLYWATER_ANI_JAR)
						{
							if (z->GetIsDameByHoly() == false)
							{
								z->SubtractHP(this->dame);
								z->SetIsDameByHoly(true);
								z->SetTimeHoly(GetTickCount());

							}
							x += dx;
							y += dy;
						}
						else
						{
							if (z->GetBurn() == false)
							{
								EffectCollection* effectcollection = new EffectCollection();
								Effect* spark = effectcollection->SpawnEffect(SPARK);
								if (dynamic_cast<PlayScene*>(scene))
								{
									spark->SetPosition(z->x, z->y);
									PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
									pScene->SpawnObject(spark);
								}
								z->SubtractHP(this->dame);
								z->SetBurn(true);
								z->SetTimeBurn(GetTickCount());
							}
						}
						if (z->GetHP() == 0)
						{
							if (dynamic_cast<PlayScene*>(scene))
							{
								PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
								pScene->GetSimon()->AddScore(z->GetScore());

								ItemCollection* itemcollection = new ItemCollection();
								Item* item = itemcollection->SpawnRandomItem(z->x);
								if (dynamic_cast<PlayScene*>(scene))
								{
									PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
									float tx, ty;
									z->GetPosition(tx, ty);
									item->SetPosition(tx, ty);
									pScene->SpawnObject(item);
								}

								z->Destroy();
							}

						}
					}
				}
				else {
					if (e->nx != 0)
						x += dx;
					if (e->ny != 0)
						y += dy;
				}
			}
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}

}

void HolyWater::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (this->state == HOLYWATER_ANI_JAR)
	{
		l = x + 4;
		t = y;
		r = l + HOLYWATER_BBOX_WIDTH - 8;
		b = t + HOLYWATER_BBOX_HEIGHT;
	}
	else
	{
		l = x;
		t = y;
		r = l + HOLYWATER_BBOX_WIDTH;
		b = t + HOLYWATER_BBOX_HEIGHT;
	}

}

void HolyWater::SetState(int state)
{
	this->state = state;
	switch (state)
	{
		case HOLYWATER_STATE_JAR:
			this->vy = -HOLYWATER_FALLING_VY;
			break;
		case HOLYWATER_STATE_BURNING:
		{
			this->vx = 0;
			this->vy = 0;
			break;
		}
	}
}
