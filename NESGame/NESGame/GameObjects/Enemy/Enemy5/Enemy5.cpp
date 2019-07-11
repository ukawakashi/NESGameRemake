#include "Enemy5.h"

vector<Rect> Enemy5::LoadRECT(Enemy5State::StateName state)
{
	//flag =true la not die
	vector<Rect> listSourceRect;
	switch (state) {
	case Enemy5State::Running:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLCivilian(), "SneakerRun");
		break;
	case Enemy5State::Attack:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLCivilian(), "SneakerAttack");
		break;
	case Enemy5State::Attacked:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLCivilian(), "SneakerStand");
		break;
	case Enemy5State::Die:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLExplosions(), "Explosion1");
		break;
	default:
		break;
	}
	return listSourceRect;
}

Enemy5::Enemy5(Player *player, vector<D3DXVECTOR2> listpos)
{
	mPlayer = player;
	mListPosition = listpos;

	SetPosition(listpos.at(0));
	mAnimationRunning = new Animation(ResourceManager::GetInstance()->GetTextureCivilian(), 12, LoadRECT(Enemy5State::Running), (float)1 / 0.3, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(120, 193, 152), Entity::civilian);
	mAnimationAttack = new Animation(ResourceManager::GetInstance()->GetTextureCivilian(), 4, LoadRECT(Enemy5State::Attack), (float)1 / 0.3, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(120, 193, 152), Entity::civilian);
	mAnimationAttacked = new Animation(ResourceManager::GetInstance()->GetTextureCivilian(), 6, LoadRECT(Enemy5State::Attacked), (float)1 / 0.3, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(120, 193, 152), Entity::civilian);
	mAnimationDied = new Animation(ResourceManager::GetInstance()->GetTextureExplosions(), 5, LoadRECT(Enemy5State::Die), (float)1 / 0.5, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(186, 254, 202), Entity::flare);
	mAnimationDied->SetScale(D3DXVECTOR2(1.5, 1.5));

	mSprite = new Sprite(ResourceManager::GetInstance()->GetTextureGuard(), LoadRECT(Enemy5State::Attack).at(0), 0, 0, D3DCOLOR_XRGB(120, 193, 152), D3DXVECTOR2(0.5, 1), GameGlobal::mCiviliantexture);

	mCurrentAnimation = nullptr;
	mCurrentState = Enemy5State::None;
	Tag = EntityTypes::Enemy;
	this->mData = new Enemy5Data();
	this->mData->enemy = this;
}


Enemy5::~Enemy5()
{
	delete this;
}
void Enemy5::Update()
{
	CheckAction();
	if (Heal == 0)
	{
		positionted.push_back(CurrentPosIndex);
		SetState(new Enemy5Die(this->mData));
	}

	if (mCurrentState != Enemy5State::Attacked && mCurrentState != Enemy5State::Die)
	{
		if (CheckFire)
		{
			SetState(new Enemy5Fighting(this->mData));
		}

		if (CheckRunning)
			SetState(new Enemy5Running(this->mData));

		if (!CheckFire && !CheckRunning)
		{
			//SetState(new Enemy5Attacked(this->mData));
			mCurrentState = Enemy5State::None;
		}

	}


	if (mCurrentState != Enemy5State::None && mCurrentAnimation != nullptr)
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
void Enemy5::Draw(D3DXVECTOR2 transform)
{

	if (mCurrentAnimation != nullptr && mCurrentState != Enemy5State::None)
	{
		mCurrentAnimation->SetPosition(this->GetPosition());

		mCurrentAnimation->GetSprite()->FlipVertical(!Reverse);
		mCurrentAnimation->GetSprite()->SetTranslation(transform);
		mCurrentAnimation->Draw();

	}

	else
	{
		mSprite->FlipVertical(!Reverse);
		mSprite->SetTranslation(transform);
		mSprite->SetPosition(GetPosition());
		mSprite->Draw();
	}


}
void Enemy5::SetState(Enemy5State *newState)
{
	delete this->mData->state;

	this->mData->state = newState;

	this->changeAnimation(newState->GetState());

	mCurrentState = newState->GetState();
}

void Enemy5::OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side)
{
	if (this->mPlayer->isPlayerAttacking() || impactor->Tag == Entity::AppleThrow)
	{
		//SetState(new Enemy5Attacked(this->mData));
		this->Heal--;
	}
	if (mCurrentState == Enemy5State::Attack && mCurrentAnimation->GetCurrentFrame() == 3 &&
		mPlayer->mCurrentState == PlayerState::Standing)
	{
		SetState(new Enemy5Fighting(this->mData));
		mPlayer->SetState(new PlayerAttackedState(mPlayer->mPlayerData));
	}

	if (mCurrentState == Enemy5State::Attack && mCurrentAnimation->GetCurrentFrame() == 3 && mPlayer->mCurrentState != PlayerState::Standing && !mPlayer->isAttacked)
	{
		mPlayer->HPCount--;
		mPlayer->isAttacked = true;
	}
	if (this->mData->state)
		this->mData->state->OnCollision(impactor, side, data);
//	mCurrentKnife->SetState(WeaponState::Breaking);

}


Rect Enemy5::GetBound()
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

void Enemy5::changeAnimation(Enemy5State::StateName state)
{
	switch (state)
	{
	case Enemy5State::None:
		mCurrentAnimation = nullptr;
		break;
	case Enemy5State::Running:
		mCurrentAnimation = mAnimationRunning;
		break;
	case Enemy5State::Attack:
		mCurrentAnimation = mAnimationAttack;
		/*if (!this->isDead() && mCurrentAnimation->GetCurrentFrame() == 0)
		{
			ResourceManager::GetInstance()->playSound("Attack", false, 1);
		}*/
		break;
	case Enemy5State::Attacked:
		mCurrentAnimation = mAnimationAttacked;
		//if (Heal > 1)
			//ResourceManager::GetInstance()->playSound("Enemy2Attacked", false, 1);
		break;
	case Enemy5State::Die:
		mCurrentAnimation = mAnimationDied;
		//ResourceManager::GetInstance()->playSound("Die", false, 1);
		break;
	default:
		break;
	}

	this->width = mCurrentAnimation->GetSprite()->GetWidth();
	this->height = mCurrentAnimation->GetSprite()->GetHeight();
}
void Enemy5::CheckAction() {
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
	//if (GetPosition().x > 2820 && GetPosition().x < 2980) {
		if (deltax > 120)
		{
			CheckRunning = false;
			CheckFire = false;
			return;
		}
		if (deltax <= 120 && deltax >= 20)
		{
			CheckRunning = true;
			CheckFire = false;
		}
		if (deltax <= 20)
		{
			CheckRunning = false;
			CheckFire = true;
		}
	/*}
	else
	{
		CheckRunning = false;
		CheckFire = false;
	}*/
	
}

Animation* Enemy5::GetCurrentAnimation()
{
	return mCurrentAnimation;
}