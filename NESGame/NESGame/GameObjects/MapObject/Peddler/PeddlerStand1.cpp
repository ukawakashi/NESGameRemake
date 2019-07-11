#include "PeddlerStand1.h"
#include "Peddler.h"



PeddlerStand1::PeddlerStand1()
{
}


PeddlerStand1::~PeddlerStand1()
{
}


PeddlerStand1::PeddlerStand1(PeddlerData *data)
{
	this->mData = data;
}

void PeddlerStand1::Update()
{
	if (this->mData->enemy->GetCurrentAnimation()->GetCurrentFrame() == 19)
	{
		this->mData->enemy->GetCurrentAnimation()->Reset();
		//this->mData->enemy->SetPosition(0, 0);
		//this->mData->enemy->Heal = 2;
		this->mData->enemy->SetState(new PeddlerSell(this->mData));
	}
}
PeddlerState::StateName PeddlerStand1::GetState()
{
	return PeddlerState::Stand1;
}


void PeddlerStand1::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

