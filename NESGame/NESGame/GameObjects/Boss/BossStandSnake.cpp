#include "BossStandSnake.h"

#include "Boss.h"

BossStandSnake::BossStandSnake(BossData *data)
{
	this->mData = data;
	StartTime = GetTickCount();
}


BossStandSnake::~BossStandSnake()
{
}



void BossStandSnake::Update()
{
	if (GetTickCount() - StartTime >= 800) mData->boss->SetState(new BossSnakeAttack(mData));
	

}
BossState::StateName BossStandSnake::GetState()
{
	return BossState::StandSnake;
}


void BossStandSnake::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

