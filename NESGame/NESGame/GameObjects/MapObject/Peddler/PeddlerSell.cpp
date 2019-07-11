#include "PeddlerSell.h"
#include "Peddler.h"



PeddlerSell::PeddlerSell()
{
}


PeddlerSell::~PeddlerSell()
{
}





PeddlerSell::PeddlerSell(PeddlerData *data)
{
	this->mData = data;

}

void PeddlerSell::Update()
{
	if (this->mData->enemy->GetCurrentAnimation()->GetCurrentFrame() == 25 )
	{
		return;
	}
}
PeddlerState::StateName PeddlerSell::GetState()
{
	return PeddlerState::Sell;
}


void PeddlerSell::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

