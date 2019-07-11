#include "PlayerSitFight.h"
#include "PlayerSit.h"


PlayerSitFight::PlayerSitFight(PlayerData *playerData)
{
	this->mPlayerData = playerData;
}


PlayerSitFight::~PlayerSitFight()
{
}








void PlayerSitFight::Update(float dt)
{
	if (this->mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 6)
	{
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		this->mPlayerData->player->SetState(new PlayerSit(this->mPlayerData));
	}
}

void PlayerSitFight::HandleKeyboard(std::map<int, bool> keys)
{

}

void PlayerSitFight::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	//if (impactor->Tag == Entity::LandWood || impactor->Tag == Entity::string) return;

}

PlayerState::StateName PlayerSitFight::GetState()
{
	return PlayerState::SitFight;
}
