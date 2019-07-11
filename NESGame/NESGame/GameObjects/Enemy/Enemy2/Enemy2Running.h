#pragma once
#include "Enemy2State.h"
class Enemy2Running : public Enemy2State
{
public:
	Enemy2Running();
	Enemy2Running(Enemy2Data *data);
	~Enemy2Running();

	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};





