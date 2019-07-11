#pragma once
#include "../../Entity.h"
#include "Enemy3Data.h"

class Enemy3State
{
public:
	Enemy3State();
	Enemy3State(Enemy3Data *enemyData);

	Enemy3Data *mData;
	~Enemy3State();

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


