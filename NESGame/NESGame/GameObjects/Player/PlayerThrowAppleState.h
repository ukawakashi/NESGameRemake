#pragma once
#include "PlayerState.h"
class PlayerThrowAppleState : public PlayerState
{
public:
	PlayerThrowAppleState(PlayerData *playerData);
	~PlayerThrowAppleState();
	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
protected:
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
};

