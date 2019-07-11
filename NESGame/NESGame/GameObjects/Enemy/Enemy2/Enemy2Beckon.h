#pragma once
#include "Enemy2State.h"
class Enemy2Beckon : public Enemy2State
{
public:
	Enemy2Beckon();
	Enemy2Beckon(Enemy2Data *data);
	~Enemy2Beckon();

	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


