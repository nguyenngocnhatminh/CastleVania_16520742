#include "Enemy.h"

void Enemy::Render()
{
	animations[0]->Render(nx, x, y);
}

void Enemy::SetIsAttack(bool x)
{
	this->isAttack = x;
}
bool Enemy::IsAttack()
{
	return this->isAttack;
}

void Enemy::SpawnItem()
{
	if (this->setDestroy) {

	}
}

void Enemy::Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (dynamic_cast<PlayScene*>(scene))
	{
		PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
		if (pScene->GetIsFreeze() == true)
		{
			vx = 0;
			vy = 0;
			if (!animations[0]->CheckLockAnimation())
			{
				animations[0]->LockAnimation(true);
			}
			return;
		}
		else
		{
			animations[0]->LockAnimation(false);
		}
	}
}