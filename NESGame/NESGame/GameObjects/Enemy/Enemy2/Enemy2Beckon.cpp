#include "Enemy2Beckon.h"

#include "Enemy2.h"


Enemy2Beckon::Enemy2Beckon()
{
}


Enemy2Beckon::~Enemy2Beckon()
{
}




Enemy2Beckon::Enemy2Beckon(Enemy2Data *data)
{
	this->mData = data;
}

void Enemy2Beckon::Update()
{
	if (mData->enemy->GetCurrentAnimation()->GetCurrentFrame() < 2)
		mData->enemy->GetCurrentAnimation()->SetCurrentFrame(2);
}
Enemy2State::StateName Enemy2Beckon::GetState()
{
	return Enemy2State::Benkon;
}


void Enemy2Beckon::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

