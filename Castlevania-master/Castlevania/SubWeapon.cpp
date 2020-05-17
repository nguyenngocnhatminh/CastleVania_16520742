#include "SubWeapon.h"
#include"Torch.h"
#include"debug.h"
#include "Effect.h"
#include"Spark.h"
#include"flame.h"
#include"PlayScene.h"
#include"ItemCollection.h"
#include"EffectCollection.h"
#include "define.h"
#include"Candle.h"
#include"Ground.h"

void SubWeapon::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{

	if (isDestroy)
	{
		return;
	}
	CGameObject::Update(dt, scene);


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


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Ground*>(e->obj))
			{
				if (vy > 0)	// vy  0 la nhung vu khi roi duoc xuong dat
					this->is_touchable_ground=true;
				else
				{
					x += dx;
					y += dy;
				}
			}
			else if (dynamic_cast<Torch*>(e->obj)) {
				Torch* torch = dynamic_cast<Torch*>(e->obj);
					ItemCollection* itemcollection = new ItemCollection();
					Item* item = itemcollection->SpawnItem(torch->GetItem());
					EffectCollection* effectcollection = new EffectCollection();
					Effect* spark = effectcollection->SpawnEffect(1);	//1: id spark
					Effect* flame = effectcollection->SpawnEffect(2);	//2: id flame
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
				
			}
			else if (dynamic_cast<Candle*>(e->obj)) {

				Candle* candle = dynamic_cast<Candle*>(e->obj);
				ItemCollection* itemcollection = new ItemCollection();
				Item* item = itemcollection->SpawnItem(candle->GetItem());
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
				else if (nx != 0)
					y += dy;

			}
			else {
				if (nx != 0)
					x += dx;
				else if (nx != 0)
					y += dy;
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}

}
