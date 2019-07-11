#pragma once
#include "PlayerState.h"
class PlayerFighting : public PlayerState
{
public:
	PlayerFighting(PlayerData *playerData);
	~PlayerFighting();
	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};