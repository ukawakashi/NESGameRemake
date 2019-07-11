#include "ManThrowBowl.h"

vector<Rect> ManThrowBowl::LoadRect(bool flag)
{
	vector<Rect> listSourceRect;
	if (flag)
	{
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLCivilian(), "ManThrowBowl");
	}
	else
	{
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLExplosions(), "Explosion1");
	}
	return listSourceRect;
}

ManThrowBowl::ManThrowBowl(vector<D3DXVECTOR2> listpos)
{
	mListPosition = listpos;
	SetPosition(listpos.at(0));
	ThrowAnimate = new Animation(ResourceManager::GetInstance()->GetTextureCivilian(), 10, LoadRect(true), (float)1 / 0.3, D3DXVECTOR2(0, 0.5), D3DCOLOR_XRGB(120, 193, 152), Entity::civilian);
	ThrowAnimate->SetScale(D3DXVECTOR2(1, 1));

	DieAnimate = new Animation(ResourceManager::GetInstance()->GetTextureExplosions(), 5, LoadRect(false), (float)1 / 0.3, D3DXVECTOR2(0, 0.5), D3DCOLOR_XRGB(120, 193, 152), Entity::civilian);
	DieAnimate->SetScale(D3DXVECTOR2(1.5, 1.5));

	mWeapon = new Weapon(Entity::Bowl);

	Tag = Entity::Enemy;
	mCurrentWeapon = mWeapon;
	mCurrentWeapon->SetPosition(GetPosition());
}


ManThrowBowl::~ManThrowBowl()
{
}
void ManThrowBowl::Update(Entity* player)
{
	
		CheckSite(player);
		if (HP <= 0)
		{
			mCurrentAnimate = DieAnimate;
			mCurrentAnimate->SetPosition(GetPosition());
			Sound::getInstance()->play("Die", false, 1);
			mCurrentAnimate->Update(1);
			if (mCurrentAnimate->GetCurrentFrame() == 4)
			{
				mCurrentAnimate->Reset();
				mCurrentAnimate = nullptr;
				SetPosition(0, 0);
				HP = 1;
			}
			return;
		}
		else
			if (AllowThrow)
			{
				mCurrentAnimate = ThrowAnimate;

				if (mCurrentAnimate != nullptr) //Khac null moi update
				{
					mCurrentAnimate->SetPosition(GetPosition());
					mCurrentAnimate->Update(1);
					if (mCurrentAnimate->GetCurrentFrame() == 9) //Nem xong thi thoi ko nem nua,cho khi nao bowl None moi nem tiep
						mCurrentAnimate = nullptr;
				}

				if (mCurrentWeapon->GetCurrentState() == WeaponState::NONE) //NONE FIRST, None thi flying
				{
					if (mCurrentAnimate != nullptr && mCurrentAnimate->GetCurrentFrame() == 7)
					{
						mCurrentWeapon->SetPosition(GetPosition().x + 25, GetPosition().y + 10);
						mCurrentWeapon->SetState(WeaponState::Flying);
					}
				}
			}
			else
			{
				if (mCurrentAnimate != nullptr)
				{
					if (mCurrentAnimate->GetCurrentFrame() < 9)
						mCurrentAnimate->Update(1);
					else
						mCurrentAnimate = nullptr;
				}
			}
		mCurrentWeapon->Update(1);
}

void ManThrowBowl::CheckSite(Entity* player)
{
	for (int i = 0; i < mListPosition.size(); i++)
	{
		if (player->GetPosition().y < mListPosition.at(i).y) continue;
		int deltay = player->GetPosition().y - mListPosition.at(i).y;
		int deltax = abs(player->GetPosition().x - mListPosition.at(i).x);
		if (deltax <= 100 && deltay <= 150)
		{
			SetPosition(mListPosition.at(i));
			break;
		}
	}
	if (abs(GetPosition().x - player->GetPosition().x) <= 100 && player->GetPosition().y > GetPosition().y)
		AllowThrow = true;
	else AllowThrow = false;


}
void ManThrowBowl::Draw(D3DXVECTOR3 position, Rect sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{


	if (mCurrentAnimate != nullptr)
		mCurrentAnimate->Draw(GetPosition(), sourceRect, scale, transform, angle, rotationCenter, colorKey);
	if (mCurrentWeapon->GetCurrentState() != WeaponState::NONE)
		mCurrentWeapon->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);

}
void ManThrowBowl::OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side)
{
	mCurrentWeapon->SetState(WeaponState::Breaking);
	if (impactor->Tag == EntityTypes::PlayerOne)
	{
		if (this->mPlayer->isPlayerAttacking())
			HP--;
		//	mCurrentKnife->SetState(WeaponState::Breaking)
	}
	if (impactor->Tag == Entity::AppleThrow) HP--;


}

Rect ManThrowBowl::GetBound()
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
