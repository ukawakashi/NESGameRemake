#include "Enemy1Attacked.h"
#include "Enemy1.h"



Enemy1Attacked::Enemy1Attacked()
{
}


Enemy1Attacked::~Enemy1Attacked()
{
}





Enemy1Attacked::Enemy1Attacked(Enemy1Data *data)
{
	this->mData = data;
	
}

void Enemy1Attacked::Update()
{

	if (this->mData->enemy->GetCurrentAnimation()->GetCurrentFrame() == 8)
	{
		this->mData->enemy->Heal--;
		this->mData->enemy->GetCurrentAnimation()->Reset();
		this->mData->enemy->SetState(new Enemy1Running(this->mData));
	}
}
Enemy1State::StateName Enemy1Attacked::GetState()
{
	return Enemy1State::Attacked;
}


void Enemy1Attacked::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

