#include "Enemy5Die.h"
#include "Enemy5.h"



Enemy5Die::Enemy5Die()
{
}


Enemy5Die::~Enemy5Die()
{
}


Enemy5Die::Enemy5Die(Enemy5Data *data)
{
	this->mData = data;
}

void Enemy5Die::Update()
{
	if (this->mData->enemy->GetCurrentAnimation()->GetCurrentFrame() == 4)
	{
		this->mData->enemy->GetCurrentAnimation()->Reset();
		this->mData->enemy->SetPosition(0, 0);
		this->mData->enemy->Heal = 2;
		this->mData->enemy->mCurrentState = Enemy5State::None;
	}
}
Enemy5State::StateName Enemy5Die::GetState()
{
	return Enemy5State::Die;
}


void Enemy5Die::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

