#include "PLayerThrowClimb.h"


#include "Player.h"
#include "PlayerClimbState.h"
#include "PlayerStandHori.h"
PLayerThrowClimb::PLayerThrowClimb(PlayerData *playerData)
{
	this->mPlayerData = playerData;

	
}


PLayerThrowClimb::~PLayerThrowClimb()
{
}

void PLayerThrowClimb::Update(float dt)
{
	int curFrame = mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame();
	if (curFrame == 5 && check == 1)
	{
		this->mPlayerData->player->GetCurrentAnimation()->Reset();

		this->mPlayerData->player->SetState(new PlayerClimbState(mPlayerData));
		return;
	}
	if (curFrame == 5 && check == 0)
	{
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		this->mPlayerData->player->SetState(new PlayerStandHori(mPlayerData));
		return;
	}
}
void PLayerThrowClimb::HandleKeyboard(std::map<int, bool> keys)
{
}

PlayerState::StateName PLayerThrowClimb::GetState()
{
	return PlayerState::ThrowClimb;
}

void PLayerThrowClimb::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::Rope)
	{
		check = 1;
		return;
	}
	if (impactor->Tag == Entity::StringHori)
	{
		check = 0;
		return;
	}
}
