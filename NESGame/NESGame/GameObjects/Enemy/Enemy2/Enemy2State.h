#pragma once
#include "../../Entity.h"
#include "Enemy2Data.h"

class Enemy2State
{
public:
	Enemy2State();
	Enemy2State(Enemy2Data *enemyData);

	Enemy2Data *mData;
	~Enemy2State();

	enum StateName
	{
		None,
		Benkon,
		Running,
		Attack,
		Attacked,
		Die,
		WalkHotcoal
	};
	virtual void Update();
	virtual StateName GetState() = 0;
	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


