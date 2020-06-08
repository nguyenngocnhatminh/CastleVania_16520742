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