#pragma once
#include "Player.h"
#include "PlayerState.h"
class PlayerJumpPole : public PlayerState
{
public:
	PlayerJumpPole(PlayerData *playerData);
	~PlayerJumpPole();
	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

	virtual StateName GetState();

};



