#pragma once
#include "BossState.h"
class BossJafarAttack: public BossState
{
public:
	BossJafarAttack(BossData *data);
	~BossJafarAttack();
	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	int check =1;
};

