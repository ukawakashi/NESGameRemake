#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerJumpingState : public PlayerState
{
public:
    PlayerJumpingState(PlayerData *playerData);
    ~PlayerJumpingState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState();

protected:
    //do bien tien van toc sau moi frame tinh bang pixel / s
 
    bool noPressed;
    bool allowMoveRight, allowMoveLeft;

	bool isLeftOrRightKeyPressed;
};

