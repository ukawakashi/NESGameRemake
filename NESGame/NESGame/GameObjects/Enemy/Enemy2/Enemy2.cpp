#include "Enemy2.h"
#include <ctime>

vector<Rect> Enemy2::LoadRECT(Enemy2State::StateName state)
{
	vector<Rect> listSourceRect;
	switch (state)
	{
	case Enemy2State::Die:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLExplosions(), "Explosion1");
		break;
	case Enemy2State::None:
		break;
	case Enemy2State::Running:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLGuard(), "SwordmanRun");
		break;
	case Enemy2State::Attack:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLGuard(), "SwordmanAttack");
		break;
	case Enemy2State::Attacked:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLGuard(), "SwordmanAttacked");
	case Enemy2State::Benkon:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLGuard(), "SwordmanProvocative");
		break;
	case Enemy2State::WalkHotcoal:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLGuard(), "SwordmanWalkHotcoal");
		break;
	default:
		break;
	}
	return listSourceRect;
}
Enemy2::Enemy2(Player *player, vector<D3DXVECTOR2> list)
{
	mPlayer = player;
	mListPosition = list;

	mAnimationRunning = new Animation(ResourceManager::GetInstance()->GetTextureGuard(), 8, LoadRECT(Enemy2State::Running), (float)1 / 1, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(120, 193, 152), Entity::Enemy);
	mAnimationAttack = new Animation(ResourceManager::GetInstance()->GetTextureGuard(), 11, LoadRECT(Enemy2State::Attack), (float)1 / 0.25, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(120, 193, 152), Entity::Enemy);
	mAnimationAttacked = new Animation(ResourceManager::GetInstance()->GetTextureGuard(), 6, LoadRECT(Enemy2State::Attacked), (float)1 / 0.5, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(120, 193, 152), Entity::Enemy);
	mAnimationDied = new Animation(ResourceManager::GetInstance()->GetTextureExplosions(), 5, LoadRECT(Enemy2State::Die), (float)1 / 0.5, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(186, 254, 202), Entity::flare);
	mAnimationDied->SetScale(D3DXVECTOR2(1.5, 1.5));
	mAnimationBenkon = new Animation(ResourceManager::GetInstance()->GetTextureGuard(), 6, LoadRECT(Enemy2State::Benkon), (float)1 / 0.25, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(120, 193, 152), Entity::Enemy);
	mAnimationWalkHotcoal = new Animation(ResourceManager::GetInstance()->GetTextureGuard(), 9, LoadRECT(Enemy2State::WalkHotcoal), (float)1 / 0.5, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(120, 193, 152), Entity::Enemy);
	mSprite = new Sprite(ResourceManager::GetInstance()->GetTextureGuard(), LoadRECT(Enemy2State::Attack).at(0), 0, 0, D3DCOLOR_XRGB(120, 193, 152), D3DXVECTOR2(0.5, 1), GameGlobal::mEnemytexture);

	mCurrentAnimation = nullptr;
	mCurrentState = Enemy2State::None;
	Tag = EntityTypes::Enemy;
	this->mData = new Enemy2Data();
	this->mData->enemy = this;
}


Enemy2::~Enemy2()
{
	delete this;
}

void Enemy2::Update()
{
	srand(time(NULL));
	CheckAction();

	if (Heal == 0)
	{
		positionted.push_back(CurrentPosIndex);
		SetState(new Enemy2Die(this->mData));
	}

	if (mCurrentState != Enemy2State::Attacked && mCurrentState != Enemy2State::Die)
	{
		if (CheckFire)
			SetState(new Enemy2Fighting(this->mData));

		if (CheckRunning)
			SetState(new Enemy2Running(this->mData));
		if (CheckCoal)
			SetState(new Enemy2WalkHotcoal(this->mData));
		if (CheckBecKon)
			SetState(new Enemy2Beckon(this->mData));
		if (!CheckFire && !CheckRunning)
		{
			int a = rand() % 2;
			switch (a)
			{
			case 0:
				randomState = new Enemy2Beckon(this->mData); break;
			case 1:
				randomState = new Enemy2Fighting(this->mData); break;
			}
			SetState(randomState);
		}

	}





	if (mCurrentState != Enemy2State::None && mCurrentAnimation != nullptr)
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

void Enemy2::Draw(D3DXVECTOR2 transform)
{

	if (mCurrentAnimation != nullptr && mCurrentState != Enemy2State::None)
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

void Enemy2::SetState(Enemy2State *newState)
{
	delete this->mData->state;

	this->mData->state = newState;

	this->changeAnimation(newState->GetState());

	mCurrentState = newState->GetState();
}
Rect Enemy2::GetBound()
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

void Enemy2::changeAnimation(Enemy2State::StateName state)
{
	switch (state)
	{
	case Enemy2State::None:
		mCurrentAnimation = nullptr;
		break;
	case Enemy2State::Running:
		mCurrentAnimation = mAnimationRunning;
		break;
	case Enemy2State::Attack:
		mCurrentAnimation = mAnimationAttack;
		if (!this->isDead() && mCurrentAnimation->GetCurrentFrame() == 0)
		{
			ResourceManager::GetInstance()->playSound("Attack", false, 1);
		}
		break;
	case Enemy2State::Attacked:
		mCurrentAnimation = mAnimationAttacked;
		//if (Heal > 1)
			//ResourceManager::GetInstance()->playSound("Enemy2Attacked", false, 1);
		break;
	case Enemy2State::Die:
		mCurrentAnimation = mAnimationDied;
		//ResourceManager::GetInstance()->playSound("Die", false, 1);
		break;
	case Enemy2State::Benkon:
		mCurrentAnimation = mAnimationBenkon;
		break;
	case Enemy2State::WalkHotcoal:
		mCurrentAnimation = mAnimationWalkHotcoal;
		break;
	default:
		break;
	}

	this->width = mCurrentAnimation->GetSprite()->GetWidth();
	this->height = mCurrentAnimation->GetSprite()->GetHeight();
}
void Enemy2::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{

	if (this->mPlayer->isPlayerAttacking() || impactor->Tag == Entity::AppleThrow)
	{
		SetState(new Enemy2Attacked(this->mData));
	}
	if (mCurrentState == Enemy2State::Attack && mCurrentAnimation->GetCurrentFrame() ==4    &&
		mPlayer->mCurrentState == PlayerState::Standing)
	{
		mPlayer->SetState(new PlayerAttackedState(mPlayer->mPlayerData));
	}

	if (mCurrentState == Enemy2State::Attack && mCurrentAnimation->GetCurrentFrame() == 4 && mPlayer->mCurrentState != PlayerState::Standing && !mPlayer->isAttacked)
	{
		mPlayer->HPCount--;
		mPlayer->isAttacked = true;
	}
	if (this->mData->state)
		this->mData->state->OnCollision(impactor, side, data);



	
}
void Enemy2::CheckAction()
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
	if (GetPosition().x > 810 && GetPosition().x < 1150) {
		if (GetPosition().x > 820 && GetPosition().x < 950 || GetPosition().x>1010 && GetPosition().x < 1120 || GetPosition().x>3070 && GetPosition().x < 3220)
			CheckCoal = true;
		else
			CheckCoal = false;
		if (deltax <= 500 && deltax >= 50)
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
	else if (GetPosition().x  > 3100 && GetPosition().x  <3340 && GetPosition().y >600
		|| GetPosition().x  > 3610 && GetPosition().x  <3860 && GetPosition().y >600
		|| GetPosition().x  > 4010 && GetPosition().x  <4300 && GetPosition().y >600
		|| GetPosition().x  > 3630 && GetPosition().x  <3810 && GetPosition().y <600 && GetPosition().y >350
		|| GetPosition().x  > 2910 && GetPosition().x  <3175 && GetPosition().y <300
		|| GetPosition().x  > 4420 && GetPosition().y <300)
	{
		if (deltax > 250)
			{
				CheckRunning = false;
				CheckFire = false;
				CheckBecKon = true;
			}
			if (deltax <= 250 && deltax >= 50)
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
	if (GetPosition().x == 1667.67 && GetPosition().y == 275.33)
	{
		if (deltax > 190)
		{
			CheckBecKon = true;
		}
		else {
			CheckRunning = false;
			CheckFire = true;
		}
	}
}
Animation* Enemy2::GetCurrentAnimation()
{
	return mCurrentAnimation;
}