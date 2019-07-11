#pragma once
#include "Enemy1State.h"
class Enemy1Die : public Enemy1State
{
public:
	Enemy1Die();
	Enemy1Die(Enemy1Data *data);
	~Enemy1Die();
	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

