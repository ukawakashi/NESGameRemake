#pragma once
#include "Enemy5State.h"
class Enemy5Attacked : public Enemy5State
{
public:
	Enemy5Attacked();
	Enemy5Attacked(Enemy5Data *data);
	~Enemy5Attacked();
	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


