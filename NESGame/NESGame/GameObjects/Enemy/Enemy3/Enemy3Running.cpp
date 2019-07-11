#include "Enemy3Running.h"

#include "Enemy3.h"


Enemy3Running::Enemy3Running()
{
}


Enemy3Running::~Enemy3Running()
{
}




Enemy3Running::Enemy3Running(Enemy3Data *data)
{
	this->mData = data;
}

void Enemy3Running::Update()
{
	D3DXVECTOR2 A = D3DXVECTOR2(3800, 485);
	D3DXVECTOR2 B = D3DXVECTOR2(3955, 440);
	//D3DXVECTOR2 A = impactor->GetPosition();
	//D3DXVECTOR2 B = D3DXVECTOR2(A.x + impactor->GetWidth() / 2, A.y - impactor->GetHeight() / 2);
	//D3DXVECTOR2 A = /*impactor->GetPosition();*/D3DXVECTOR2(1144, 6);
	D3DXVECTOR2 vtcp = D3DXVECTOR2(B.x - A.x, B.y - A.y);
	D3DXVECTOR2 vtpt = D3DXVECTOR2(vtcp.y, -vtcp.x);

	float y = (-vtpt.x*(mData->enemy->GetPosition().x - A.x)) / vtpt.y + A.y;
	
	if (mData->enemy->Reverse) {
		mData->enemy->AddPosition(1, 0);
	}
	else {
		mData->enemy->AddPosition(-1, 0);
	}
	if (check == true && mData->enemy->GetPosition().x >3800 && mData->enemy->GetPosition().x <3955)
		mData->enemy->SetPosition(mData->enemy->GetPosition().x, y);
}
Enemy3State::StateName Enemy3Running::GetState()
{
	return Enemy3State::Running;;
}


void Enemy3Running::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	if (impactor->Tag == Entity::stair)
	{
		check = true;
		return;
	}
	else {
		check = false;
		return;
	}
	return;
}

