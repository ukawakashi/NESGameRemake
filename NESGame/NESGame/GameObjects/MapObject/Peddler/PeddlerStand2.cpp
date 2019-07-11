#include "PeddlerStand2.h"

#include "Peddler.h"


PeddlerStand2::PeddlerStand2()
{
}


PeddlerStand2::~PeddlerStand2()
{
}




PeddlerStand2::PeddlerStand2(PeddlerData *data)
{
	this->mData = data;
}

void PeddlerStand2::Update()
{
	//	mData->enemy->AddPosition(1, 0);
}
PeddlerState::StateName PeddlerStand2::GetState()
{
	return PeddlerState::Stand2;
}


void PeddlerStand2::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

