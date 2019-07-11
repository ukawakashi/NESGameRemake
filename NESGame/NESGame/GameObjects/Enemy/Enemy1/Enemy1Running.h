#pragma once
#include "Enemy1State.h"
class Enemy1Running : public Enemy1State
{
public:
	Enemy1Running();
	Enemy1Running(Enemy1Data *data);
	~Enemy1Running();

	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};



