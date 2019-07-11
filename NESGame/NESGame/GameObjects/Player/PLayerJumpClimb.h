
#pragma once
#include "PlayerState.h"
class PLayerJumpClimb : public PlayerState
{
public:
	PLayerJumpClimb(PlayerData *playerData);
	~PLayerJumpClimb();
	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

