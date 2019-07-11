#include "PlayerSitThrow.h"
#include "PlayerSit.h"


PlayerSitThrow::PlayerSitThrow(PlayerData *playerData)
{
	this->mPlayerData = playerData;
}


PlayerSitThrow::~PlayerSitThrow()
{
}










void PlayerSitThrow::Update(float dt)
{
	if (this->mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 4)
	{
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		this->mPlayerData->player->SetState(new PlayerSit(this->mPlayerData));
	}
}

void PlayerSitThrow::HandleKeyboard(std::map<int, bool> keys)
{

}

void PlayerSitThrow::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	//if (impactor->Tag == Entity::LandWood || impactor->Tag == Entity::string) return;

}

PlayerState::StateName PlayerSitThrow::GetState()
{
	return PlayerState::SitThrow;
}
