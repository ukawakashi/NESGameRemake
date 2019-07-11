#include "PlayerThrowAppleState.h"
#include "Player.h"
#include "PlayerFallingState.h"


PlayerThrowAppleState::PlayerThrowAppleState(PlayerData *playerData)
{
	this->mPlayerData = playerData;

}


PlayerThrowAppleState::~PlayerThrowAppleState()
{
}

void PlayerThrowAppleState::Update(float dt)
{
	int curFrame= mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame();
	if (curFrame == 5)
	{
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		this->mPlayerData->player->SetState(new PlayerStandingState(mPlayerData));
	}
}
void PlayerThrowAppleState::HandleKeyboard(std::map<int, bool> keys)
{
	
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		return;
	}
}

PlayerState::StateName PlayerThrowAppleState::GetState()
{
	 return PlayerState::Throwing;
}

void PlayerThrowAppleState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}
