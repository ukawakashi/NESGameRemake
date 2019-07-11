#include "Enemy1Die.h"
#include "Enemy1.h"



Enemy1Die::Enemy1Die()
{
}


Enemy1Die::~Enemy1Die()
{
	this->mData = NULL;
	delete this->mData;
}


Enemy1Die::Enemy1Die(Enemy1Data *data)
{
	this->mData = data;
}

void Enemy1Die::Update()
{
	if (this->mData->enemy->GetCurrentAnimation()->GetCurrentFrame() == 4)
	{
		this->mData->enemy->GetCurrentAnimation()->Reset();
		this->mData->enemy->SetPosition(0, 0);
		this->mData->enemy->Heal = 2;
		this->mData->enemy->mCurrentState = Enemy1State::None;
	}
}
Enemy1State::StateName Enemy1Die::GetState()
{
	return Enemy1State::Die;
}


void Enemy1Die::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

