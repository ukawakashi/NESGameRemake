#pragma once
#include "PlayerState.h"

class PLayerRevive : public PlayerState
{
public:
	PLayerRevive(PlayerData *playerData);
	~PLayerRevive();
	void Update(float dt);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	virtual StateName GetState();
};




