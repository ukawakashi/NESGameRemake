#include "Peddler.h"

vector<Rect> Peddler::LoadRECT(PeddlerState::StateName state)
{
	vector<Rect> listSourceRect;
	switch (state)
	{
	case PeddlerState::Stand1:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLPeddler(),"Stand1");
		break;
	case PeddlerState::Sell:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLPeddler(),"Showing");
		break;
	case PeddlerState::Stand2:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLPeddler(),"Stand2");
		break;
	default:
		break;
	}
	return listSourceRect;
}

Peddler::Peddler(Player *player, vector<D3DXVECTOR2> list)
{
	mPlayer = player;
	mListPosition = list;

	mAnimationStand1 = new Animation(ResourceManager::GetInstance()->GetTexturePeddler(), 20, LoadRECT(PeddlerState::Stand1), (float)1 / 0.6, D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(248, 0, 248), Entity::Peddler);

	mAnimationSell = new Animation(ResourceManager::GetInstance()->GetTexturePeddler(), 26 , LoadRECT(PeddlerState::Sell), (float)1 / 0.02, D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::Peddler);
	mAnimationStand2 = new Animation(ResourceManager::GetInstance()->GetTexturePeddler(), 27, LoadRECT(PeddlerState::Stand2), (float)1 / 0.6, D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(248, 0, 248), Entity::Peddler);
	mSprite = new Sprite(ResourceManager::GetInstance()->GetTexturePeddler(), LoadRECT(PeddlerState::Stand1).at(0), 0, 0, D3DCOLOR_XRGB(120, 193, 152), D3DXVECTOR2(0.5, 1), GameGlobal::mPeddlertexture);

	mCurrentAnimation = nullptr;
	mTemp = mAnimationStand2;
	mCurrentState = PeddlerState::None;
	Tag = EntityTypes::Enemy;
	this->mData = new PeddlerData();
	this->mData->enemy = this;

}


Peddler::~Peddler()
{
	delete this;
}
void Peddler::Update()
{
	CheckAction();
	if (CheckStand1)
		SetState(new PeddlerStand1(this->mData));

	
}
void Peddler::Draw(D3DXVECTOR2 transform)
{
	if (mCurrentAnimation != nullptr && mCurrentState != PeddlerState::None)
	{
		mCurrentAnimation->SetPosition(this->GetPosition());

		mCurrentAnimation->GetSprite()->FlipVertical(Reverse);
		mCurrentAnimation->GetSprite()->SetTranslation(transform);
		mCurrentAnimation->Draw();

	}

	else
	{
		mSprite->FlipVertical(Reverse);
		mSprite->SetTranslation(transform);
		mSprite->SetPosition(GetPosition());
		mSprite->Draw();
	}
}
void Peddler::SetState(PeddlerState *newState)
{
	delete this->mData->state;

	this->mData->state = newState;

	this->changeAnimation(newState->GetState());

	mCurrentState = newState->GetState();
}
Rect Peddler::GetBound()
{
	Rect rect;
	if (mCurrentAnimation == nullptr)
	{
		rect.left = this->posX - mSprite->GetWidth() / 2;
		rect.right = rect.left + mSprite->GetWidth();
		rect.top = this->posY - mSprite->GetHeight(); //Chú ý đoạn này
		rect.bottom = this->posY;// + mCurrentAnimation->GetSprite()->GetHeight() / 2;
		return rect;
	}

	rect.left = this->posX - mCurrentAnimation->GetSprite()->GetWidth() / 2;
	rect.right = rect.left + mCurrentAnimation->GetSprite()->GetWidth();
	rect.top = this->posY - mCurrentAnimation->GetSprite()->GetHeight(); //Chú ý đoạn này
	rect.bottom = this->posY;// + mCurrentAnimation->GetSprite()->GetHeight() / 2;

	float cWidth = this->posX;
	float cHeight = this->posY - mCurrentAnimation->GetSprite()->GetHeight() / 2;
	SetCenter(D3DXVECTOR2(cWidth, cHeight));
	return rect;
}
void Peddler::changeAnimation(PeddlerState::StateName state)
{
	switch (state)
	{
	case PeddlerState::None:
		mCurrentAnimation = nullptr;
		break;
	case PeddlerState::Stand1:
		mCurrentAnimation = mAnimationStand1;
		break;
	case PeddlerState::Stand2:
		mCurrentAnimation = mAnimationStand2;
	case PeddlerState::Sell:
		mCurrentAnimation = mAnimationSell;
	default:
		break;
	}

	this->width = mCurrentAnimation->GetSprite()->GetWidth();
	this->height = mCurrentAnimation->GetSprite()->GetHeight();
}
void Peddler::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{

	/*if (this->mPlayer->isPlayerAttacking() || impactor->Tag == Entity::AppleThrow)
	{
		SetState(new Enemy2Attacked(this->mData));
	}
	if (mCurrentState == PeddlerState::Attack && mCurrentAnimation->GetCurrentFrame() == 4 &&
		mPlayer->mCurrentState == PlayerState::Standing)
	{
		mPlayer->SetState(new PlayerAttackedState(mPlayer->mPlayerData));
	}

	if (mCurrentState == PeddlerState::Attack && mCurrentAnimation->GetCurrentFrame() == 4 && mPlayer->mCurrentState != PlayerState::Standing && !mPlayer->isAttacked)
	{
		mPlayer->HPCount--;
		mPlayer->isAttacked = true;
	}
	if (this->mData->state)
		this->mData->state->OnCollision(impactor, side, data);*/




}
void Peddler::CheckAction()
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
		if (abs(mPlayer->GetPosition().y - mListPosition.at(i).y) >= 30) continue;
		int deltay = mPlayer->GetPosition().y - mListPosition.at(i).y;
		int deltax = abs(mPlayer->GetPosition().x - mListPosition.at(i).x);
		if (deltax <= 300 && deltay <= 150)
		{
			if (i == CurrentPosIndex) continue;
			SetPosition(mListPosition.at(i));
			CurrentPosIndex = i;
			break;
		}
	}


	int deltax = abs(GetPosition().x - mPlayer->GetPosition().x);
	
	if (deltax > 50)
	{
		CheckStand1 = false;
		CheckStand2 = false;
		CheckSell = false;
	}
	if (deltax <= 50)
	{
		CheckStand1 = true;
		CheckStand2 = false;
		CheckSell = false;
	}
	
}
Animation* Peddler::GetCurrentAnimation()
{
	return mCurrentAnimation;
}
