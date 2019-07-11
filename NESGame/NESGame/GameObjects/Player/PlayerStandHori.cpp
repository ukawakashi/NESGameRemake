#include "PlayerStandHori.h"
#include "Player.h"
#include "PlayerFallingState.h"
#include "PlayerSit.h"
#include "PlayerFighting.h"
#include "PlayerFiredState.h"
#include "../../GameDefines/GameDefine.h"
#include "PlayerClimHori.h"
#include "PlayerFightHori.h"

PlayerStandHori::PlayerStandHori(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
} 


PlayerStandHori::~PlayerStandHori()
{
}

void PlayerStandHori::Update(float dt)
{

}

void PlayerStandHori::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_LEFT] || keys[VK_RIGHT])
    {
		if (mPlayerData->player->GetPosition().y < 420 && mPlayerData->player->GetPosition().y > 310 && mPlayerData->player->GetPosition().x > 4000)
			mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x,390);
		else if (mPlayerData->player->GetPosition().y < 290) {
			mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, 165);
		}
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
        this->mPlayerData->player->SetState(new PlayerClimHori(this->mPlayerData));
        return;
    }
	else
	if (keys[VkKeyScan('z')])
	{
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		this->mPlayerData->player->SetState(new PLayerThrowClimb(this->mPlayerData));
		return;
	}
	else
	if (keys[VkKeyScan('x')])
	{
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		this->mPlayerData->player->SetState(new PlayerFightHori(this->mPlayerData));
		return;
	}
	if (keys[VK_SPACE]) {
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		this->mPlayerData->player->SetPosition(this->mPlayerData->player->GetPosition().x, this->mPlayerData->player->GetPosition().y + 20);
		this->mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
		return;
	}
	
}
void PlayerStandHori::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//if(impactor->Tag == Entity::StringHori && side == Entity::Top)
	//{

	//	//this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top) /*+ 85*/);
	//	float a = impactor->GetPosition().y - mPlayerData->player->GetPosition().y;
	//	//mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, impactor->GetPosition().y);//mPlayerData->player->GetPosition().y /*+10*/);
	//	mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, impactor->GetPosition().y - a+1);//mPlayerData->player->GetPosition().y /*+10*/);
	//	this->mPlayerData->player->SetVy(0);
	//	this->mPlayerData->player->SetVx(0);
	//	return;
	//}
	switch (side)
	{
	case Entity::Left:
	{
		//va cham phia ben trai player

		if (impactor->Tag == Entity::Land)
		{
			if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
			{
				this->mPlayerData->player->allowMoveLeft = false;

				//day Player ra phia ben phai de cho player khong bi xuyen qua object
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
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
			}
			return;
		}
		break;
	}

	case Entity::Top:
		//this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
		/*if (mPlayerData->player->GetPosition().y>300)
			mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, 393);
		else
			mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, 170);*/
		//this->mPlayerData->player->SetVy(0);
		break;

	/*case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
	{

		this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top)+70);

		this->mPlayerData->player->SetVy(0);

		break;
	}*/
	}

}
PlayerState::StateName PlayerStandHori::GetState()
{
    return PlayerState::StandHori;
}
