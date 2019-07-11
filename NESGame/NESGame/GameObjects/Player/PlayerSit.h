#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerSit : public PlayerState
{
public:
	PlayerSit(PlayerData *playerData);
	~PlayerSit();
	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	virtual StateName GetState();
};
