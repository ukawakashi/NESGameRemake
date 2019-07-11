#include "BossSnakeAttack.h"


#include "Boss.h"
BossSnakeAttack::~BossSnakeAttack()
{
}




BossSnakeAttack::BossSnakeAttack(BossData *data)
{
	this->mData = data;

}

void BossSnakeAttack::Update()
{
	if (mData->boss->GetCurrentAnimation()->GetCurrentFrame() ==5)
	{
		if (mData->boss->currentAmmo >= 3) mData->boss->currentAmmo = 0;
		mData->boss->listFireBurn.at(mData->boss->currentAmmo)->isActive = true;
		mData->boss->listFireBurn.at(mData->boss->currentAmmo)->isLeftorRight = !mData->boss->Reverse;
		
		mData->boss->currentAmmo++;
		mData->boss->GetCurrentAnimation()->SetCurrentFrame(6);

	}
	if (mData->boss->GetCurrentAnimation()->GetCurrentFrame() == 10)
	{
		mData->boss->GetCurrentAnimation()->Reset();
		mData->boss->SetState(new BossStandSnake(mData));

	}
}
BossSnakeAttack::StateName BossSnakeAttack::GetState()
{
	return BossState::SnakeAttack;
}


void BossSnakeAttack::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

