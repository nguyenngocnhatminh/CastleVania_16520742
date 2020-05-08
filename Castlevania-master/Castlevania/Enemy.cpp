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
void Enemy::SetID(int id)
{
	this->ID = id;
}
int Enemy::GetID()
{
	return this->ID;
}