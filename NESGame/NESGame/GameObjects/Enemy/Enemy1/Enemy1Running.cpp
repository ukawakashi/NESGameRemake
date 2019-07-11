#include "Enemy1Running.h"

#include "Enemy1.h"

Enemy1Running::Enemy1Running()
{
}


Enemy1Running::~Enemy1Running()
{
}


Enemy1Running::Enemy1Running(Enemy1Data *data)
{
	this->mData = data;
}

void Enemy1Running::Update()
{
	if(mData->enemy->Reverse)
		mData->enemy->AddPosition(1, 0);
	else
		mData->enemy->AddPosition(-1, 0);
}
Enemy1State::StateName Enemy1Running::GetState()
{
	return Enemy1State::Running;;
}


void Enemy1Running::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

