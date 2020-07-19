#include "StopWatch.h"
#include "Hub.h"

void StopWatch::Update(DWORD dt,Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{
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

	if (this->isDestroy)
	{
		return;
	}

	if (this->stopwatch_start != 0)
	{
		if (dynamic_cast<PlayScene*>(scene))
		{
			PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
			pScene->SetIsFreeze(true);
		}

	}
	if (GetTickCount() - this->stopwatch_start > STOPWATCH_FREEZE_TIME)
	{
		if (dynamic_cast<PlayScene*>(scene))
		{
			PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
			pScene->SetIsFreeze(false);
			this->SetDestroy();
		}
	}
}


StopWatch::StopWatch() :SubWeapon()
{
	this->stopwatch_start = GetTickCount();
	this->dame = 0;
	this->heart_cost = 5;
}


StopWatch::~StopWatch()
{
}
