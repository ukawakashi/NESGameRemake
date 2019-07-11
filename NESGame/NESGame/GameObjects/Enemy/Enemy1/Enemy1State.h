#pragma once
#include "../../Entity.h"
#include "Enemy1Data.h"

class Enemy1State
{
public:
	Enemy1State();
	~Enemy1State();

	Enemy1State(Enemy1Data *enemyData);
	Enemy1Data *mData;
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

