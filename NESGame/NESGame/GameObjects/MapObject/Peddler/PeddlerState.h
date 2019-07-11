#pragma once
#include "../../Entity.h"
#include "PeddlerData.h"

class PeddlerState
{
public:
	PeddlerState();
	PeddlerState(PeddlerData *enemyData);

	PeddlerData *mData;
	~PeddlerState();

	enum StateName
	{
		None,
		Stand1,
		Stand2,
		Sell
	};
	virtual void Update();
	virtual StateName GetState() = 0;
	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};


