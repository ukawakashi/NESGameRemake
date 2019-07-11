#include "BossState.h"



BossState::BossState()
{
}


BossState::~BossState()
{
}




void BossState::Update()
{

}
void BossState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

BossState::BossState(BossData *enemyData)
{
	this->mData = enemyData;
}