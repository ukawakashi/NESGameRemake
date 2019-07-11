#pragma once
#include "Enemy3State.h"
class Enemy3Attacked : public Enemy3State
{
public:
	Enemy3Attacked();
	Enemy3Attacked(Enemy3Data *data);
	~Enemy3Attacked();
	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


