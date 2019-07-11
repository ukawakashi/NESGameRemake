#include "Enemy2Fighting.h"

#include "Enemy2.h"


Enemy2Fighting::Enemy2Fighting()
{
}


Enemy2Fighting::~Enemy2Fighting()
{
}




Enemy2Fighting::Enemy2Fighting(Enemy2Data *data)
{
	this->mData = data;
}

void Enemy2Fighting::Update()
{
	//	mData->enemy->AddPosition(1, 0);
}
Enemy2State::StateName Enemy2Fighting::GetState()
{
	return Enemy2State::Attack;
}


void Enemy2Fighting::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

