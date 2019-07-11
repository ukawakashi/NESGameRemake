#include "PlayerFighting.h"
#include "Player.h"
#include "PlayerStandingState.h"

PlayerFighting::PlayerFighting(PlayerData *playerData)
{
	this->mPlayerData = playerData;
}


PlayerFighting::~PlayerFighting()
{
}



void PlayerFighting::Update(float dt)
{
	if (this->mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 4)
	{
		this->mPlayerData->player->GetCurrentAnimation()->Reset();
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
	}
	
}

void PlayerFighting::HandleKeyboard(std::map<int, bool> keys)
{
	
}

PlayerState::StateName PlayerFighting::GetState()
{
	return PlayerState::Attack;
}


void PlayerFighting::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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
