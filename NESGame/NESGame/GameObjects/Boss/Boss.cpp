#include "Boss.h"


vector<Rect> Boss::LoadRect(BossState::StateName state)
{
	vector<Rect> listSourceRect;
	Rect rect;
	switch (state)
	{
	case BossState::StandJafar:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLJafar(), "JafarStand");

		break;
	case BossState::StandSnake:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLJafar(), "JafarSnakeStand");
		break;
	case BossState::JafarAttack:
		/*rect.left = 8; rect.top = 9; rect.right = rect.left + 64; rect.bottom = rect.top + 70; listSourceRect.push_back(rect);*/
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLJafar(), "JafarStartPulling");
		break;
	case BossState::SnakeAttack:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLJafar(), "JafarSnakeAttack");
		break;
	case BossState::Die:
		break;

	}
	return listSourceRect;
}
vector<Rect> Boss::LoadRectFire()
{
	vector<Rect> listSourceRect;
	listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLJafar(), "AroundFire");
	return listSourceRect;
}
vector<Rect> Boss::LoadRectStar()
{
	vector<Rect> listSourceRect;
	listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLJafar(), "Pull");
	return listSourceRect;
}
Boss::Boss(Player* player, D3DXVECTOR3 pos)
{
	SetPosition(pos);
	mPlayer = player;
	mPlayer->AppleCount = 50;
	mAnimationStandJafar = new Animation(ResourceManager::GetInstance()->GetTextureBossJafar(), 8, LoadRect(BossState::StandJafar), (float)1 / 0.15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(186, 254, 202), Entity::jafar);
	mAnimationJafarAttack = new Animation(ResourceManager::GetInstance()->GetTextureBossJafar(), 17, LoadRect(BossState::JafarAttack), (float)1 / 0.2, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(186, 254, 202), Entity::jafar);
	mAnimationSnakeAttack = new Animation(ResourceManager::GetInstance()->GetTextureBossJafar(), 11, LoadRect(BossState::SnakeAttack), (float)1 / 0.25, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(186, 254, 202), Entity::jafar);
	mAnimationStandSnake = new Animation(ResourceManager::GetInstance()->GetTextureBossJafar(), 6, LoadRect(BossState::StandSnake), (float)1 / 0.15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(186, 254, 202), Entity::jafar);


	mAnimationFire1 = new Animation(ResourceManager::GetInstance()->GetTextureBossJafar(), 5, LoadRectFire(), (float)1 / 0.15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(186, 254, 202), Entity::jafar);
	mAnimationFire2 = new Animation(ResourceManager::GetInstance()->GetTextureBossJafar(), 5, LoadRectFire(), (float)1 / 0.15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(186, 254, 202), Entity::jafar);
	mAnimationFire3 = new Animation(ResourceManager::GetInstance()->GetTextureBossJafar(), 5, LoadRectFire(), (float)1 / 0.15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(186, 254, 202), Entity::jafar);
	mAnimationFire1->SetScale(D3DXVECTOR2(1, 1.5));
	mAnimationFire2->SetScale(D3DXVECTOR2(1, 1.5));
	mAnimationFire3->SetScale(D3DXVECTOR2(1, 1));
	mAnimationFire1->SetPosition(GetPosition().x - 30, GetPosition().y);
	mAnimationFire2->SetPosition(GetPosition().x + 30, GetPosition().y);
	mAnimationFire3->SetPosition(GetPosition());

	mAnimationStar = new Animation(ResourceManager::GetInstance()->GetTextureBossJafar(), 3, LoadRectStar(), (float)1 / 0.1, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(186, 254, 202), Entity::jafar);


	Rect rect;
	rect.left = 198; rect.top = 226; rect.right = rect.left + 27; rect.bottom = rect.top + 13;
	star1 = new Sprite(ResourceManager::GetInstance()->GetTextureBossJafar(), rect, 0, 0, D3DCOLOR_XRGB(186, 254, 202), D3DXVECTOR2(0.5, 0.5), GameGlobal::mJafartexture);

	rect.left = 238; rect.top = 224; rect.right = rect.left + 23; rect.bottom = rect.top + 15;
	star2 = new Sprite(ResourceManager::GetInstance()->GetTextureBossJafar(), rect, 0, 0, D3DCOLOR_XRGB(186, 254, 202), D3DXVECTOR2(0.5, 0.5), GameGlobal::mJafartexture);

	rect.left = 270; rect.top = 225; rect.right = rect.left + 25; rect.bottom = rect.top + 14;
	star3 = new Sprite(ResourceManager::GetInstance()->GetTextureBossJafar(), rect, 0, 0, D3DCOLOR_XRGB(186, 254, 202), D3DXVECTOR2(0.5, 0.5), GameGlobal::mJafartexture);

	this->mData = new BossData();
	this->mData->boss = this;

	SetState(new BossStandJafar(mData));


	listFireBurn.push_back(new FireBurn(D3DXVECTOR2(GetPosition().x, GetPosition().y + 4)));
	listFireBurn.push_back(new FireBurn(D3DXVECTOR2(GetPosition().x, GetPosition().y + 4)));
	listFireBurn.push_back(new FireBurn(D3DXVECTOR2(GetPosition().x, GetPosition().y + 4)));


	/*listMeteor.push_back(new Apple(Entity::FireBullet));
	lastTimeCreateMeteor = GetTickCount();*/
}


Boss::~Boss()
{
}
void Boss::Update()
{
	/*if (GetTickCount() - lastTimeCreateMeteor >= 3500 && listMeteor.size() <2)
	{
		listMeteor.push_back(new Apple(Entity::FireBullet));
		lastTimeCreateMeteor = GetTickCount();
	}*/

	/*if(mCurrentState==BossState::MeteorSummon || mCurrentState == BossState::StandJafar || mCurrentState == BossState::JafarAttack)
		for (int i = 0; i < listMeteor.size(); i++)
	{

		if (listMeteor.at(i)->GetCurrentState() == AppleState::NONE)
		{
			int left = mPlayer->GetPosition().x - 100;
			int right = mPlayer->GetPosition().x + 100;
			int a = rand() %  (right-left +1) + left;
			listMeteor.at(i)->SetPosition(a, 250);

			listMeteor.at(i)->SetState(AppleState::Flying);
		}
		else
		listMeteor.at(i)->Update(1);

	}*/


	if (mData->boss->mPlayer->GetPosition().x < mData->boss->GetPosition().x)
		Reverse = true;
	else if (mData->boss->mPlayer->GetPosition().x > mData->boss->GetPosition().x)
		Reverse = false;

	if (BossAttacked)
	{
		if ((GetTickCount() - lastTimeBossAttacked) / 1000.0f >= 0.7f)
			BossAttacked = false;
	}
	//if (HPCount <=30 && HPCount > 12 && mCurrentState != BossState::StandJafar  && mCurrentState != BossState::JafarAttack)
	//{
	//	/*SetState(new BossJafarAttack(mData));
	//	return;*/
	//}
	if (HPCount == 15 && mCurrentState != BossState::SnakeAttack &&  mCurrentState != BossState::StandSnake)
	{
		SetState(new BossSnakeAttack(mData));
		return;
	}

	if (mCurrentState == BossState::SnakeAttack || mCurrentState == BossState::StandSnake)
	{

		mAnimationFire1->Update(1);
		mAnimationFire2->Update(1);
		mAnimationFire3->Update(1);
	}
	mCurrentAnimation->Update(1);


	if (this->mData->state)
	{
		this->mData->state->Update();
	}


	for (int i = 0; i < listFireBurn.size(); i++)
	{
		listFireBurn.at(i)->Update();
	}
}
void Boss::DrawStar(D3DXVECTOR2 transform)
{
	//srand(time(NULL));
	for (int i = 0; i < starPos.size(); i++)
	{
		if (i % 2 == 0) {
			int a = rand() % 3 + 1;
			if (a == 1)
				star1->Draw(D3DXVECTOR3(starPos.at(i).x, starPos.at(i).y /*- a*4*/, 0), Rect(), D3DXVECTOR2(), transform);
			if (a == 2)
				star2->Draw(D3DXVECTOR3(starPos.at(i).x, starPos.at(i).y /*+a*4*/, 0), Rect(), D3DXVECTOR2(), transform);
			if (a == 3)
				star3->Draw(D3DXVECTOR3(starPos.at(i).x, starPos.at(i).y /*-a*4*/, 0), Rect(), D3DXVECTOR2(), transform);
			/*if(i % 3 == 0)
				mAnimationStar->Draw(D3DXVECTOR3(starPos.at(i).x, starPos.at(i).y, 0), Rect(), D3DXVECTOR2(), transform);*/
		}
	}
}
void Boss::Draw(D3DXVECTOR2 transform)
{
	if (mCurrentState == BossState::SnakeAttack || mCurrentState == BossState::StandSnake)
	{
		mAnimationFire1->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), transform);
		mAnimationFire2->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), transform);

	}

	mCurrentAnimation->GetSprite()->FlipVertical(Reverse);
	mCurrentAnimation->SetPosition(GetPosition());
	mCurrentAnimation->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), transform);

	if (mCurrentState == BossState::JafarAttack  /*&& mCurrentAnimation->GetCurrentFrame()>=5*/)
		DrawStar(transform);


	if (mCurrentState == BossState::SnakeAttack || mCurrentState == BossState::StandSnake)
		mAnimationFire3->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), transform);


	for (int i = 0; i < listFireBurn.size(); i++)
	{
		listFireBurn.at(i)->Draw(transform);
	}

	/*if (mCurrentState == BossState::MeteorSummon || mCurrentState == BossState::StandJafar || mCurrentState == BossState::JafarAttack)
	for (int i = 0; i < listMeteor.size(); i++)
	{
		if (listMeteor.at(i)->GetCurrentState() != AppleState::NONE)
			listMeteor.at(i)->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), transform);

	}*/

}

void Boss::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == Entity::AppleThrow)
	{
		HPCount--;
		lastTimeBossAttacked = GetTickCount();
		BossAttacked = true;
	}
}
void Boss::SetState(BossState *newState)
{
	delete this->mData->state;

	this->mData->state = newState;

	this->changeAnimation(newState->GetState());

	mCurrentState = newState->GetState();
}
void Boss::changeAnimation(BossState::StateName state)
{
	switch (state)
	{
		/*case BossState::MeteorSummon:
			mCurrentAnimation = mAnimationStandJafar;
			break;*/
	case BossState::None:
		mCurrentAnimation = nullptr;
		break;
	case BossState::StandJafar:
		mCurrentAnimation = mAnimationStandJafar;
		break;
	case BossState::StandSnake:
		mCurrentAnimation = mAnimationStandSnake;
		break;
	case BossState::JafarAttack:
		mCurrentAnimation = mAnimationJafarAttack;
		break;
	case BossState::SnakeAttack:
		mCurrentAnimation = mAnimationSnakeAttack;
		break;
	}

	this->width = mCurrentAnimation->GetSprite()->GetWidth();
	this->height = mCurrentAnimation->GetSprite()->GetHeight();
}


Animation* Boss::GetCurrentAnimation()
{
	return mCurrentAnimation;
}
Rect Boss::GetBound()
{
	Rect rect;
	rect.left = this->posX - mCurrentAnimation->GetSprite()->GetWidth() / 2;
	rect.right = rect.left + mCurrentAnimation->GetSprite()->GetWidth();
	rect.top = this->posY - mCurrentAnimation->GetSprite()->GetHeight(); //Chú ý đoạn này
	rect.bottom = this->posY;

	float cWidth = this->posX;
	float cHeight = this->posY - mCurrentAnimation->GetSprite()->GetHeight() / 2;
	SetCenter(D3DXVECTOR2(cWidth, cHeight));
	return rect;
}