#include "PlayerLookUp.h"
#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerUpFight.h"

PlayerLookUp::PlayerLookUp(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	mPlayerData->player->allowJump = true;
}


PlayerLookUp::~PlayerLookUp()
{
}





void PlayerLookUp::Update(float dt)
{

}

void PlayerLookUp::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VkKeyScan('z')])
	{

		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		this->mPlayerData->player->SetState(new PlayerThrowAppleState(this->mPlayerData));
		return;
	}
	else
		if (keys[VkKeyScan('x')])
		{
			this->mPlayerData->player->GetCurrentAnimation()->Reset();
			this->mPlayerData->player->SetState(new PlayerUpFight(this->mPlayerData));
			return;
		}
	else if (keys[VK_UP])
	{
		this->mPlayerData->player->GetCurrentAnimation()->SetCurrentFrame(2);
	}
	else
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}

void PlayerLookUp::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	//if (impactor->Tag == Entity::LandWood || impactor->Tag == Entity::string) return;
	
}

PlayerState::StateName PlayerLookUp::GetState()
{
	return PlayerState::LookUp;
}
