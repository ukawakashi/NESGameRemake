#include "Enemy2WalkHotcoal.h"
#include "Enemy2.h"



Enemy2WalkHotcoal::Enemy2WalkHotcoal()
{
}


Enemy2WalkHotcoal::~Enemy2WalkHotcoal()
{
}


Enemy2WalkHotcoal::Enemy2WalkHotcoal(Enemy2Data *data)
{
	this->mData = data;
}

void Enemy2WalkHotcoal::Update()
{
	if (mData->enemy->Reverse)
		mData->enemy->AddPosition(1, 0);
	else
		mData->enemy->AddPosition(-1, 0);
	/*if (this->mData->enemy->GetCurrentAnimation()->GetCurrentFrame() == 8)
	{
		this->mData->enemy->GetCurrentAnimation()->Reset();
		this->mData->enemy->mCurrentState = Enemy2State::None;
	}*/


}
Enemy2State::StateName Enemy2WalkHotcoal::GetState()
{
	return Enemy2State::WalkHotcoal;
}


void Enemy2WalkHotcoal::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

