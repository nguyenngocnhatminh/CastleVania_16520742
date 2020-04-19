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
void SubWeapon::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{

	if (isDestroy)
	{
		return;
	}
	CGameObject::Update(dt, scene);
	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		D3DXVECTOR2 cam = pScene->GetCamera();

		if (x<cam.x || x>cam.x + SCREENSIZE::WIDTH)
		{
			this->isDestroy = true;
		}
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
