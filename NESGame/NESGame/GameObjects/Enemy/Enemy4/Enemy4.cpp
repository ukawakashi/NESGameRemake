#include "Enemy4.h"

vector<Rect> Enemy4::LoadRect(bool flag)
{
	//flag =true la not die
	vector<Rect> listSourceRect;
	if (flag)
	{
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLCivilian(), "Circus");

	}
	else
	{
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLExplosions(), "Explosion1");
	}
	return listSourceRect;
}

Enemy4::Enemy4(vector<D3DXVECTOR2> listpos)
{
	mListPosition = listpos;
	SetPosition(listpos.at(0));
	ThrowAnimate = new Animation(ResourceManager::GetInstance()->GetTextureCivilian(), 11, LoadRect(true), (float)1 / 0.3, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(120, 193, 152), Entity::civilian);
	DieAnimate = new Animation(ResourceManager::GetInstance()->GetTextureExplosions(), 5, LoadRect(false), (float)1 / 0.5, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(186, 254, 202), Entity::flare);
	DieAnimate->SetScale(D3DXVECTOR2(1.5, 1.5));

	mKnife = new Weapon(Entity::KnifeEnemy3);
	Tag = Entity::Enemy;

	mCurrentKnife = mKnife;
	mCurrentKnife->SetPosition(GetPosition().x, GetPosition().y-30);
}


Enemy4::~Enemy4()
{
	delete this;
}
void Enemy4::Update(Entity* player)
{
	if (HP <= 0)
	{
		
		mCurrentAnimate = DieAnimate;
		mCurrentAnimate->SetPosition(GetPosition());
		Sound::getInstance()->play("Die", false, 1);
		mCurrentAnimate->Update(1);
		positionted.push_back(CurrentPosIndex);
		if (mCurrentAnimate->GetCurrentFrame() == 4)
		{
			mCurrentAnimate->Reset();
			mCurrentAnimate = nullptr;
			SetPosition(0, 0);
			HP = 2;
		}
		return;
	}
	CheckSite(player);
	mCurrentKnife->mReverse = mReverse;
	

	if (AllowThrow)
	{
		mCurrentAnimate = ThrowAnimate;

		if (mCurrentAnimate != nullptr) //Khac null moi update
		{
			mCurrentAnimate->SetPosition(GetPosition());
			mCurrentAnimate->Update(1);
			if (mCurrentAnimate->GetCurrentFrame() ==11) //Nem xong thi thoi ko nem nua,cho khi nao bowl None moi nem tiep
				mCurrentAnimate = nullptr;
		}


		if (mCurrentKnife->GetCurrentState() == WeaponState::NONE) //NONE FIRST, None thi flying
		{
			if (mCurrentAnimate != nullptr && mCurrentAnimate->GetCurrentFrame() == 8)
			{
				mCurrentKnife->SetPosition(GetPosition().x, GetPosition().y-30);
				mCurrentKnife->SetState(WeaponState::Flying);
				mCurrentKnife->curState->acceX = 8.0f;
				mCurrentKnife->curState->acceY = 0.07f;
			}
		}
	}
	else
	{
		if (mCurrentAnimate != nullptr)
		{
			if (mCurrentAnimate->GetCurrentFrame()<9)
				mCurrentAnimate->Update(1);
			else
				mCurrentAnimate = nullptr;
		}
	}
	mCurrentKnife->Update(1);
}

void Enemy4::CheckSite(Entity* player)
{


	for (int i = 0; i < mListPosition.size(); i++)
	{
		bool flag = false;
		for (int j = 0; j<positionted.size(); j++)
			if (i == positionted.at(j))
			{
				flag = true;
				break;
			}
		if (flag) continue;
		int deltay = player->GetPosition().y - mListPosition.at(i).y;
		int deltax = abs(player->GetPosition().x - mListPosition.at(i).x);
		if (deltax <= 200)
		{
			SetPosition(mListPosition.at(i));
			CurrentPosIndex = i;
			break;
		}
	}
	if (abs(GetPosition().x - player->GetPosition().x) <= 200 )
		AllowThrow = true;
	else AllowThrow = false;

	if (player->GetPosition().x > GetPosition().x) mReverse = false;
	else  mReverse = true;


}
void Enemy4::Draw(D3DXVECTOR3 position, Rect sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{


	if (mCurrentAnimate != nullptr)
	{
		mCurrentAnimate->GetSprite()->FlipVertical(mReverse);
		mCurrentAnimate->Draw(GetPosition(), sourceRect, scale, transform, angle, rotationCenter, colorKey);
	}
	if (mCurrentKnife->GetCurrentState() != WeaponState::NONE)
		mCurrentKnife->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);

}
void Enemy4::OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side)
{
	if (this->mPlayer->isPlayerAttacking() && mPlayer->GetCurrentAnimation()->GetCurrentFrame() == 3)
		HP--;
	if (impactor->Tag == Entity::AppleThrow) HP--;
//	mCurrentKnife->SetState(WeaponState::Breaking);

}


Rect Enemy4::GetBound()
{
	Rect rect{ 0,0,0,0 };
	if (mCurrentAnimate == nullptr)
	{
		
		return rect;
	}

	rect.left = this->posX - mCurrentAnimate->GetSprite()->GetWidth() / 2;
	rect.right = rect.left + mCurrentAnimate->GetSprite()->GetWidth();
	rect.top = this->posY - mCurrentAnimate->GetSprite()->GetHeight(); //Chú ý đoạn này
	rect.bottom = this->posY;// + mCurrentAnimation->GetSprite()->GetHeight() / 2;

	float cWidth = this->posX;
	float cHeight = this->posY - mCurrentAnimate->GetSprite()->GetHeight() / 2;
	SetCenter(D3DXVECTOR2(cWidth, cHeight));
	return rect;
}