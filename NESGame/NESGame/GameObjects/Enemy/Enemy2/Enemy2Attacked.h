#pragma once
#include "Enemy2State.h"
class Enemy2Attacked : public Enemy2State
{
public:
	Enemy2Attacked();
	Enemy2Attacked(Enemy2Data *data);
	~Enemy2Attacked();
	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


