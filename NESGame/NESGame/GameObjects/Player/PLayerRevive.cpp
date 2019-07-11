#include "PLayerRevive.h"
#include "Player.h"



PLayerRevive::PLayerRevive(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVx(0);
	this->mPlayerData->player->SetVy(0);
}


PLayerRevive::~PLayerRevive()
{
}
void PLayerRevive::Update(float dt)
{
	if (this->mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 13)
	{
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		this->mPlayerData->player->PlayerLiveCount--;
		this->mPlayerData->player->SetState(new PlayerStandingState(mPlayerData));
	}
}


void PLayerRevive::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	//if (impactor->Tag == Entity::LandWood || impactor->Tag == Entity::string) return;

}

PlayerState::StateName PLayerRevive::GetState()
{
	return PlayerState::Revive;
}
