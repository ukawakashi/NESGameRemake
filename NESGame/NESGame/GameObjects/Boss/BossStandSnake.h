#pragma once
#include "BossState.h"
class BossStandSnake : public BossState
{
public:
	BossStandSnake(BossData *data);
	~BossStandSnake();
	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	int StartTime;
};


