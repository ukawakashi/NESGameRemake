
#include "Player.h"
#include "../../GameDefines/GameDefine.h"
#include "PlayerClimbState.h"
#include "PlayerJumpingState.h"
#include "PlayerFallClimb.h"
#include "PlayerStandHori.h"

PlayerFallClimb::PlayerFallClimb(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    /*acceleratorY =5.0f;
    acceleratorX = 3.0f;

    if (this->mPlayerData->player->GetVx() == 0)
    {
        allowMoveX = false;
    }
    else
    {
        allowMoveX = true;
    }*/
	this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);

	acceleratorY = 15.0f;



	this->mPlayerData->player->AddVy(100);
}


PlayerFallClimb::~PlayerFallClimb()
{
}

void PlayerFallClimb::Update(float dt)
{
    this->mPlayerData->player->AddVy(acceleratorY);
	//if (mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 3) mPlayerData->player->GetCurrentAnimation()->SetCurrentFrame(2);
    if (mPlayerData->player->GetVy() > /*Define::PLAYER_MAX_JUMP_VELOCITY*/800)
    {
        mPlayerData->player->SetVy(/*Define::PLAYER_MAX_JUMP_VELOCITY*/800);
    }
}

void PlayerFallClimb::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
    {
        mPlayerData->player->SetReverse(false);

        isLeftOrRightKeyPressed = true;
        //di chuyen sang phai
        if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
        {
          //  this->mPlayerData->player->AddVx(acceleratorX);
			this->mPlayerData->player->SetVx(80);
            if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }
    }
    else if (keys[VK_LEFT])
    {
        mPlayerData->player->SetReverse(true);

        isLeftOrRightKeyPressed = true;
        //di chuyen sang trai
        if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
        {
          //  this->mPlayerData->player->AddVx(-acceleratorX);
			this->mPlayerData->player->SetVx(-80);
            if (this->mPlayerData->player->GetVx() <= -Define::PLAYER_MAX_RUNNING_SPEED)
            {
                this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }
    }
    else
    {
        isLeftOrRightKeyPressed = false;    
    }
}

PlayerState::StateName PlayerFallClimb::GetState()
{
    return PlayerState::FallClimb;
}


void PlayerFallClimb::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	//if (mPlayerData->player->GetPosition().x > 4710 && mPlayerData->player->GetPosition().x < 4720) {
		if (impactor->Tag == Entity::Rope &&  mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() > 4)
		{
			mPlayerData->player->SetPosition(impactor->GetPosition().x, mPlayerData->player->GetPosition().y);
			mPlayerData->player->SetVx(0);
			mPlayerData->player->SetVy(0);
			mPlayerData->player->SetState(new PlayerClimbState(this->mPlayerData));
			return;
		}
	//}

	//if (mPlayerData->player->GetPosition().y < 420 && mPlayerData->player->GetPosition().y > 310 && mPlayerData->player->GetPosition().x > 4000 || mPlayerData->player->GetPosition().y < 290)
	//{
		if (impactor->Tag == Entity::StringHori && side == Entity::Top /*&& (mPlayerData->player->GetPosition().y < 440)*/)
		{
			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			//mPlayerData->player->SetReverse(mPlayerData->player->GetReverse());
			//mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, impactor->GetPosition().y);//mPlayerData->player->GetPosition().y /*+10*/);
			if (mPlayerData->player->GetPosition().y < 420 && mPlayerData->player->GetPosition().y > 310 && mPlayerData->player->GetPosition().x > 4000)
				mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, /*impactor->GetPosition().y - a +10*/395);//mPlayerData->player->GetPosition().y /*+10*/);
			else if (mPlayerData->player->GetPosition().y < 290) {
				mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, 170);
			}
			mPlayerData->player->SetVy(0);
			mPlayerData->player->SetState(new PlayerStandHori(this->mPlayerData));
			return;
		}
	//}

	if (impactor->Tag == Entity::AppleObject)
		return;


	switch (side)
	{
	case Entity::Left:
		if (impactor->Tag == Entity::Wall) {
			if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
			{
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				this->mPlayerData->player->SetVx(0);
			}
		}
		break;

	case Entity::Right:
		if (impactor->Tag == Entity::Wall) {
			if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
			{
				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				this->mPlayerData->player->SetVx(0);
			}
			break;
		}

	case Entity::Top:
	{
		/*this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

		this->mPlayerData->player->SetVy(0);*/

		break;
	}

	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:

		/*if (impactor->Tag == Entity::flagPole)
		{

			mPlayerData->player->SetState(new PlayerBung(this->mPlayerData));
			return;
		}
		if (impactor->Tag == Entity::Camel)
		{
			this->mPlayerData->player->SetState(new PlayerJumpingState(this->mPlayerData));
			return;
		}*/
		if (data.RegionCollision.right - data.RegionCollision.left >= 16.0f)
		{

			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top)); //Code cho player đứng trên vật thể
			RECT r = this->mPlayerData->player->GetBound();
			if (isLeftOrRightKeyPressed)
			{
				mPlayerData->player->GetCurrentAnimation()->Reset();
				this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
			}
			else
			{
				mPlayerData->player->GetCurrentAnimation()->Reset();
				this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			}
		}
		return;

	default:
		break;
	}
}


