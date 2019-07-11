#include "Peddler1.h"

vector<Rect> Peddler1::LoadRect(int flag)
{
	vector<Rect> listSourceRect;
	switch (flag)
	{
	case 1:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLPeddler(), "Stand1"); break;
	case 2:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLPeddler(), "Showing"); break;
	case 3:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLPeddler(), "Stand2"); break;
	case 4:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLPeddler(), "Sell2"); break;
	default:
		break;
	}
	return listSourceRect;
}

Peddler1::Peddler1(vector<D3DXVECTOR2> listpos)
{
	mListPosition = listpos;
	SetPosition(listpos.at(0));
	Stand1Animate = new Animation(ResourceManager::GetInstance()->GetTexturePeddler(), 20, LoadRect(1), (float)1 / 0.3, D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(248, 0, 248), Entity::Peddler);
	Stand1Animate->SetScale(D3DXVECTOR2(1, 1));

	ShellAnimate = new Animation(ResourceManager::GetInstance()->GetTexturePeddler(), 26 , LoadRect(2), (float)1 / 0.3, D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::Peddler);
	ShellAnimate->SetScale(D3DXVECTOR2(1,1));

	Stand2Animate = new Animation(ResourceManager::GetInstance()->GetTexturePeddler(), 35, LoadRect(3), (float)1 / 0.3, D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(248, 0, 248), Entity::Peddler);
	Stand2Animate->SetScale(D3DXVECTOR2(1, 1));
	Sell2Animate = new Animation(ResourceManager::GetInstance()->GetTexturePeddler(), 1, LoadRect(4), (float)1 / 0.3, D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::Peddler);
	
	mCurrentAnimate = Stand1Animate;
	mTemp = Stand2Animate;
	Tag = Entity::Enemy;

}


Peddler1::~Peddler1()
{
	delete this;
}
void Peddler1::Update(Entity* player)
{
	CheckSite(player);
	if (AllowStand1)
	{
		mCurrentAnimate = Stand1Animate;

		if (mCurrentAnimate != nullptr) //Khac null moi update
		{
			mCurrentAnimate->SetPosition(GetPosition());
			mCurrentAnimate->Update(1);
			if (mCurrentAnimate->GetCurrentFrame() == 19) //Nem xong thi thoi ko nem nua,cho khi nao bowl None moi nem tiep
			{
				AllowShell = true;
			}
		}
	}
	if (AllowShell) {
		mCurrentAnimate = ShellAnimate;

		if (mCurrentAnimate != nullptr) //Khac null moi update
		{
			mCurrentAnimate->SetPosition(GetPosition()/*.x, GetPosition().y-20*/);
			mCurrentAnimate->Update(1);
			if (mCurrentAnimate->GetCurrentFrame() == 20) //Nem xong thi thoi ko nem nua,cho khi nao bowl None moi nem tiep
			{
				AllowStand2 = true;
			}
			if (mCurrentAnimate->GetCurrentFrame() == 25) //Nem xong thi thoi ko nem nua,cho khi nao bowl None moi nem tiep
			{
				AllowSell2 = true;
			}
		}
	}
	if(AllowSell2){
		mCurrentAnimate = Sell2Animate;

		if (mCurrentAnimate != nullptr) //Khac null moi update
		{
			mCurrentAnimate->SetPosition(GetPosition()/*.x, GetPosition().y-20*/);
			mCurrentAnimate->Update(1);
			mTemp->Update(1);
		}
	}
}

void Peddler1::CheckSite(Entity* player)
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
	if (abs(GetPosition().x - player->GetPosition().x) <= 100 && player->GetPosition().y < 230)
		AllowStand1 = true;
	else AllowStand1 = false;


}
void Peddler1::Draw(D3DXVECTOR3 position, Rect sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if (mCurrentAnimate != nullptr)
		mCurrentAnimate->Draw(GetPosition(), sourceRect, scale, transform, angle, rotationCenter, colorKey);
	if (AllowStand2)
		mTemp->Draw(D3DXVECTOR3(3989,213,0), sourceRect, scale, transform, angle, rotationCenter, colorKey);
}
void Peddler1::OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side)
{
//	if (impactor->Tag == EntityTypes::PlayerOne)
//	{
//		if (this->mPlayer->isPlayerAttacking())
//			HP--;
//		//	mCurrentKnife->SetState(WeaponState::Breaking)
//	}
//	if (impactor->Tag == Entity::AppleThrow) HP--;
}

Rect Peddler1::GetBound()
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
