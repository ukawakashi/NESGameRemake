#include "Enemy2Running.h"

#include "Enemy2.h"


Enemy2Running::Enemy2Running()
{
}


Enemy2Running::~Enemy2Running()
{
}




Enemy2Running::Enemy2Running(Enemy2Data *data)
{
	this->mData = data;
}

void Enemy2Running::Update()
{
	if (mData->enemy->Reverse)
		mData->enemy->AddPosition(1, 0);
	else
		mData->enemy->AddPosition(-1, 0);
}
Enemy2State::StateName Enemy2Running::GetState()
{
	return Enemy2State::Running;;
}


void Enemy2Running::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

