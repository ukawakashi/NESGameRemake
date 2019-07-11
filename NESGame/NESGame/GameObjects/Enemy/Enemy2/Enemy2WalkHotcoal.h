#pragma once
#include "Enemy2State.h"
class Enemy2WalkHotcoal : public Enemy2State
{
public:
	Enemy2WalkHotcoal();
	Enemy2WalkHotcoal(Enemy2Data *data);
	~Enemy2WalkHotcoal();
	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

