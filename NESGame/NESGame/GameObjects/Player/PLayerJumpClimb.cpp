#include "PLayerJumpClimb.h"


#include "Player.h"
#include "PlayerClimbState.h"
#include "PlayerFallClimb.h"
#include "PlayerStandHori.h"


PLayerJumpClimb::PLayerJumpClimb(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	this->mPlayerData->player->SetVy(-500);

	acceleratorY = 40.0f;
	acceleratorX = 0.0f;



	this->mPlayerData->player->AddVy(100);
}


PLayerJumpClimb::~PLayerJumpClimb()
{
}

void PLayerJumpClimb::Update(float dt)
{
	
	/*int curFrame = mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame();
	if (curFrame == 4)
	{
		this->mPlayerData->player->GetCurrentAnimation()->Reset();

		this->mPlayerData->player->SetState(new PlayerFallingState(mPlayerData));
	}*/
	this->mPlayerData->player->AddVy(acceleratorY);
	/*if(mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 0)
	mPlayerData->player->GetCurrentAnimation()->SetCurrentFrame(1);*/
	/*if (mPlayerData->player->GetVy() >= 0)
	{
	mPlayerData->player->GetCurrentAnimation()->Reset();
	mPlayerData->player->SetState(new PlayerFallingState(this->mPlayerData));
	return;
	}*/
	//if (mPlayerData->player->GetVy() > 150)
	//{
	//	mPlayerData->player->SetVy(0);
	//	/*this->mPlayerData->player->SetState(new PlayerFallClimb(this->mPlayerData));*/
	//}
}
void PLayerJumpClimb::HandleKeyboard(std::map<int, bool> keys)
{


}

PlayerState::StateName PLayerJumpClimb::GetState()
{
	return PlayerState::JumpClimb;
}

void PLayerJumpClimb::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (mPlayerData->player->GetPosition().y > 445 && mPlayerData->player->GetPosition().x > 4700
		|| mPlayerData->player->GetPosition().y > 400 && mPlayerData->player->GetPosition().x > 2000 && mPlayerData->player->GetPosition().x < 2200
		|| mPlayerData->player->GetPosition().y>230 && mPlayerData->player->GetPosition().x > 1450 && mPlayerData->player->GetPosition().x < 1600
		|| mPlayerData->player->GetPosition().y>90 && mPlayerData->player->GetPosition().x > 2650 && mPlayerData->player->GetPosition().x < 2750)
	{

		if (impactor->Tag == Entity::Rope)
		{
			mPlayerData->player->SetPosition(impactor->GetPosition().x, mPlayerData->player->GetPosition().y);
			if (this->mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 2)
			{
				mPlayerData->player->SetVx(0);
				mPlayerData->player->SetVy(0);
				mPlayerData->player->SetState(new PlayerClimbState(this->mPlayerData));
			}
			//mPlayerData->player->allowJump = true;


			return;
		}
	}
	if (mPlayerData->player->GetPosition().y < 445 && mPlayerData->player->GetPosition().y > 290 && mPlayerData->player->GetPosition().x > 4000 
		|| mPlayerData->player->GetPosition().y < 290 ) {
		if (impactor->Tag == Entity::StringHori && side == Entity::Top /*&& (mPlayerData->player->GetPosition().y < 440)*/)
		{
			//mPlayerData->player->SetReverse(mPlayerData->player->GetReverse());
			//mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, impactor->GetPosition().y);//mPlayerData->player->GetPosition().y /*+10*/);
			//mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, impactor->GetPosition().y - a+10);//mPlayerData->player->GetPosition().y /*+10*/);
			if (mPlayerData->player->GetPosition().y < 420 && mPlayerData->player->GetPosition().y > 310 && mPlayerData->player->GetPosition().x > 4000)
				mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x,395);
			else if (mPlayerData->player->GetPosition().y < 290)
				mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, 170);
			mPlayerData->player->SetVy(0);
			mPlayerData->player->SetState(new PlayerStandHori(this->mPlayerData));
			return;
		}
	}
	switch (side)
	{
	case Entity::Left:
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
		/*if (mPlayerData->player->GetPosition().y < 440) {
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

			this->mPlayerData->player->SetVy(0);
		}*/

		break;
	}

	/*case Entity::BottomRight: case Entity::BottomLeft: case Entity::Bottom:
	{
		this->mPlayerData->player->AddPosition(0, (data.RegionCollision.bottom - data.RegionCollision.top));

		this->mPlayerData->player->SetVy(0);

		break;
	}*/

	default:
		break;
	}
}