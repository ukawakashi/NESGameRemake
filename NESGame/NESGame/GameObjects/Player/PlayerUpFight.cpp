#include "PlayerUpFight.h"
#include "PlayerSit.h"
#include "PlayerLookUp.h"
#include "PlayerStandingState.h"

PlayerUpFight::PlayerUpFight(PlayerData *playerData)
{
	this->mPlayerData = playerData;
}


PlayerUpFight::~PlayerUpFight()
{
}








void PlayerUpFight::Update(float dt)
{
	if (this->mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 19)
	{
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
	}
}

void PlayerUpFight::HandleKeyboard(std::map<int, bool> keys)
{
}

void PlayerUpFight::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	//if (impactor->Tag == Entity::LandWood || impactor->Tag == Entity::string) return;

}

PlayerState::StateName PlayerUpFight::GetState()
{
	return PlayerState::UpAttack;
}
