#include "PlayerJumpPole.h"

#include "PlayerJumpingState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpThrow.h"
#include "PlayerClimbState.h"
#include "PlayerStandHori.h"
#include "../../GameDefines/GameDefine.h"


PlayerJumpPole::~PlayerJumpPole()
{
}




PlayerJumpPole::PlayerJumpPole(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);

	acceleratorY = 30.0f;
	acceleratorX = 0.0f;

	this->mPlayerData->player->AddVy(-180);

}



void PlayerJumpPole::Update(float dt)
{
	this->mPlayerData->player->AddVy(acceleratorY);

	if (mPlayerData->player->GetVy() >= 0)
	{
		//acceleratorY *= -1;
		return;
	}

}

void PlayerJumpPole::HandleKeyboard(std::map<int, bool> keys)
{

	if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);

		//di chuyen sang phai
		if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			//this->mPlayerData->player->AddVx(acceleratorX);
			this->mPlayerData->player->SetVx(200);
			if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}

	
	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);

		//di chuyen sang trai
		if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			//this->mPlayerData->player->AddVx(-acceleratorX);
			this->mPlayerData->player->SetVx(-200);
			if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}

	
	}


}

PlayerJumpPole::StateName PlayerJumpPole::GetState()
{
	return PlayerState::JumpPole;
}
void PlayerJumpPole::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::flagPole )
	{
		
		switch (side)
		{
		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
			if (impactor->Tag == Entity::StringHori)
			{
				return;
			}
			if (mPlayerData->player->GetVy() >= 0)
				this->mPlayerData->player->SetState(new PlayerJumpPole(this->mPlayerData));
			break;
		/*case Entity::Left:
		{
			if (impactor->Tag != Entity::LandWood)
			{
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				this->mPlayerData->player->SetVx(0);
			}
			break;
		}

		case Entity::Right:
		{
			if (impactor->Tag != Entity::LandWood)
			{
				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				this->mPlayerData->player->SetVx(0);
			}
			break;
		}

		case Entity::TopRight: case Entity::TopLeft: case Entity::Top:
		{
			if (impactor->Tag == Entity::flagPole)
			{

				mPlayerData->player->SetState(new PlayerJumpPole(this->mPlayerData));
				return;
			}
			break;
		}*/
		}
		return;
	}
	if (impactor->Tag == Entity::AppleObject)
		return;

	this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
	this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
	
	switch (side)
	{
	case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
		if (impactor->Tag == Entity::StringHori)
		{
			return;
		}
	}
	//if (impactor->Tag == Entity::StringHori /*&& (side == Entity::Top || side == Entity::TopRight || side == Entity::TopLeft || side == Entity::Left || side == Entity::Right)*/)
	//{
	//	mPlayerData->player->SetReverse(mPlayerData->player->GetReverse());
	//	//mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x,impactor->GetPosition().y);
	//	mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, mPlayerData->player->GetPosition().y + 35);

	//	mPlayerData->player->SetVy(0);
	//	mPlayerData->player->SetState(new PlayerStandHori(this->mPlayerData));
	//	return;
	//}
	
}