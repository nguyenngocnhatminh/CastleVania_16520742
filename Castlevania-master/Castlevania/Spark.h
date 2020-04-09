
#include "Effect.h"


class Spark : public Effect
{
private:

public:
	Spark();
	~Spark();

	void Update(DWORD dt, Scene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};



