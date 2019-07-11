#include "PlayerState.h"


PlayerState::PlayerState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
}

PlayerState::PlayerState()
{

}

PlayerState::~PlayerState()
{
}

void PlayerState::Update(float dt)
{

}

void PlayerState::HandleKeyboard(std::map<int, bool> keys)
{

}
float PlayerState::GetAcceX()
{
	return acceleratorX;
}

float PlayerState::GetAcceY()
{
	return acceleratorY;
}
bool PlayerState::GetCheckZ()
{
	return checkZ;
}
bool PlayerState::GetCheckX()
{
	return checkX;
}
bool PlayerState::GetCheckSpace()
{
	return checkSpace;
}
bool PlayerState::GetCheckUp()
{
	return checkUp;
}
bool PlayerState::GetCheckDown()
{
	return checkDown;
}
void PlayerState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}
bool PlayerState::isThrowing(PlayerState::StateName state)
{
	if (state == PlayerState::Throwing || state == PlayerState::ThrowClimb || state == PlayerState::SitThrow || state == PlayerState::JumpThrow)
		return true;
	return false;
}