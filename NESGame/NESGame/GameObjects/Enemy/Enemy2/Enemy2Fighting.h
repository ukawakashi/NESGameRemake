#pragma once
#include "Enemy2State.h"
class Enemy2Fighting : public Enemy2State
{
public:
	Enemy2Fighting();
	Enemy2Fighting(Enemy2Data *data);
	~Enemy2Fighting();

	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


