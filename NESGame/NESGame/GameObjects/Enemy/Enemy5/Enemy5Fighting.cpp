#include "Enemy5Fighting.h"

#include "Enemy5.h"


Enemy5Fighting::Enemy5Fighting()
{
}


Enemy5Fighting::~Enemy5Fighting()
{
}




Enemy5Fighting::Enemy5Fighting(Enemy5Data *data)
{
	this->mData = data;
}

void Enemy5Fighting::Update()
{
	//	mData->enemy->AddPosition(1, 0);
}
Enemy5State::StateName Enemy5Fighting::GetState()
{
	return Enemy5State::Attack;
}


void Enemy5Fighting::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::stair)
	{

		D3DXVECTOR2 A = D3DXVECTOR2(3800, 485);
		D3DXVECTOR2 B = D3DXVECTOR2(3955, 440);
		//D3DXVECTOR2 A = impactor->GetPosition();
		//D3DXVECTOR2 B = D3DXVECTOR2(A.x + impactor->GetWidth() / 2, A.y - impactor->GetHeight() / 2);
		//D3DXVECTOR2 A = /*impactor->GetPosition();*/D3DXVECTOR2(1144, 6);
		D3DXVECTOR2 vtcp = D3DXVECTOR2(B.x - A.x, B.y - A.y);
		D3DXVECTOR2 vtpt = D3DXVECTOR2(vtcp.y, -vtcp.x);

		float y = (-vtpt.x*(mData->enemy->GetPosition().x - A.x)) / vtpt.y + A.y;
		mData->enemy->SetPosition(mData->enemy->GetPosition().x, y);
		return;
	}
	return;
}

