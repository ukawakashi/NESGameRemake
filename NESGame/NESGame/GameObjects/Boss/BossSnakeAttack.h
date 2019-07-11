#pragma once
#include "BossState.h"
class BossSnakeAttack : public BossState
{
public:
	BossSnakeAttack(BossData *data);
	~BossSnakeAttack();

	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


