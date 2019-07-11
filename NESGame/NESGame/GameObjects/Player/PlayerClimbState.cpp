#include "PlayerFallingState.h"
#include "Player.h"
#include "PlayerJumpingState.h"
#include "PlayerClimbState.h"
#include "../../GameDefines/GameDefine.h"
#include "PLayerJumpClimb.h"
#include "PlayerFightHori.h"
#include "PlayerFallClimb.h"

PlayerClimbState::PlayerClimbState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	acceleratorY =100;
	
}


PlayerClimbState::~PlayerClimbState()
{
}

void PlayerClimbState::Update(float dt)
{
	mPlayerData->player->SetVy(acceleratorY);
}

void PlayerClimbState::HandleKeyboard(std::map<int, bool> keys)
{
	mPlayerData->player->GetCurrentAnimation()->SetReverse(false);
	if (keys[VK_RIGHT])
	{
		mPlayerData->player->GetCurrentAnimation()->SetCurrentFrame(6);
		mPlayerData->player->SetReverse(true);


	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->GetCurrentAnimation()->SetCurrentFrame(6);
		mPlayerData->player->SetReverse(false);

	}
	else if (keys[VK_UP] )
	{
		if (mPlayerData->player->GetPosition().y > 415 && mPlayerData->player->GetPosition().x > 4700
			|| mPlayerData->player->GetPosition().y > 400 && mPlayerData->player->GetPosition().x > 2000 && mPlayerData->player->GetPosition().x < 2200
			|| mPlayerData->player->GetPosition().y>230 && mPlayerData->player->GetPosition().x > 1450 && mPlayerData->player->GetPosition().x < 1600
			|| mPlayerData->player->GetPosition().y>170 && mPlayerData->player->GetPosition().x > 2650 && mPlayerData->player->GetPosition().x < 2750)
			acceleratorY = -100;
		else {
			acceleratorY = 0;
			mPlayerData->player->GetCurrentAnimation()->SetCurrentFrame(6);
			return;
		}

	}
	else if (keys[VK_DOWN] /*&& mPlayerData->player->GetPosition().y<500 && mPlayerData->player->GetPosition().x>4700*/)
	{
		acceleratorY = 100;
		mPlayerData->player->GetCurrentAnimation()->SetReverse(true);
		if(mPlayerData->player->GetPosition().y>580 && mPlayerData->player->GetPosition().x>4700)
			this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
	}
	else
	{
		acceleratorY = 0;
		mPlayerData->player->GetCurrentAnimation()->SetCurrentFrame(6);
		checkDown = checkUp = false;
	}
	if (keys[VK_SPACE] && (keys[VK_LEFT] || keys[VK_RIGHT]))
	{
		
		if (1)
		{
			if (!mPlayerData->player->GetReverse())
			{
				this->mPlayerData->player->SetPosition(this->mPlayerData->player->GetPosition().x - 15, this->mPlayerData->player->GetPosition().y);
				//this->mPlayerData->player->SetVx(50);
			}
			else
			{
				this->mPlayerData->player->SetPosition(this->mPlayerData->player->GetPosition().x + 15, this->mPlayerData->player->GetPosition().y);
				//this->mPlayerData->player->SetVx(50);
			}
			//this->mPlayerData->player->SetVy(80);

			this->mPlayerData->player->SetState(new PlayerFallClimb(this->mPlayerData));
			return;
		}
	}
	// Nhảy tại chỗ dây
	if (keys[VK_SPACE] && !keys[VK_LEFT]&& !keys[VK_RIGHT])
	{

		this->mPlayerData->player->SetState(new PLayerJumpClimb(this->mPlayerData));
		return;
	}

	if (keys[VkKeyScanA('z')] )
	{
		this->mPlayerData->player->mAnimationThrowClimb->GetSprite()->SetCenterDraw(D3DXVECTOR2(0.5, 1));
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		this->mPlayerData->player->SetState(new PLayerThrowClimb(this->mPlayerData));
		return;
	}
	if (keys[VkKeyScan('x')])
	{
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		this->mPlayerData->player->SetState(new PlayerFightHori(this->mPlayerData));
		return;
	}

}
PlayerState::StateName PlayerClimbState::GetState()
{
	return PlayerState::Climbing;
}


void PlayerClimbState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}
