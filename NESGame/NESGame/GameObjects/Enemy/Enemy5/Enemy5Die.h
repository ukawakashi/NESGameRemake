#pragma once
#include "Enemy5State.h"
class Enemy5Die : public Enemy5State
{
public:
	Enemy5Die();
	Enemy5Die(Enemy5Data *data);
	~Enemy5Die();
	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

