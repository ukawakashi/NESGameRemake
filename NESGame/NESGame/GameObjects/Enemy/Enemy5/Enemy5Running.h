#pragma once
#include "Enemy5State.h"
class Enemy5Running : public Enemy5State
{
public:
	Enemy5Running();
	Enemy5Running(Enemy5Data *data);
	~Enemy5Running();
	bool check = true;
	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};





