#pragma once
#include "PeddlerState.h"
class PeddlerSell : public PeddlerState
{
public:
	PeddlerSell();
	PeddlerSell(PeddlerData *data);
	~PeddlerSell();
	void Update();
	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


