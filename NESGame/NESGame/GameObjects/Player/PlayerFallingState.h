#pragma once
#include "PlayerState.h"


class PlayerFallingState : public PlayerState
{
public:
    PlayerFallingState(PlayerData *playerData);
    ~PlayerFallingState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();
	void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

protected:
    //do bien tien van toc sau moi frame tinh bang pixel / s
   

    //neu nhu van toc ban dau = khong thi se khong cho giam toc do
    bool allowMoveX;

    bool isLeftOrRightKeyPressed;
};

