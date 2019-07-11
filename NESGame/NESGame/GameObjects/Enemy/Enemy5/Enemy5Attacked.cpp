#include "Enemy5Attacked.h"
#include "Enemy5.h"



Enemy5Attacked::Enemy5Attacked()
{
}


Enemy5Attacked::~Enemy5Attacked()
{
}





Enemy5Attacked::Enemy5Attacked(Enemy5Data *data)
{
	this->mData = data;

}

void Enemy5Attacked::Update()
{

	if (this->mData->enemy->GetCurrentAnimation()->GetCurrentFrame() ==4 )
	{
		this->mData->enemy->GetCurrentAnimation()->Reset();
		this->mData->enemy->SetState(new Enemy5Running(this->mData));
	}
}
Enemy5State::StateName Enemy5Attacked::GetState()
{
	return Enemy5State::Attacked;;
}


void Enemy5Attacked::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

