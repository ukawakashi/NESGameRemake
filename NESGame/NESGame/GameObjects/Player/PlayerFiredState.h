#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerFiredState : public PlayerState
{
public:
	PlayerFiredState(PlayerData *playerData);
	~PlayerFiredState();
	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	virtual StateName GetState();
};

