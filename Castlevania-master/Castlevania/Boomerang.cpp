#include "Boomerang.h"
#include"define.h"
#include"PlayScene.h"
#include "debug.h"
#include "Ground.h"
#include "Torch.h"
#include "Effect.h"
#include"ItemCollection.h"
#include"EffectCollection.h"
#include "Candle.h"
#include "Enemy.h"
void Boomerang::Render()
{
	if (isDestroy)
	{
		return;
	}
	animations[0]->Render(nx, x, y);
}

void Boomerang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + BOOMERANG_BBOX_WIDTH;
	b = t + BOOMERANG_BBOX_HEIGHT;
}

void Boomerang::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (isBack == false)
	{
		if (nx > 0)
		{
			this->vx = BOOMERANG_VX;
		}
		else
		{
			this->vx = -BOOMERANG_VX;
		}
		boomerang_range--;
	}
	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();


		if (((int)x < (int)(cam.x+10) || (int)x > (int)(cam.x + SCREENSIZE::WIDTH - BOOMERANG_BBOX_WIDTH) || boomerang_range <= 0)
			&& this->isBack == false)
		{
			this->vx = -vx;
			this->isBack = true;
			this->BacktoSimon = true;
			this->boomerang_range = 50;
			DebugOut(L"bom\n");
		}
	}
	if (this->BacktoSimon == true)
	{
		this->SetCollideOneTime();
		this->BacktoSimon = false;
		DebugOut(L"boom\n");
	}
	

	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if (x<cam.x || x>cam.x + SCREENSIZE::WIDTH - 10 || y < cam.y || y > cam.y + SCREENSIZE::HEIGHT - 20)
		{
			this->setDestroy = true;
		}

	}

	if (setDestroy)
	{
		if (dynamic_cast<PlayScene*>(scene))
		{
			PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
			if (pScene->GetSimon()->EqualShot())
			{
				pScene->GetSimon()->UpCurrentShoot();
			}
		}
		this->Destroy();
	}
	CGameObject::Update(dt, scene);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 

	CalcPotentialCollisions(colliable_objects, coEvents);

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


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Torch*>(e->obj)) {
				Torch* torch = dynamic_cast<Torch*>(e->obj);
				ItemCollection* itemcollection = new ItemCollection();
				Item* item = itemcollection->SpawnItem(torch->GetItem(), torch->x);
				EffectCollection* effectcollection = new EffectCollection();
				Effect* spark = effectcollection->SpawnEffect(SPARK);	//1: id spark
				Effect* flame = effectcollection->SpawnEffect(FLAME);	//2: id flame
				if (dynamic_cast<PlayScene*>(scene))
				{
					PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
					DebugOut(L"Va cham voi torch \n");
					float tx, ty;
					torch->GetPosition(tx, ty);
					spark->SetPosition(tx, ty + 8);
					flame->SetPosition(tx + 5, ty + 10);
					item->SetPosition(tx, ty);
					pScene->SpawnObject(spark);
					pScene->SpawnObject(flame);
					pScene->SpawnObject(item);
					torch->SetDestroy();
				}
				if (nx != 0)
					x += dx;
				if (ny != 0)
					y += dy;

			}
			else if (dynamic_cast<Candle*>(e->obj)) {

				Candle* candle = dynamic_cast<Candle*>(e->obj);
				ItemCollection* itemcollection = new ItemCollection();
				Item* item = itemcollection->SpawnItem(candle->GetItem(), candle->x);
				EffectCollection* effectcollection = new EffectCollection();
				Effect* spark = effectcollection->SpawnEffect(SPARK);	//1: id spark
				Effect* flame = effectcollection->SpawnEffect(FLAME);	//2: id flame
				if (dynamic_cast<PlayScene*>(scene))
				{
					PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
					DebugOut(L"Va cham voi torch \n");
					float tx, ty;
					candle->GetPosition(tx, ty);
					spark->SetPosition(tx, ty + 8);
					flame->SetPosition(tx + 5, ty + 10);
					item->SetPosition(tx, ty);
					pScene->SpawnObject(spark);
					pScene->SpawnObject(flame);
					pScene->SpawnObject(item);
					candle->SetDestroy();
				}
				if (nx != 0)
					x += dx;
				if (ny != 0)
					y += dy;

			}
			else if (dynamic_cast<Enemy*>(e->obj)) {
				Enemy* f = dynamic_cast<Enemy*> (e->obj);
				if (!f->GetHurtByBom()&& !this->isBack
					|| this->isBack && !f->GetHurtByBomReturn())
				{
					EffectCollection* effectcollection = new EffectCollection();
					Effect* spark = effectcollection->SpawnEffect(SPARK);
					if (!f->IsDestroy())
					{
						if (dynamic_cast<PlayScene*>(scene))
						{
							spark->SetPosition(f->x, f->y);
							PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
							pScene->SpawnObject(spark);
						}
						f->SubtractHP(this->dame);				
						if (!this->isBack)
						{
							f->SetHurtByBom(true);
							f->SetTimeHurtByBom(GetTickCount());
						}
						else
						{
							f->SetHurtByBomReturn(true);
							f->SetTimeHurtByBomReturn(GetTickCount());

						}
						if (f->GetHP() == 0)
						{
							if (dynamic_cast<PlayScene*>(scene))
							{
								PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
								pScene->GetSimon()->SetScore(pScene->GetSimon()->GetScore() + f->GetScore());
							}

							ItemCollection* itemcollection = new ItemCollection();
							Item* item = itemcollection->SpawnRandomItem(f->x);
							if (dynamic_cast<PlayScene*>(scene))
							{
								PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
								float tx, ty;
								f->GetPosition(tx, ty);
								item->SetPosition(tx, ty);
								pScene->SpawnObject(item);
							}
							f->Destroy();
						}
						x += dx;
						y += dy;
					}
					else
					{
						x += dx;
						y += dy;

					}
				}
			}
			else {
				if (nx != 0)
					x += dx;
				if (ny != 0)
					y += dy;
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}


}
