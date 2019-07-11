#include "Enemy3.h"
#include "../../Player/PlayerAttackedState.h"

vector<Rect> Enemy3::LoadRECT(Enemy3State::StateName state)
{
	vector<Rect> listSourceRect;
	switch (state)
	{
	case Enemy3State::Die:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLExplosions(), "Explosion1");
		break;

	case Enemy3State::None:
		break;
	case Enemy3State::Running:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLGuard(), "FatmanRun");

		break;
	case Enemy3State::Attack:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLGuard(), "FatmanAttack");

		break;
	case Enemy3State::Attacked:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLGuard(), "FatmanAttacked");

	default:
		break;
	}
	return listSourceRect;
}
Enemy3::Enemy3(Player *player, vector<D3DXVECTOR2> list)
{
	mPlayer = player;
	mListPosition = list;


	mAnimationRunning = new Animation(ResourceManager::GetInstance()->GetTextureGuard(), 8, LoadRECT(Enemy3State::Running), (float)1 / 1, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(120, 193, 152), Entity::Enemy);
	mAnimationAttack = new Animation(ResourceManager::GetInstance()->GetTextureGuard(), 7, LoadRECT(Enemy3State::Attack), (float)1 / 0.2, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(120, 193, 152), Entity::Enemy);
	mAnimationAttacked = new Animation(ResourceManager::GetInstance()->GetTextureGuard(), 10, LoadRECT(Enemy3State::Attacked), (float)1 / 0.25, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(120, 193, 152), Entity::Enemy);
	mAnimationDied = new Animation(ResourceManager::GetInstance()->GetTextureExplosions(), 5, LoadRECT(Enemy3State::Die), (float)1 / 0.5, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(186, 254, 202), Entity::flare);
	mAnimationDied->SetScale(D3DXVECTOR2(1.5, 1.5));

	Rect rect;
	rect.left = 9; rect.top = 663; rect.right = rect.left + 43; rect.bottom = rect.top + 49;
	mSprite = new Sprite(ResourceManager::GetInstance()->GetTextureGuard(), rect, 0, 0, D3DCOLOR_XRGB(120, 193, 152), D3DXVECTOR2(0.5, 1), GameGlobal::mEnemytexture);

	mCurrentAnimation = nullptr;
	mCurrentState = Enemy3State::None;
	Tag = EntityTypes::Enemy;
	this->mData = new Enemy3Data();
	this->mData->enemy = this;


	mKnife = new Weapon(Entity::KnifeEnemy3);
	mKnife->SetState(WeaponState::NONE);


}


Enemy3::~Enemy3()
{
	delete this;
}

void Enemy3::Update()
{


	CheckAction();

	mKnife->Update(1);
	mKnife->mReverse = !Reverse;

	if (Heal == 0)
	{
		positionted.push_back(CurrentPosIndex);
		SetState(new Enemy3Die(this->mData));

	}

	if (mCurrentState != Enemy3State::Attacked && mCurrentState != Enemy3State::Die)
	{
		if (CheckFire)
		{
			SetState(new Enemy3Fighting(this->mData));
			if (mKnife->GetCurrentState() == WeaponState::NONE)
			{
				mKnife->SetPosition(GetPosition().x, GetPosition().y - 50);
				mKnife->SetState(WeaponState::Flying);
			}
		}

		if (CheckRunning)
			SetState(new Enemy3Running(this->mData));

		if (!CheckFire && !CheckRunning)
		{
			mCurrentState = Enemy3State::None;
		}

	}


	if (mCurrentState != Enemy3State::None && mCurrentAnimation != nullptr)
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
void Enemy3::Draw(D3DXVECTOR2 transform)
{
	if (mCurrentAnimation != nullptr && mCurrentState != Enemy3State::None)
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


	mKnife->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(1, 1), transform);


}

void Enemy3::SetState(Enemy3State *newState)
{
	delete this->mData->state;

	this->mData->state = newState;

	this->changeAnimation(newState->GetState());

	mCurrentState = newState->GetState();
}
Rect Enemy3::GetBound()
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

void Enemy3::changeAnimation(Enemy3State::StateName state)
{
	switch (state)
	{
	case Enemy3State::None:
		mCurrentAnimation = nullptr;
		break;
	case Enemy3State::Running:
		mCurrentAnimation = mAnimationRunning;
		break;
	case Enemy3State::Attack:
		mCurrentAnimation = mAnimationAttack;
		if (!this->isDead() && mCurrentAnimation->GetCurrentFrame() == 0)
		{
			ResourceManager::GetInstance()->playSound("Attack", false, 1);
		}
		break;
	case Enemy3State::Attacked:
		mCurrentAnimation = mAnimationAttacked;
		break;
	case Enemy3State::Die:
		mCurrentAnimation = mAnimationDied;
		/*ResourceManager::GetInstance()->playSound("Die", false, 1);*/
		break;
	default:
		break;
	}

	this->width = mCurrentAnimation->GetSprite()->GetWidth();
	this->height = mCurrentAnimation->GetSprite()->GetHeight();
}
void Enemy3::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{

	if (this->mPlayer->isPlayerAttacking() || impactor->Tag == Entity::AppleThrow || impactor->Tag == Entity::CamelSpit && impactor->GetPosition().x> 1650 )
	{
		SetState(new Enemy3Attacked(this->mData));
	}
	if (mCurrentState == Enemy3State::Attack && mCurrentAnimation->GetCurrentFrame() == 4 && mPlayer->mCurrentState != PlayerState::Fired)
	{
		mPlayer->SetState(new PlayerAttackedState(mPlayer->mPlayerData));
	}
	if (this->mData->state)
		this->mData->state->OnCollision(impactor, side, data);
}
void Enemy3::CheckAction()
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
		if (abs(mPlayer->GetPosition().y - mListPosition.at(i).y) >= 60) continue;
		int deltay = abs(mPlayer->GetPosition().y - mListPosition.at(i).y);
		int deltax = abs(mPlayer->GetPosition().x - mListPosition.at(i).x);
		if (deltax <= 300 && deltay <= 100)
		{
			if (i == CurrentPosIndex) continue;
			SetPosition(mListPosition.at(i));
			CurrentPosIndex = i;
			break;
		}
	}


	int deltax = abs(GetPosition().x - mPlayer->GetPosition().x);
	if (GetPosition().x < 2015 && GetPosition().x < 1660 && GetPosition().y > 550)
	{ 
		CheckRunning = true;
		CheckFire = false;
		if (deltax <= 50)
		{
			CheckRunning = false;
			CheckFire = true;
		}
	}
	else if( GetPosition().x < 2190 && GetPosition().x > 1960 && GetPosition().y < 300
		|| GetPosition().x > 4470 && GetPosition().y > 600
		|| GetPosition().x > 3850 && GetPosition().x < 4000 && GetPosition().y > 350 && GetPosition().y < 500
		|| GetPosition().x > 2930 && GetPosition().x < 3000 && GetPosition().y > 350 && GetPosition().y < 500
		|| GetPosition().x > 3210 && GetPosition().x < 3480 && GetPosition().y < 350
		|| GetPosition().x > 4410 && GetPosition().y < 350)
	{
		if (deltax > 250)
		{
			CheckRunning = false;
			CheckFire = false;
			return;
		}
		if (deltax <= 250 && deltax >= 100)
		{
			CheckRunning = true;
			CheckFire = false;
		}
		if (deltax <= 140)
		{
			CheckRunning = false;
			CheckFire = true;
		}
	}
	else {}
	if (GetPosition().x < 1950 && GetPosition().y < 600 && GetPosition().y > 300)
	{

		CheckRunning = false;
		CheckFire = false;
	}
	if (GetPosition().x < 3230 && GetPosition().x > 3220 && GetPosition().y < 500 && GetPosition().y > 300)
	{
		CheckRunning = false;
		if (deltax <= 140)
		{
			CheckFire = true;
		}
	}

}
Animation* Enemy3::GetCurrentAnimation()
{
	return mCurrentAnimation;
}