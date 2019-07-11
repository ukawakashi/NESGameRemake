#pragma once
#include "Enemy3State.h"
class Enemy3Fighting : public Enemy3State
{
public:
	Enemy3Fighting();
	Enemy3Fighting(Enemy3Data *data);
	~Enemy3Fighting();

	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


