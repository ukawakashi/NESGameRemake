#include "PlayerSit.h"
#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerSitFight.h"
#include "PlayerSitThrow.h"

PlayerSit::PlayerSit(PlayerData *playerData)
{
	this->mPlayerData = playerData;
}


PlayerSit::~PlayerSit()
{
}





void PlayerSit::Update(float dt)
{

}

void PlayerSit::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VkKeyScan('x')])
	{
		this->mPlayerData->player->SetState(new PlayerSitFight(this->mPlayerData));
		return;
	} else 
		if (keys[VkKeyScan('z')])
		{
			this->mPlayerData->player->SetState(new PlayerSitThrow(this->mPlayerData));
			return;
		}
	if (keys[VK_DOWN])
	{
		if (this->mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 3) this->mPlayerData->player->GetCurrentAnimation()->SetCurrentFrame(2);
	}
	else
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
	
}

void PlayerSit::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	//if (impactor->Tag == Entity::LandWood || impactor->Tag == Entity::string) return;
	
}

PlayerState::StateName PlayerSit::GetState()
{
	return PlayerState::Sit;
}
