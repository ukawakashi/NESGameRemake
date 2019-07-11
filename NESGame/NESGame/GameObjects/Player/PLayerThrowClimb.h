
#pragma once
#include "PlayerState.h"
class PLayerThrowClimb : public PlayerState
{
public:
	PLayerThrowClimb(PlayerData *playerData);
	~PLayerThrowClimb();
	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);
	int check;
	virtual StateName GetState();
protected:
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

