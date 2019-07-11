#pragma once
#include "PlayerState.h"

class PlayerStandHori : public PlayerState
{
public:
    PlayerStandHori(PlayerData *playerData);
    ~PlayerStandHori();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

protected:
};

