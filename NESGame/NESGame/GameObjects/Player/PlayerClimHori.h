#pragma once

#include "PlayerState.h"

class PlayerClimHori : public PlayerState
{
public:
	PlayerClimHori(PlayerData *playerData);
	~PlayerClimHori();
	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

};




