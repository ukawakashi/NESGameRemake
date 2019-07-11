#pragma once
#include "Enemy5State.h"
class Enemy5Fighting : public Enemy5State
{
public:
	Enemy5Fighting();
	Enemy5Fighting(Enemy5Data *data);
	~Enemy5Fighting();

	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


