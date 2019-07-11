#include "BossJafarAttack.h"
#include "Boss.h"
#include "BossStandJafar.h"

BossJafarAttack::~BossJafarAttack()
{
}



int StartTimeJafarAttack, CurTimeJafar;
BossJafarAttack::BossJafarAttack(BossData *data)
{
	this->mData = data;
	StartTimeJafarAttack = GetTickCount();
}
bool CheckLeftorRight;

void BossJafarAttack::Update()
{
	if (mData->boss->GetCurrentAnimation()->GetCurrentFrame() >2)
	{

		if (mData->boss->mPlayer->GetPosition().x > mData->boss->GetPosition().x)
		{
			mData->boss->mPlayer->AddPosition(D3DXVECTOR2(-2, 0));
			CheckLeftorRight = false;
		}
		if (mData->boss->mPlayer->GetPosition().x < mData->boss->GetPosition().x)
		{
			mData->boss->mPlayer->AddPosition(D3DXVECTOR2(2, 0));
			CheckLeftorRight = true;
		}
		if (abs(mData->boss->mPlayer->GetPosition().x - mData->boss->GetPosition().x) < 10)
		{
			if (CheckLeftorRight)
				mData->boss->mPlayer->AddPosition(D3DXVECTOR2(50, 0));
			else
				mData->boss->mPlayer->AddPosition(D3DXVECTOR2(-50, 0));
			CheckLeftorRight = !CheckLeftorRight;
			mData->boss->GetCurrentAnimation()->Reset();
			if (mData->boss->mPlayer->mCurrentState != PlayerState::Fired)
				mData->boss->mPlayer->SetState(new PlayerFiredState(mData->boss->mPlayer->mPlayerData));
			mData->boss->SetState(new BossStandJafar(mData));
			return;
		}/*
		if (check == 1) {
			mData->boss->GetCurrentAnimation()->SetCurrentFrame(5);
			check = 0;
		}
		else {
			mData->boss->GetCurrentAnimation()->SetCurrentFrame(6);
			check = 1;
		}*/
	}

	D3DXVECTOR3 A;
	if(mData->boss->mPlayer->GetPosition().x > mData->boss->GetPosition().x)
	 A = D3DXVECTOR3(mData->boss->GetPosition().x+30, mData->boss->GetPosition().y-50,0);
	// A = D3DXVECTOR3( mData->boss->mAnimationStar->GetSprite()->GetPosition().x + 30, mData->boss->mAnimationStar->GetSprite()->GetPosition().y - 50, 0);
	else A = D3DXVECTOR3(mData->boss->GetPosition().x - 30, mData->boss->GetPosition().y - 50, 0);
		//A = D3DXVECTOR3(mData->boss->mAnimationStar->GetSprite()->GetPosition().x - 30,	mData->boss->mAnimationStar->GetSprite()->GetPosition().y - 50, 0);
	D3DXVECTOR3 B = D3DXVECTOR3(mData->boss->mPlayer->GetPosition().x, mData->boss->mPlayer->GetPosition().y-10,0);
	D3DXVECTOR2 vtcp = D3DXVECTOR2(B.x - A.x, B.y - A.y);
	D3DXVECTOR2 vtpt = D3DXVECTOR2(vtcp.y, -vtcp.x);


	mData->boss->starPos.clear();
	if (A.x < B.x)
	{
		for (int i = A.x; i < B.x;i+=20)
		{
			float y = (-vtpt.x*(i - A.x)) / vtpt.y + A.y;
			mData->boss->starPos.push_back(D3DXVECTOR3(i, y,0));
		}
	}
	else
	{
		for (int i = B.x; i < A.x; i+=20)
		{
			float y = (-vtpt.x*(i - A.x)) / vtpt.y + A.y;
			mData->boss->starPos.push_back(D3DXVECTOR3(i, y,0));
		}
	}


	
	if (GetTickCount() - StartTimeJafarAttack >= 2500)
	{
		mData->boss->GetCurrentAnimation()->Reset();
		mData->boss->SetState(new BossStandJafar(mData));
	}


}
BossJafarAttack::StateName BossJafarAttack::GetState()
{
	return BossState::JafarAttack;
}


void BossJafarAttack::OnCollision(Entity *impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
	return;
}

