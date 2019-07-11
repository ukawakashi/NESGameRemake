#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerFighting.h"
#include "PlayerClimbState.h"
#include "PlayerPushState.h"
#include "../../GameDefines/GameDefine.h"

PlayerRunningState::PlayerRunningState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    
    acceleratorX = 50.0f;

	this->mPlayerData->player->allowMoveLeft = true;
	this->mPlayerData->player->allowMoveRight = true;
}


PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::Update(float dt)
{
	if (mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 0)
		mPlayerData->player->GetCurrentAnimation()->SetCurrentFrame(1) ;
}

void PlayerRunningState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		if (mPlayerData->player->allowMoveRight)
		{
			mPlayerData->player->SetReverse(false);

			//di chuyen sang phai
			if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->AddVx(acceleratorX);

				if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
				{
					this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
				}
			}
			if (this->mPlayerData->player->GetPosition().x <2175 && this->mPlayerData->player->GetPosition().x > 2089 && this->mPlayerData->player->GetPosition().y > 500)
			{
				mPlayerData->player->SetPosition(2165, this->mPlayerData->player->GetPosition().y);
				mPlayerData->player->SetVx(0);
				mPlayerData->player->SetVy(0);
				mPlayerData->player->SetState(new PlayerPushState(this->mPlayerData));
				return;
			}
			if (this->mPlayerData->player->GetPosition().x <2750 && this->mPlayerData->player->GetPosition().x > 2720 && this->mPlayerData->player->GetPosition().y>520)
			{
				mPlayerData->player->SetPosition(2723, this->mPlayerData->player->GetPosition().y);
				mPlayerData->player->SetVx(0);
				mPlayerData->player->SetVy(0);
				mPlayerData->player->SetState(new PlayerPushState(this->mPlayerData));
				return;
			}
			if (this->mPlayerData->player->GetPosition().x <3130 && this->mPlayerData->player->GetPosition().x > 3120 && this->mPlayerData->player->GetPosition().y<250)
			{
				mPlayerData->player->SetPosition(3120, this->mPlayerData->player->GetPosition().y);
				mPlayerData->player->SetVx(0);
				mPlayerData->player->SetVy(0);
				mPlayerData->player->SetState(new PlayerPushState(this->mPlayerData));
				return;
			}
			if (this->mPlayerData->player->GetPosition().x <4740 && this->mPlayerData->player->GetPosition().x > 4725 && this->mPlayerData->player->GetPosition().y>550)
			{
				mPlayerData->player->SetPosition(4735, this->mPlayerData->player->GetPosition().y);
				mPlayerData->player->SetVx(0);
				mPlayerData->player->SetVy(0);
				mPlayerData->player->SetState(new PlayerPushState(this->mPlayerData));
				return;
			}
			if (this->mPlayerData->player->GetPosition().x <3520 && this->mPlayerData->player->GetPosition().x > 3500 && this->mPlayerData->player->GetPosition().y<400)
			{
				mPlayerData->player->SetPosition(3510, this->mPlayerData->player->GetPosition().y);
				mPlayerData->player->SetVx(0);
				mPlayerData->player->SetVy(0);
				mPlayerData->player->SetState(new PlayerPushState(this->mPlayerData));
				return;
			}
			if (this->mPlayerData->player->GetPosition().x <4270 && this->mPlayerData->player->GetPosition().x > 4260 && this->mPlayerData->player->GetPosition().y<400)
			{
				mPlayerData->player->SetPosition(4265, this->mPlayerData->player->GetPosition().y);
				mPlayerData->player->SetVx(0);
				mPlayerData->player->SetVy(0);
				mPlayerData->player->SetState(new PlayerPushState(this->mPlayerData));
				return;
			}

		}
	}
	else if (keys[VK_LEFT])
	{
		if (mPlayerData->player->allowMoveLeft)
		{
			mPlayerData->player->SetReverse(true);

			//di chuyen sang trai
			if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->AddVx(-acceleratorX);

				if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
				{
					this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
				}
			}
			if (this->mPlayerData->player->GetPosition().x > 1470 && this->mPlayerData->player->GetPosition().x < 10 && this->mPlayerData->player->GetPosition().y > 560
			|| this->mPlayerData->player->GetPosition().x > 1470 && this->mPlayerData->player->GetPosition().x < 1500 && this->mPlayerData->player->GetPosition().y < 450)
			{
				mPlayerData->player->SetPosition(1500, this->mPlayerData->player->GetPosition().y);
				mPlayerData->player->SetVx(0);
				mPlayerData->player->SetVy(0);
				mPlayerData->player->SetState(new PlayerPushState(this->mPlayerData));
				return;
			}
			if (this->mPlayerData->player->GetPosition().x > 2280 && this->mPlayerData->player->GetPosition().x < 2285 && this->mPlayerData->player->GetPosition().y>600)
			{
				mPlayerData->player->SetPosition(2280, this->mPlayerData->player->GetPosition().y);
				mPlayerData->player->SetVx(0);
				mPlayerData->player->SetVy(0);
				mPlayerData->player->SetState(new PlayerPushState(this->mPlayerData));
				return;
			}
			if (this->mPlayerData->player->GetPosition().x > 2530 && this->mPlayerData->player->GetPosition().x < 2550 && this->mPlayerData->player->GetPosition().y<250)
			{
				mPlayerData->player->SetPosition(2550, this->mPlayerData->player->GetPosition().y);
				mPlayerData->player->SetVx(0);
				mPlayerData->player->SetVy(0);
				mPlayerData->player->SetState(new PlayerPushState(this->mPlayerData));
				return;
			}
			if (this->mPlayerData->player->GetPosition().x > 2840 && this->mPlayerData->player->GetPosition().x < 2855 && this->mPlayerData->player->GetPosition().y>550)
			{
				mPlayerData->player->SetPosition(2855, this->mPlayerData->player->GetPosition().y);
				mPlayerData->player->SetVx(0);
				mPlayerData->player->SetVy(0);
				mPlayerData->player->SetState(new PlayerPushState(this->mPlayerData));
				return;
			}
			if (this->mPlayerData->player->GetPosition().x > 3085 && this->mPlayerData->player->GetPosition().x < 3095)
			{
				mPlayerData->player->SetPosition(3095, this->mPlayerData->player->GetPosition().y);
				mPlayerData->player->SetVx(0);
				mPlayerData->player->SetVy(0);
				mPlayerData->player->SetState(new PlayerPushState(this->mPlayerData));
				return;
			}
			if (this->mPlayerData->player->GetPosition().x > 3625 && this->mPlayerData->player->GetPosition().x < 3640 && this->mPlayerData->player->GetPosition().y<250)
			{
				mPlayerData->player->SetPosition(3630, this->mPlayerData->player->GetPosition().y);
				mPlayerData->player->SetVx(0);
				mPlayerData->player->SetVy(0);
				mPlayerData->player->SetState(new PlayerPushState(this->mPlayerData));
				return;
			}
			if (this->mPlayerData->player->GetPosition().x > 4380 && this->mPlayerData->player->GetPosition().x < 4390 && this->mPlayerData->player->GetPosition().y<250)
			{
				mPlayerData->player->SetPosition(4385, this->mPlayerData->player->GetPosition().y);
				mPlayerData->player->SetVx(0);
				mPlayerData->player->SetVy(0);
				mPlayerData->player->SetState(new PlayerPushState(this->mPlayerData));
				return;
			}
		}

	}
	else
	{
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		return;
	}
	
}

void PlayerRunningState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{


	if (impactor->Tag == Entity::stair)
	{
		if (mPlayerData->player->GetPosition().x < 2000) {
			D3DXVECTOR2 A = /*impactor->GetPosition();*/D3DXVECTOR2(1144, 625);
			D3DXVECTOR2 B =/* D3DXVECTOR2(A.x + impactor->GetWidth() / 2, A.y - impactor->GetHeight() / 2);*/D3DXVECTOR2(1394, 567);
			//D3DXVECTOR2 A = /*impactor->GetPosition();*/D3DXVECTOR2(1144, 6);
			//D3DXVECTOR2 B =/* D3DXVECTOR2(A.x + impactor->GetWidth() / 2, A.y - impactor->GetHeight() / 2);*/D3DXVECTOR2(1400, 567);
			D3DXVECTOR2 vtcp = D3DXVECTOR2(B.x - A.x, B.y - A.y);
			D3DXVECTOR2 vtpt = D3DXVECTOR2(vtcp.y, -vtcp.x);

			float y = (-vtpt.x*(mPlayerData->player->GetPosition().x - A.x)) / vtpt.y + A.y;
			if (mPlayerData->player->GetPosition().x > 1394)
				mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, mPlayerData->player->GetPosition().y);
			else
				mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, y);
			return;

		}
		else if (mPlayerData->player->GetPosition().x < 4000 && mPlayerData->player->GetPosition().x >3700)
		{
			D3DXVECTOR2 A = D3DXVECTOR2(3800, 485);
			D3DXVECTOR2 B = D3DXVECTOR2(3955, 440);
			//D3DXVECTOR2 A = impactor->GetPosition();
			//D3DXVECTOR2 B = D3DXVECTOR2(A.x + impactor->GetWidth() / 2, A.y - impactor->GetHeight() / 2);
			//D3DXVECTOR2 A = /*impactor->GetPosition();*/D3DXVECTOR2(1144, 6);
			D3DXVECTOR2 vtcp = D3DXVECTOR2(B.x - A.x, B.y - A.y);
			D3DXVECTOR2 vtpt = D3DXVECTOR2(vtcp.y, -vtcp.x);

			float y = (-vtpt.x*(mPlayerData->player->GetPosition().x - A.x)) / vtpt.y + A.y;
			if (mPlayerData->player->GetPosition().x > 3916)
				mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, mPlayerData->player->GetPosition().y);
			else
				mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, y);
			return;
		}
		else
		{
			D3DXVECTOR2 A = D3DXVECTOR2(4380, 649);
			D3DXVECTOR2 B = D3DXVECTOR2(4477, 622);
			D3DXVECTOR2 vtcp = D3DXVECTOR2(B.x - A.x, B.y - A.y);
			D3DXVECTOR2 vtpt = D3DXVECTOR2(vtcp.y, -vtcp.x);

			float y = (-vtpt.x*(mPlayerData->player->GetPosition().x - A.x)) / vtpt.y + A.y;
			if (mPlayerData->player->GetPosition().x > 4477)
				mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, mPlayerData->player->GetPosition().y);
			else		
			mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, y);
			return;
		}
	}

	if (impactor->Tag == Entity::stair2)
	{
		D3DXVECTOR2 A = mPlayerData->player->startStair2 /*- D3DXVECTOR2(0, 7)*/;
		D3DXVECTOR2 B = mPlayerData->player->endStair2;
		D3DXVECTOR2 vtcp = D3DXVECTOR2(B.x - A.x, B.y - A.y);
		D3DXVECTOR2 vtpt = D3DXVECTOR2(vtcp.y, -vtcp.x);

		float y = (-vtpt.x*(mPlayerData->player->GetPosition().x - A.x)) / vtpt.y + A.y;

		mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, y);
		return;
	}

	if (impactor->Tag == Entity::stair1)
	{
		D3DXVECTOR2 A = mPlayerData->player->startStair1 /*- D3DXVECTOR2(10, 0)*/;
		D3DXVECTOR2 B = mPlayerData->player->endStair1 ;//*D3DXVECTOR2(2515, 523);*/
		D3DXVECTOR2 vtcp = D3DXVECTOR2(B.x - A.x, B.y - A.y);
		D3DXVECTOR2 vtpt = D3DXVECTOR2(vtcp.y, -vtcp.x);

		float y = (-vtpt.x*(mPlayerData->player->GetPosition().x - A.x)) / vtpt.y + A.y;

		mPlayerData->player->SetPosition(mPlayerData->player->GetPosition().x, y);
		return;
	}
	if (impactor->Tag == Entity::Rope)
	{
		mPlayerData->player->SetPosition(impactor->GetPosition().x, mPlayerData->player->GetPosition().y);
		mPlayerData->player->SetVx(0);
		mPlayerData->player->SetVy(0);
		mPlayerData->player->SetState(new PlayerClimbState(this->mPlayerData));
		return;
	}
	if (impactor->Tag == Entity::Camel)
	{
		return;
	}

	//if (impactor->Tag == Entity::Wall && (side == Entity::Left|| side == Entity::Right))
	//{
	//	//mPlayerData->player->SetPosition(impactor->GetPosition().x, mPlayerData->player->GetPosition().y);
	//    this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left)+10, 0);
	//	mPlayerData->player->SetVx(0);
	//	mPlayerData->player->SetVy(0);
	//	mPlayerData->player->SetState(new PlayerPushState(this->mPlayerData));
	//	return;
	//}

	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	//if (impactor->Tag == Entity::LandWood || impactor->Tag == Entity::string) return;
	switch (side)
	{
	case Entity::Left:
	{
		//va cham phia ben trai player
	
		if (impactor->Tag != Entity::LandWood )
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

PlayerState::StateName PlayerRunningState::GetState()
{
	return PlayerState::Running;
}
