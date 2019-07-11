#pragma once
#include "PlayerState.h"
class PlayerFightHori : public PlayerState
{
public:
	PlayerFightHori(PlayerData *playerData);
	~PlayerFightHori();
	void Update(float dt);

	void HandleKeyboard(std::map<int, bool> keys);

	virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	int check = 1;
};