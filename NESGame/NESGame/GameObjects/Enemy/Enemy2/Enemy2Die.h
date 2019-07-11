#pragma once
#include "Enemy2State.h"
class Enemy2Die : public Enemy2State
{
public:
	Enemy2Die();
	Enemy2Die(Enemy2Data *data);
	~Enemy2Die();
	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

