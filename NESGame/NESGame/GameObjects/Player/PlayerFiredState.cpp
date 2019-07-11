#include "PlayerFiredState.h"
#include "PlayerStandingState.h"
#include "PlayerRunningState.h"
#include "PlayerJumpingState.h"
#include "PlayerFighting.h"


PlayerFiredState::~PlayerFiredState()
{
}




PlayerFiredState::PlayerFiredState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	mPlayerData->player->HPCount--;
	mPlayerData->player->isAttacked = true;

}






void PlayerFiredState::Update(float dt)
{

	
	if (this->mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() ==5)
	{
	
		this->mPlayerData->player->isAttacked = false;
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
	}

}

void PlayerFiredState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
		return;
	}
	else if (keys[VK_SPACE])
	{
		this->mPlayerData->player->SetState(new PlayerJumpingState(this->mPlayerData));
		return;
	}
	else if (keys[VK_NUMPAD0])
	{
		this->mPlayerData->player->SetState(new PlayerFighting(this->mPlayerData));
		return;
	}
	
	

}


PlayerState::StateName PlayerFiredState::GetState()
{
	return PlayerState::Fired;
}


void PlayerFiredState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	//if (impactor->Tag == Entity::LandWood || impactor->Tag == Entity::string) return;
	switch (side)
	{
	case Entity::Left:
	{
		//va cham phia ben trai player

		if (impactor->Tag != Entity::LandWood)
		{
			if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
			{
				this->mPlayerData->player->allowMoveLeft = false;

				//day Player ra phia ben phai de cho player khong bi xuyen qua object
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);

				this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			}

			return;
		}
		break;
	}

	case Entity::Right:
	{

		//va cham phia ben phai player
		if (impactor->Tag != Entity::LandWood)
		{

			if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
			{
				this->mPlayerData->player->allowMoveRight = false;
				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			}
			return;
		}
		break;
	}

	case Entity::Top:
		break;

	case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
	{

		this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

		this->mPlayerData->player->SetVy(0);

		break;
	}
	}
}
