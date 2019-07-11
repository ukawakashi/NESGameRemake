#include "Enemy3Die.h"
#include "Enemy3.h"



Enemy3Die::Enemy3Die()
{
}


Enemy3Die::~Enemy3Die()
{
}


Enemy3Die::Enemy3Die(Enemy3Data *data)
{
	this->mData = data;
}

void Enemy3Die::Update()
{
	//ResourceManager::GetInstance()->playSound("Die", false, 1);
	if (this->mData->enemy->GetCurrentAnimation()->GetCurrentFrame() == 4)
	{
		this->mData->enemy->GetCurrentAnimation()->Reset();
		this->mData->enemy->SetPosition(0, 0);
		this->mData->enemy->Heal = 2;
		this->mData->enemy->mCurrentState = Enemy3State::None;
	}
}
Enemy3State::StateName Enemy3Die::GetState()
{
	return Enemy3State::Die;
}


void Enemy3Die::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

