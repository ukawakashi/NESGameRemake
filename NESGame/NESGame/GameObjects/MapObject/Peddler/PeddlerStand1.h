#pragma once
#include "PeddlerState.h"
class PeddlerStand1 : public PeddlerState
{
public:
	PeddlerStand1();
	PeddlerStand1(PeddlerData *data);
	~PeddlerStand1();
	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

