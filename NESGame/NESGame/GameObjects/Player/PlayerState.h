#pragma once
#include "PlayerData.h"
#include "../Entity.h"
#include <map>

class PlayerState
{
public:
    enum StateName
    {
		//bmoi them
        Standing,//
		Throwing,//
		Attack,//
		UpAttack,
		LookUp,
		Sit,//

		SitThrow,//
		SitFight,
		RunJump,//
		Jumping,//
		Falling,//
		FallClimb,
		FallAction,
		Landing,
		JumpThrow,//
		JumpFight,
		JumpPole, //Flip
		Running,//
		Stopping,
		Climbing,//
		ClimbingHori,//
		StandHori,
		ThrowClimb,//
		AttackClimb,
		JumpClimb,
		Pushing,
		Fired,//
		Sit2,
		Attacked,
        Die,//
		Revive,//?
		Win,
		FlyingBlack,
		KissPrincess,
		RunFight,
    };

    ~PlayerState();

    virtual void Update(float dt);

    virtual void HandleKeyboard(std::map<int, bool> keys);

	virtual void OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
	static bool isThrowing(PlayerState::StateName state);
    //ham thuan ao bat buoc phai ke thua
    virtual StateName GetState() = 0;
	float GetAcceX();
	float GetAcceY();
	bool GetCheckZ(); bool GetCheckX(); bool GetCheckSpace(); bool GetCheckUp(); bool GetCheckDown();
protected:
    PlayerState(PlayerData *playerData);
    PlayerState();
	float acceleratorY;
	float acceleratorX;

	bool checkZ = true, checkX = true, checkSpace = true, checkUp = true, checkDown = true;
    PlayerData *mPlayerData;
};

