#include "Enemy3Attacked.h"
#include "Enemy3.h"



Enemy3Attacked::Enemy3Attacked()
{
}


Enemy3Attacked::~Enemy3Attacked()
{
}





Enemy3Attacked::Enemy3Attacked(Enemy3Data *data)
{
	this->mData = data;

}

void Enemy3Attacked::Update()
{
	if (this->mData->enemy->GetCurrentAnimation()->GetCurrentFrame() == 0)
	{
		this->mData->enemy->Heal--;
	}

	if (this->mData->enemy->GetCurrentAnimation()->GetCurrentFrame() == 9)
	{
		
		this->mData->enemy->GetCurrentAnimation()->Reset();
		this->mData->enemy->SetState(new Enemy3Running(this->mData));
	}
}
Enemy3State::StateName Enemy3Attacked::GetState()
{
	return Enemy3State::Attacked;;
}


void Enemy3Attacked::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

