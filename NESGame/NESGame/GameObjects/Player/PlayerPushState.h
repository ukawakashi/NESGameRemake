#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerPushState : public PlayerState
{
public:
	PlayerPushState(PlayerData *playerData);
	~PlayerPushState();
	void Update(float dt);
	bool checkLeft = false, checkRight = false;
	void HandleKeyboard(std::map<int, bool> keys);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	virtual StateName GetState();
};
