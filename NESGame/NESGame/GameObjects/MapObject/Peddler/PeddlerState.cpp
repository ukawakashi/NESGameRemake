#include "PeddlerState.h"



PeddlerState::PeddlerState()
{
}

PeddlerState::PeddlerState(PeddlerData *enemyData)
{
	this->mData = enemyData;
}

PeddlerState::~PeddlerState()
{
}



void PeddlerState::Update()
{

}
void PeddlerState::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}

