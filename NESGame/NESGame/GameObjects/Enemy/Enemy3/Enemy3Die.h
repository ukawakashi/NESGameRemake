#pragma once
#include "Enemy3State.h"
class Enemy3Die : public Enemy3State
{
public:
	Enemy3Die();
	Enemy3Die(Enemy3Data *data);
	~Enemy3Die();
	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

