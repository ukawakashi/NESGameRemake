#include "Enemy2Die.h"
#include "Enemy2.h"



Enemy2Die::Enemy2Die()
{
}


Enemy2Die::~Enemy2Die()
{
}


Enemy2Die::Enemy2Die(Enemy2Data *data)
{
	this->mData = data;
}

void Enemy2Die::Update()
{
	if (this->mData->enemy->GetCurrentAnimation()->GetCurrentFrame() == 4)
	{
		this->mData->enemy->GetCurrentAnimation()->Reset();


		this->mData->enemy->SetPosition(0, 0);
		this->mData->enemy->Heal = 2;
		this->mData->enemy->mCurrentState = Enemy2State::None;
	}


}
Enemy2State::StateName Enemy2Die::GetState()
{
	return Enemy2State::Die;
}


void Enemy2Die::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

