#include "Enemy1Fighting.h"

#include "Enemy1.h"


Enemy1Fighting::Enemy1Fighting()
{
}


Enemy1Fighting::~Enemy1Fighting()
{
}




Enemy1Fighting::Enemy1Fighting(Enemy1Data *data)
{
	this->mData = data;
}

void Enemy1Fighting::Update()
{
	//	mData->enemy->AddPosition(1, 0);
}
Enemy1State::StateName Enemy1Fighting::GetState()
{
	return Enemy1State::Attack;
}


void Enemy1Fighting::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

