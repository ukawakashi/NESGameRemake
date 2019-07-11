#include "Enemy1.h"


vector<Rect> Enemy1::LoadRECT(Enemy1State::StateName state)
{
	vector<Rect> listSourceRect;
	switch (state)
	{
	case Enemy1State::Die:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLExplosions(), "Explosion1");
		break;

	case Enemy1State::None:
		break;
	case Enemy1State::Running:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLGuard(), "StickmanRun");

		break;
	case Enemy1State::Attack:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLGuard(), "StickmanAttack");

		break;
	case Enemy1State::Attacked:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLGuard(), "StickmanAttacked");
		break;
	default:
		break;
	}
	return listSourceRect;
}
Enemy1::Enemy1(Player *player, vector<D3DXVECTOR2> list)
{
	mPlayer = player;
	mListPosition = list;


	mAnimationRunning = new Animation(ResourceManager::GetInstance()->GetTextureGuard(), 8, LoadRECT(Enemy1State::Running), (float)1 / 1, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(120, 193, 152), Entity::Enemy);
	mAnimationAttack = new Animation(ResourceManager::GetInstance()->GetTextureGuard(), 6, LoadRECT(Enemy1State::Attack), (float)1 / 0.25, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(120, 193, 152), Entity::Enemy);
	mAnimationAttacked = new Animation(ResourceManager::GetInstance()->GetTextureGuard(), 9, LoadRECT(Enemy1State::Attacked), (float)1 / 0.5, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(120, 193, 152), Entity::Enemy);
	mAnimationDied = new Animation(ResourceManager::GetInstance()->GetTextureExplosions(), 5, LoadRECT(Enemy1State::Die), (float)1 / 0.5, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(186, 254, 202), Entity::flare);
	mAnimationDied->SetScale(D3DXVECTOR2(1.5, 1.5));
	mSprite = new Sprite(ResourceManager::GetInstance()->GetTextureGuard(), LoadRECT(Enemy1State::Attacked).at(0), 0, 0, D3DCOLOR_XRGB(120, 193, 152), D3DXVECTOR2(0.5, 1), GameGlobal::mEnemytexture);

	mCurrentAnimation = nullptr;
	mCurrentState = Enemy1State::None;
	Tag = EntityTypes::Enemy;
	this->mData = new Enemy1Data();
	this->mData->enemy = this;




}


Enemy1::~Enemy1()
{
	delete this;
}

void Enemy1::Update()
{
		CheckAction();

		if (Heal == 0)
		{
			positionted.push_back(CurrentPosIndex);
			SetState(new Enemy1Die(this->mData));
		}

		if (mCurrentState != Enemy1State::Attacked && mCurrentState != Enemy1State::Die)
		{
			if (CheckFire)
			{
				SetState(new Enemy1Fighting(this->mData));
			}

			if (CheckRunning)
				SetState(new Enemy1Running(this->mData));

			if (!CheckFire && !CheckRunning)
			{
				mCurrentState = Enemy1State::None;
			}

		}





		if (mCurrentState != Enemy1State::None && mCurrentAnimation != nullptr)
		{

			mCurrentAnimation->Update(1);
			if (this->mData->state)
			{
				this->mData->state->Update();
			}
		}

		if (GetPosition().x < mPlayer->GetPosition().x)
			Reverse = true;
		else
			Reverse = false;


}
void Enemy1::Draw(D3DXVECTOR2 transform)
{

	if (mCurrentAnimation != nullptr && mCurrentState != Enemy1State::None)
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

void Enemy1::SetState(Enemy1State *newState)
{
	delete this->mData->state;

	this->mData->state = newState;

	this->changeAnimation(newState->GetState());

	mCurrentState = newState->GetState();
}
Rect Enemy1::GetBound()
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

void Enemy1::changeAnimation(Enemy1State::StateName state)
{
	switch (state)
	{
	case Enemy1State::None:
		mCurrentAnimation = nullptr;
		break;
	case Enemy1State::Running:
		mCurrentAnimation = mAnimationRunning;
		break;
	case Enemy1State::Attack:
		mCurrentAnimation = mAnimationAttack;
		if (!this->isDead() && mCurrentAnimation->GetCurrentFrame() == 0)
		{
			ResourceManager::GetInstance()->playSound("Attack", false, 1);
		}
		break;
	case Enemy1State::Attacked:
		mCurrentAnimation = mAnimationAttacked;
		//if (Heal > 1)
			//ResourceManager::GetInstance()->playSound("Enemy1Attacked", false, 1);
		break;
	case Enemy1State::Die:
		mCurrentAnimation = mAnimationDied;
		//ResourceManager::GetInstance()->playSound("Die", false, 1);
		break;
	default:
		break;
	}

	this->width = mCurrentAnimation->GetSprite()->GetWidth();
	this->height = mCurrentAnimation->GetSprite()->GetHeight();
}
void Enemy1::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (this->mPlayer->isPlayerAttacking() || impactor->Tag == Entity::AppleThrow || impactor->Tag == Entity::CamelSpit)
	{
		SetState(new Enemy1Attacked(this->mData));

	}/*

	if (this->mPlayer->getState() == PlayerState::Attack || impactor->Tag == Entity::AppleThrow)
	{
		SetState(new Enemy1Attacked(this->mData));
	}*/
	if (mCurrentState == Enemy1State::Attack && mCurrentAnimation->GetCurrentFrame() == 4 &&
		mPlayer->mCurrentState == PlayerState::Standing)
	{
		mPlayer->SetState(new PlayerAttackedState(mPlayer->mPlayerData));
	}

	if (mCurrentState == Enemy1State::Attack && mCurrentAnimation->GetCurrentFrame() == 4 && mPlayer->mCurrentState != PlayerState::Standing && !mPlayer->isAttacked)
	{
		mPlayer->HPCount--;
		mPlayer->isAttacked = true;
	}
	if (this->mData->state)
		this->mData->state->OnCollision(impactor, side, data);




}
void Enemy1::CheckAction()
{
	for (int i = 0; i < mListPosition.size(); i++)
	{
		bool flag = false;
		for (int j = 0; j < positionted.size(); j++)
			if (i == positionted.at(j))
			{
				flag = true;
				break;
			}
		if (flag) continue;
		if (abs(mPlayer->GetPosition().y - mListPosition.at(i).y) >= 50) continue;
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


	if ((GetPosition().x - GetWidth() / 2) > 575 && GetPosition().x < 780 || GetPosition().x > 2660 && GetPosition().x < 2780)
	{
		if (deltax > 180)
		{
			CheckRunning = false;
			CheckFire = false;
			return;
		}
		if (deltax <= 180 && deltax >= 50)
		{
			CheckRunning = true;
			CheckFire = false;
		}

		if (deltax <= 50)
		{
			CheckRunning = false;
			CheckFire = true;
		}
	}
	else {
		CheckRunning = false;
		if (deltax <= 50)
		{
			CheckFire = true;
		}
	}
}


Animation* Enemy1::GetCurrentAnimation()
{
	return mCurrentAnimation;
}