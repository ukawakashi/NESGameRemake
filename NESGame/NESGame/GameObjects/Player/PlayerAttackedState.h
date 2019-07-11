#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerAttackedState : public PlayerState
{
public:
	PlayerAttackedState(PlayerData *playerData);
	~PlayerAttackedState();
	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	virtual StateName GetState();
};

