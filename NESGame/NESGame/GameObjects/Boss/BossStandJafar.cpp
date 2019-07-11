#include "BossStandJafar.h"
#include "Boss.h"




BossStandJafar::~BossStandJafar()
{
}







BossStandJafar::BossStandJafar(BossData *data)
{
	this->mData = data;
	StartTime = GetTickCount();
}


void BossStandJafar::Update()
{
	if (GetTickCount() - StartTime >= 1500) mData->boss->SetState(new BossJafarAttack(mData));

}
BossStandJafar::StateName BossStandJafar::GetState()
{
	return BossState::StandJafar;
}


void BossStandJafar::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

