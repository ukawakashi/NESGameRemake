#pragma once
#include "BossState.h"
class BossStandJafar : public BossState
{
public:
	BossStandJafar(BossData *data);
	~BossStandJafar();
	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	int StartTime;
};

