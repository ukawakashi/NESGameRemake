#pragma once
#include "../../Entity.h"
#include "Enemy5Data.h"

class Enemy5State
{
public:
	Enemy5State();
	Enemy5State(Enemy5Data *enemyData);

	Enemy5Data *mData;
	~Enemy5State();

	enum StateName
	{
		None,
		Running,
		Attack,
		Attacked,
		Die
	};
	virtual void Update();
	virtual StateName GetState() = 0;
	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


