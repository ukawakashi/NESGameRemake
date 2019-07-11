#include "PlayerJumpFight.h"
#include "PlayerFallAction.h"


PlayerJumpFight::PlayerJumpFight(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	acceleratorY = 20.0f;
}


PlayerJumpFight::~PlayerJumpFight()
{
}

void PlayerJumpFight::Update(float dt)
{
	this->mPlayerData->player->AddVy(acceleratorY);
	if ( mPlayerData->player->GetCurrentAnimation()->GetCurrentFrame() == 6)
	{
		mPlayerData->player->GetCurrentAnimation()->Reset();
		mPlayerData->player->SetState(new PlayerFallAction(this->mPlayerData));
		return;
	}
}

void PlayerJumpFight::HandleKeyboard(std::map<int, bool> keys)
{


}

void PlayerJumpFight::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//lay phia va cham so voi player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
	//if (impactor->Tag == Entity::LandWood || impactor->Tag == Entity::string) return;
	switch (side)
	{
	case Entity::Left:
		if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
		{
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			this->mPlayerData->player->SetVx(0);
		}
		break;

	case Entity::Right:
		if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
		{
			this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
			this->mPlayerData->player->SetVx(0);
		}
		break;

	case Entity::Top:
		break;

	case Entity::Bottom:
	case Entity::BottomRight:
	case Entity::BottomLeft:

		//if (data.RegionCollision.right - data.RegionCollision.left >= 16.0f)
		//{

			this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top)); //Code cho player đứng trên vật thể
			RECT r = this->mPlayerData->player->GetBound();
			
			mPlayerData->player->GetCurrentAnimation()->Reset();
			this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
		
		//}
		return;

	default:
		break;
	}

}

PlayerState::StateName PlayerJumpFight::GetState()
{
	return PlayerState::JumpFight;
}
