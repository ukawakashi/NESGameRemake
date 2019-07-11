#pragma once
#include "Enemy1State.h"
class Enemy1Fighting : public Enemy1State
{
public:
	Enemy1Fighting();
	Enemy1Fighting(Enemy1Data *data);
	~Enemy1Fighting();

	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


