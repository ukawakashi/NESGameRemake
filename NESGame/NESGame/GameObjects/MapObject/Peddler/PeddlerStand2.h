#pragma once
#include "PeddlerState.h"
class PeddlerStand2 : public PeddlerState
{
public:
	PeddlerStand2();
	PeddlerStand2(PeddlerData *data);
	~PeddlerStand2();

	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


