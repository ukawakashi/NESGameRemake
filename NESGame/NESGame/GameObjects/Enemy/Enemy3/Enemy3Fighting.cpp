#include "Enemy3Fighting.h"

#include "Enemy3.h"


Enemy3Fighting::Enemy3Fighting()
{
}


Enemy3Fighting::~Enemy3Fighting()
{
}




Enemy3Fighting::Enemy3Fighting(Enemy3Data *data)
{
	this->mData = data;
}

void Enemy3Fighting::Update()
{
	//	mData->enemy->AddPosition(1, 0);
}
Enemy3State::StateName Enemy3Fighting::GetState()
{
	return Enemy3State::Attack;
}


void Enemy3Fighting::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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

