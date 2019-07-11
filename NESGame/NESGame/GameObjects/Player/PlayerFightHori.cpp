#include "PlayerFightHori.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerClimbState.h"
#include "PlayerStandHori.h"

PlayerFightHori::PlayerFightHori(PlayerData *playerData)
{
	this->mPlayerData = playerData;
}


PlayerFightHori::~PlayerFightHori()
{
}



void PlayerFightHori::Update(float dt)
{

	if (this->mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 6 && check ==1)
	{
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		this->mPlayerData->player->SetState(new PlayerClimbState(this->mPlayerData));
		return;
	}

	if (this->mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 6 && check == 0)
	{
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		this->mPlayerData->player->SetState(new PlayerStandHori(this->mPlayerData));
		return;
	}
}

void PlayerFightHori::HandleKeyboard(std::map<int, bool> keys)
{
}

PlayerState::StateName PlayerFightHori::GetState()
{
	return PlayerState::AttackClimb;
}


void PlayerFightHori::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	//if (impactor->Tag == Entity::string)
	//{
	//	mPlayerData->player->SetPosition(impactor->GetPosition().x, mPlayerData->player->GetPosition().y);
	//	mPlayerData->player->SetVx(0);
	//	mPlayerData->player->SetVy(0);
	//	mPlayerData->player->SetState(new PlayerClimbState(this->mPlayerData));
	//	return;
	//}
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
	//switch (side)
	//{
	//case Entity::Left:
	//	if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
	//	{
	//		this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
	//		this->mPlayerData->player->SetVx(0);
	//	}
	//	break;

	//case Entity::Right:
	//	if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
	//	{
	//		this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
	//		this->mPlayerData->player->SetVx(0);
	//	}
	//	break;

	//case Entity::Top:
	//	break;

	//case Entity::Bottom:
	//case Entity::BottomRight:
	//case Entity::BottomLeft:
	//	if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
	//	{

	//		this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top)); //Code cho player đứng trên vật thể
	//		RECT r = this->mPlayerData->player->GetBound();
	//	
	//			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
	//		
	//	}
	//	return;

	//default:
	//	break;
	//}
}
