#include "BossScene.h"


BossScene::BossScene(Player* pl,UI* ui)
{
	mPlayer = pl;
	mUI = ui;
	LoadContent();

}
vector<Rect>  BossScene::loadRect(bool flag)
{
	vector<Rect> listSourceRect;
	Rect rect;
	if (flag)
	{
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLExplosions(), "Explosion4");
	}
	else
	{
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "KnifeBreaking");
	}
	return listSourceRect;
}
BossScene::~BossScene()
{
}
void BossScene::LoadContent()
{
	mBackColor = 0x54acd2;

	//Nhac nen
	ResourceManager::GetInstance()->playSound("BossTheme", true, 0);

	EatItem = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 10, loadRect(false), (float)1 / 0.5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255),Entity::PlayerOne);
	EatItem->SetScale(D3DXVECTOR2(1.5, 1.5));


	Damage = new Animation(ResourceManager::GetInstance()->GetTextureExplosions(),15, loadRect(true), (float)1 / 0.4, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(186, 254, 202),Entity::flare);
	//Damage->SetScale(D3DXVECTOR2(0.5, 0.5));

	mMap = new GameMapBoss("Resources/untitled1.tmx");
	
	mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	mCamera->SetPosition(GameGlobal::GetWidth() / 2,
		mMap->GetHeight() - mCamera->GetHeight());

	mMap->SetCamera(mCamera);


	mPlayer->SetPosition(200, 50);

	mPlayer->SetCamera(mCamera);

	mBoss = new Boss(mPlayer,D3DXVECTOR3(338, 365,0));

	Rect rect;
	rect.left = 370; rect.top = 45; rect.right = rect.left + 14; rect.bottom = rect.top + 14;
	Sprite* appleSprite1 = new Sprite("Resources/Aladdin.png", rect, 0, 0, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5),GameGlobal::mAladdintexture);
	Sprite* appleSprite2 = new Sprite("Resources/Aladdin.png", rect, 0, 0, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5), GameGlobal::mAladdintexture);
	Sprite* appleSprite3 = new Sprite("Resources/Aladdin.png", rect, 0, 0, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5), GameGlobal::mAladdintexture);
	app1 = new AppleObject(appleSprite1); app1->SetPos(0, 0);
	app2= new AppleObject(appleSprite2); app2->SetPos(0, 0);
	app3 = new AppleObject(appleSprite3); app3->SetPos(0, 0);

	
	myFont = NULL;

	HRESULT rs = D3DXCreateFont(GameGlobal::GetCurrentDevice(), 50, 30, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, (LPCWSTR) "Arial", &myFont);
	if (!SUCCEEDED(rs))
	{
		return;
	}
	myRect.left = 0;
	myRect.top = GameGlobal::GetHeight()/2;
	myRect.bottom = myRect.top + GameGlobal::GetHeight() / 2;
	myRect.right = myRect.left + GameGlobal::GetWidth();
	
}


void BossScene::Update(float dt)
{
	CheckCameraAndWorldMap();
	checkCollision();
	mPlayer->HandleKeyboard(keys);

	mPlayer->Update(dt);
	if (isEnd)
	{
		ResourceManager::GetInstance()->stopSound("BossTheme");
		if (mPlayer->mCurrentState != PlayerState::Standing)
		{
			mPlayer->SetState(new PlayerStandingState(mPlayer->mPlayerData));

		}
		SceneManager::GetInstance()->ReplaceScene(new GameEnd());

	}

	mUI->Update();

	EatItem->Update(1);

	if (EatItem->GetCurrentFrame() == 3)
	{
		EatItem->SetPosition(0, 0);
	}

	Damage->Update(1);
	if (Damage->GetCurrentFrame() == 14)
	{

		Damage->SetPosition(0, 0);
	}


	mBoss->Update();

	AppleObjectHandle();

	if (mBoss->HPCount == 3) isEnd = true;
	
}

void BossScene::Draw()
{

	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x, GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y); //Lay TranSition hien tai
	mMap->Draw(); //Ve Map
	if (!isEnd)
	{
		mBoss->Draw(trans);
	}
	
	mPlayer->Draw();


	EatItem->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
	Damage->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);

	app1->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
	app2->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
	app3->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
	mUI->Draw();
}
void BossScene::CheckCameraAndWorldMap()
{
	mCamera->SetPosition(mPlayer->GetPosition());

	if (mCamera->GetBound().left < 0)
	{
		//vi position cua camera ma chinh giua camera
		//luc nay o vi tri goc ben trai cua the gioi thuc
		mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().right > mMap->GetWidth())
	{
		//luc nay cham goc ben phai cua the gioi thuc
		mCamera->SetPosition(mMap->GetWidth() - mCamera->GetWidth() / 2,
			mCamera->GetPosition().y);
	}

	if (mCamera->GetBound().top < 0)
	{
		//luc nay cham goc tren the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetHeight() / 2);
	}

	if (mCamera->GetBound().bottom > mMap->GetHeight())
	{
		//luc nay cham day cua the gioi thuc
		mCamera->SetPosition(mCamera->GetPosition().x,
			mMap->GetHeight() - mCamera->GetHeight() / 2);
	}
}
void BossScene::OnKeyUp(int keyCode)
{
	if (isEnd) return;
	keys[keyCode] = false;
	mPlayer->OnKeyUp(keyCode);

}
void BossScene::OnKeyDown(int keyCode)
{
	if (isEnd) return;
	keys[keyCode] = true;
	mPlayer->OnKeyPressed(keyCode);
}
Entity *lastFire = NULL;

void BossScene::checkCollision()
{
	//Check apple va cham voi map
	for (int i = 0; i < mPlayer->listWeapon.size(); i++)
	{
		mPlayer->listWeapon.at(i)->Update(0);
		if (mPlayer->listWeapon.at(i)->mCurrentAnim == nullptr || mPlayer->listWeapon.at(i)->curState == nullptr) continue;
		vector<Entity*> listCollisionApple;
		mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionApple, mPlayer->listWeapon.at(i));

		for (size_t j = 0; j < listCollisionApple.size(); j++)
		{
			if (listCollisionApple.at(j)->Tag == Entity::box) continue;
			Entity::CollisionReturn re = GameCollision::RecteAndRect(mPlayer->listWeapon.at(i)->GetBound(),
				listCollisionApple.at(j)->GetBound());
			if (re.IsCollided)
			{
				Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, re);
				//Xu ly va cham thang tao o day
				mPlayer->listWeapon.at(i)->OnCollision(listCollisionApple.at(j), re, sidePlayer);


			}
		}
	}

	//Check Apple vs Boss
	for (int i = 0; i < mPlayer->listWeapon.size(); i++)
	{
		if (mPlayer->listWeapon.at(i)->mCurrentAnim == nullptr || mPlayer->listWeapon.at(i)->curState == nullptr) continue;
		Entity::CollisionReturn re = GameCollision::RecteAndRect(mPlayer->listWeapon.at(i)->GetBound(),
			mBoss->GetBound());
		if (re.IsCollided)
		{
			if (mPlayer->listWeapon.at(i)->GetCurrentState() == WeaponState::Breaking) continue;
			Damage->Reset();
			Damage->SetPosition(mPlayer->listWeapon.at(i)->GetPosition());
			mBoss->OnCollision(mPlayer->listWeapon.at(i), re, Entity::NotKnow);
			/*if(mBoss->mCurrentState == BossState::StandHuman || mBoss->mCurrentState == BossState::JafarAttack)
			mBoss->SetState(new BossStandHuman(mBoss->mData));*/
			mPlayer->listWeapon.at(i)->OnCollision(mBoss, re, Entity::NotKnow);
		}
	}

	//Check Fire Ammo With object
	for (int i = 0; i < mBoss->listFireBurn.size(); i++)
	{
		vector<Entity*> listCollision;
		mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mBoss->listFireBurn.at(i));

		for (int j = 0; j < listCollision.size(); j++)
		{
			Entity::CollisionReturn r = GameCollision::RecteAndRect(mBoss->listFireBurn.at(i)->GetBound(),
				listCollision.at(j)->GetBound());
			if (r.IsCollided)
			{

				mBoss->listFireBurn.at(i)->OnCollision(listCollision.at(j), r, Entity::NotKnow);
			}
		}
	}
	//Check Fire Ammo With Player
	for (int i = 0; i < mBoss->listFireBurn.size(); i++)
	{
		Entity::CollisionReturn r = GameCollision::RecteAndRect(mBoss->listFireBurn.at(i)->GetBound(),
			mPlayer->GetBound());
		if (r.IsCollided)
		{
			if (mBoss->listFireBurn.at(i) == lastFire || !mBoss->listFireBurn.at(i)->isActive) continue;
			mPlayer->SetState(new PlayerFiredState(mPlayer->mPlayerData));
			lastFire = mBoss->listFireBurn.at(i);
		}
	}

#pragma region Check AppleObject with Player
	Entity::CollisionReturn App1 = GameCollision::RecteAndRect(mPlayer->GetBound(),
		app1->GetBound());
	if (App1.IsCollided)
	{
	
		mPlayer->AppleCount++;
		EatItem->Reset();
		EatItem->SetPosition(app1->GetPosition());
		app1->OnCollision(NULL, App1, Entity::NotKnow);


	}

	Entity::CollisionReturn App2 = GameCollision::RecteAndRect(mPlayer->GetBound(),
		app2->GetBound());
	if (App2.IsCollided)
	{
		EatItem->Reset();
		EatItem->SetPosition(app2->GetPosition());
		mPlayer->AppleCount++;
		app2->OnCollision(NULL, App2, Entity::NotKnow);
		
	}

	Entity::CollisionReturn App3 = GameCollision::RecteAndRect(mPlayer->GetBound(),
		app3->GetBound());
	if (App3.IsCollided)
	{
		EatItem->Reset();
		EatItem->SetPosition(app3->GetPosition());
		mPlayer->AppleCount++;
		app3->OnCollision(NULL, App3, Entity::NotKnow);
		
	}
#pragma endregion
	
#pragma region player va cham voi object
	//Check player va cham voi object
	int widthBottom = 0;
	Entity::EntityTypes tag = Entity::None;
	vector<Entity*> listCollision;
	
	mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mPlayer);

	for (size_t i = 0; i < listCollision.size(); i++)
	{

		Entity::CollisionReturn r = GameCollision::RecteAndRect(mPlayer->GetBound(),
			listCollision.at(i)->GetBound());
		if (r.IsCollided)
		{

			//lay phia va cham cua Entity so voi Player
			Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, r);
			
			if (listCollision.at(i)->Tag==Entity::box && sidePlayer != Entity::Bottom && sidePlayer != Entity::BottomLeft && sidePlayer != Entity::BottomLeft) return;
			//lay phia va cham cua Player so voi Entity
			Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollision.at(i), r);

			//goi den ham xu ly collision cua Player va Entity
			if (listCollision.at(i)->Tag == Entity::AppleObject)
			{
				mPlayer->AppleCount++;
				EatItem->SetPosition(listCollision.at(i)->GetPosition());
			}
			else if (listCollision.at(i)->Tag == Entity::Heart)
			{
				mPlayer->HPCount += 5;
				EatItem->SetPosition(listCollision.at(i)->GetPosition());
			}
			


			listCollision.at(i)->OnCollision(mPlayer, r, sideImpactor);
			//Check táo trùng để cộng 

			if (listCollision.at(i)->Tag == Entity::CheckPoint && mPlayer->mCurrentState != PlayerState::Falling)
			{
				mPlayer->CheckPoint = D3DXVECTOR2(listCollision.at(i)->GetPosition().x + 10, listCollision.at(i)->GetPosition().y + 15);
				return;
			}



			mPlayer->OnCollision(listCollision.at(i), r, sidePlayer);
			//kiem tra neu va cham voi phia duoi cua Player 
			if (sidePlayer == Entity::Bottom || sidePlayer == Entity::BottomLeft
				|| sidePlayer == Entity::BottomRight)
			{
				//kiem cha do dai ma mario tiep xuc phia duoi day
				int bot = r.RegionCollision.right - r.RegionCollision.left;

				if (bot > widthBottom)
					widthBottom = bot;
			}
			tag = listCollision.at(i)->Tag;

		}
	}
#pragma endregion

	
	if (mPlayer->getState() == PlayerState::Revive) return;
	if (widthBottom <20)
	{
		mPlayer->OnNoCollisionWithBottom();
	}
}

void BossScene::AppleObjectHandle()
{
	
	if ((GetTickCount()-lastTime)/1000.0f >=10.0f)
	{
		int a = rand() %4 + 1;

		app1->SetPos(mMap->listPosApp1.at(a - 1).x, mMap->listPosApp1.at(a - 1).y);
		app2->SetPos(mMap->listPosApp2.at(a - 1).x, mMap->listPosApp2.at(a - 1).y);
		app3->SetPos(mMap->listPosApp3.at(a - 1).x, mMap->listPosApp3.at(a - 1).y);
		lastTime = GetTickCount();
	}

}