#pragma once
#include "Enemy.h"

#define RAVEN_BBOX_WIDTH 32
#define RAVEN_BBOX_HEIGHT 32

#define RAVEN_ANI_IDLE 1
#define	RAVEN_ANI_FLY 2
#define RAVEN_ANI_FLAP 3

#define RAVEN_STATE_IDLE 1
#define RAVEN_STATE_FLY 2
#define RAVEN_STATE_FLAP 3

class Raven:public Enemy
{
	int state;
public:
	Raven()
	{
		this->AddAnimation("RAVEN_ANI_IDLE");
		this->AddAnimation("RAVEN_ANI_FLY");
		this->AddAnimation("RAVEN_ANI_FLAP");
	}
};

