#pragma once
#include "BossData.h"

#include "../Entity.h"
class BossState
{
public:
	BossState();
	~BossState();
	enum StateName
	{
		None,
		StandJafar,
		StandSnake,
		JafarAttack,
		SnakeAttack,
		Die
	};

	BossState(BossData *enemyData);
	BossData *mData;
	virtual void Update();
	virtual StateName GetState() = 0;
	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

