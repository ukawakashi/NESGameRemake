#include "PlayerPushState.h"
#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerPushState.h"

PlayerPushState::PlayerPushState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
}


PlayerPushState::~PlayerPushState()
{
}





void PlayerPushState::Update(float dt)
{
}

void PlayerPushState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT] /*&& checkRight*/)
	{
		if (mPlayerData->player->allowMoveRight)
		{
			mPlayerData->player->SetReverse(false);
			if (this->mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 0 ) this->mPlayerData->player->GetCurrentAnimation()->SetCurrentFrame(1);
		}
		return;
	}
	else if (keys[VK_LEFT] /*&& checkLeft*/)
	{
		if (mPlayerData->player->allowMoveLeft)
		{
			mPlayerData->player->SetReverse(true);
			if (this->mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 0  ) this->mPlayerData->player->GetCurrentAnimation()->SetCurrentFrame(1);
		}
		return;
	}
	else {
		mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
}

void PlayerPushState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

PlayerState::StateName PlayerPushState::GetState()
{
	return PlayerState::Pushing;
}
