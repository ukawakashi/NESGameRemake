#pragma once
#include "Enemy1State.h"
class Enemy1Attacked : public Enemy1State
{
public:
	Enemy1Attacked();
	Enemy1Attacked(Enemy1Data *data);
	~Enemy1Attacked();
	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


