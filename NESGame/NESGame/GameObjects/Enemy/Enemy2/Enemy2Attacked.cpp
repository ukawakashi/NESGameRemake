#include "Enemy2Attacked.h"
#include "Enemy2.h"



Enemy2Attacked::Enemy2Attacked()
{
}


Enemy2Attacked::~Enemy2Attacked()
{
}





Enemy2Attacked::Enemy2Attacked(Enemy2Data *data)
{
	this->mData = data;

}

void Enemy2Attacked::Update()
{

	if (this->mData->enemy->GetCurrentAnimation()->GetCurrentFrame() == 5)
	{
		this->mData->enemy->Heal--;
		this->mData->enemy->GetCurrentAnimation()->Reset();
		this->mData->enemy->SetState(new Enemy2Running(this->mData));
	}


	
}
Enemy2State::StateName Enemy2Attacked::GetState()
{
	return Enemy2State::Attacked;;
}


void Enemy2Attacked::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

