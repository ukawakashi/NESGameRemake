#include "MainScene.h"

MainScene::MainScene()
{
	LoadContent();
	mDieScene = new DieScene(this);
}


ManThrowBowl* Bowl1;
ManThrowBowl* Bowl2;
Peddler1* Pedder;
Enemy1* enemy1;
Enemy2* enemy2;
Enemy3* enemy3;
Enemy4* enemy4;
Enemy5* enemy5;

FlagPole *cb;
float CurTime = 0;

MainScene::~MainScene()
{
}

vector<Rect> LoadEatItem()
{
	vector<Rect> listSourceRect;
	listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "EatItem");
	return listSourceRect;
}
vector<Rect> LoadFired() {
	vector<Rect> list;
	list = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLJafar(), "AroundFire");
	return list;
}
void MainScene::LoadContent()
{
	//set mau backcolor cho scene o day la mau xanh
	mBackColor = 0x54acd2;
	GameGlobal();

	//Choi nhac nen
	ResourceManager::GetInstance()->playSound("AgrabahMarket", true, 0);

	mMap = new GameMap("Resources/AgrabahMarket.tmx");

	mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
	mCamera->SetPosition(GameGlobal::GetWidth() / 2,
		mMap->GetHeight() - mCamera->GetHeight());

	mMap->SetCamera(mCamera);
	EatItem = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 4, LoadEatItem(), (float)1 / 0.5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	EatItem->SetScale(D3DXVECTOR2(2, 2));
	EatItem->SetPosition(0, 0);

	Fired1 = new Animation(ResourceManager::GetInstance()->GetTextureBossJafar(), 5, LoadFired(), (float)1 / 0.5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(186, 254, 202));
	Fired1->SetScale(D3DXVECTOR2(0.7, 0.7));
	Fired1->SetPosition(0, 0);

	Fired2 = new Animation(ResourceManager::GetInstance()->GetTextureBossJafar(), 5, LoadFired(), (float)1 / 0.5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(186, 254, 202));
	Fired2->SetScale(D3DXVECTOR2(0.7, 0.7));
	Fired2->SetPosition(0, 0);


	mPlayer = new Player();
	mPlayer->SetPosition(200,600);
	//mPlayer->SetPosition(3200, 600);
	//mPlayer->SetPosition(4700,200);//Toa do boss


	mPlayer->endStair1 = mMap->endStair1;
	mPlayer->endStair2 = mMap->endStair2;
	mPlayer->startStair1 = mMap->startStair1;
	mPlayer->startStair2 = mMap->startStair2;


	mPlayer->SetCamera(mCamera);

	Bowl1 = new ManThrowBowl(mMap->listBowlPosition1); // Truyen list cho bowl1
	Bowl2 = new ManThrowBowl(mMap->listBowlPosition2);// Truyen list cho bowl2
	Pedder = new Peddler1(mMap->listPeddlerPosition1);

	enemy1 = new Enemy1(mPlayer, mMap->listEnemy1Position);
	enemy2 = new Enemy2(mPlayer, mMap->listEnemy2Position);
	enemy3 = new Enemy3(mPlayer, mMap->listEnemy3Position);
	enemy4 = new Enemy4(mMap->listEnemy4Position);
	enemy5 = new Enemy5(mPlayer, mMap->listEnemy5Position);
	enemy4->mPlayer = mPlayer;
	Bowl1->mPlayer = mPlayer;
	Bowl2->mPlayer = mPlayer;
	Pedder->mPlayer = mPlayer;
	mUI = new UI(mPlayer);


}

void MainScene::Update(float dt)
{
	if (mPlayer->HPCount == 0)
	{
		mPlayer->PlayerLiveCount--;
		if (mPlayer->PlayerLiveCount >= 0)
		{
			CurTime = mUI->CurTime;
			mDieScene->die->Reset();
			SceneManager::GetInstance()->ReplaceScene(mDieScene);
			OnKeyUp(lastKey);
		}
		else {
			SceneManager::GetInstance()->ReplaceScene(new MenuScene());
		}
	}
	checkCollision(); //Check va cham giua cac vat the
	if (mPlayer->HPCount == 0)
	{
		CurTime = mUI->CurTime;
		mDieScene->die->Reset();
		SceneManager::GetInstance()->ReplaceScene(mDieScene);
		OnKeyUp(lastKey);
	}

	if (mPlayer->GetPosition().x >= 4702 && mPlayer->GetPosition().y <= 226)
	{
		ResourceManager::GetInstance()->stopSound("AgrabahMarket");
		SceneManager::GetInstance()->ReplaceScene(new LevelCompleteScene(mPlayer, mUI));
	}
	mPlayer->HandleKeyboard(keys); //Xu ly ban phim cho player
	mPlayer->Update(dt); //Update player

	if (mPlayer->mCurrentState == PlayerState::Revive && mPlayer->GetCurrentAnimation()->GetCurrentFrame() == 1) mUI->CurTime = CurTime;


	CheckCameraAndWorldMap(); //Check camera vuot bien cua map

	for (int i = 0; i < mMap->listCamel.size(); i++) //Update con Lac Da
	{
		mMap->listCamel.at(i)->Update();
	}
	for (int i = 0; i < mMap->listAppleObject.size(); i++) //Update Tao Object
	{
		mMap->listAppleObject.at(i)->Update();
	}
	for (int i = 0; i < mMap->listFlagPole.size(); i++) //Update Cay Bung
	{
		mMap->listFlagPole.at(i)->Update();
	}

	for (int i = 0; i < mMap->listCheckPointSite.size(); i++) //Update CheckPoint
	{
		mMap->listCheckPointSite.at(i)->Update();
	}
	for (int i = 0; i < mMap->listRedRock.size(); i++) //Update CheckPoint
	{
		mMap->listRedRock.at(i)->Update();
	}
	for (int i = 0; i < mMap->listGenieBonus.size(); i++) //Update CheckPoint
	{
		mMap->listGenieBonus.at(i)->Update();
	}
	for (int i = 0; i < mMap->listAbuBonus.size(); i++) //Update CheckPoint
	{
		mMap->listAbuBonus.at(i)->Update();
	}

	Bowl1->Update(mPlayer);
	Bowl2->Update(mPlayer);
	Pedder->Update(mPlayer);

	for (int i = 0; i < mMap->listDropBrick.size(); i++) //Update DropBrick
	{
		mMap->listDropBrick.at(i)->Update();
	}


	enemy1->Update();
	enemy2->Update();
	enemy3->Update();
	enemy4->Update(mPlayer);
	enemy5->Update();

	EatItem->Update(1);
	if (EatItem->GetCurrentFrame() == 3) EatItem->SetPosition(0, 0);

	Fired1->Update(1);
	if (Fired1->GetCurrentFrame() == 3) Fired1->SetPosition(0, 0);

	Fired2->Update(1);
	if (Fired2->GetCurrentFrame() == 3) Fired2->SetPosition(0, 0);

	mUI->Update();


}

void MainScene::Draw()
{
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x, GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y); //Lay TranSition hien tai
	mMap->Draw(); //Ve Map
	Pedder->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans, 0, D3DXVECTOR2(), D3DXCOLOR());
	mPlayer->Draw(); //Ve Player


	Bowl1->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans, 0, D3DXVECTOR2(), D3DXCOLOR());
	Bowl2->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans, 0, D3DXVECTOR2(), D3DXCOLOR());

	for (int i = 0; i < mMap->listDropBrick.size(); i++) //Draw DropBrick
	{
		mMap->listDropBrick.at(i)->Draw(trans, D3DXVECTOR2());
	}
	for (int i = 0; i < mMap->listFlagPole.size(); i++) //
	{
		mMap->listFlagPole.at(i)->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(1, 1), trans);
	}


	for (int i = 0; i < mMap->listCheckPointSite.size(); i++) //Draw CheckPoint
	{
		mMap->listCheckPointSite.at(i)->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(1, 1), trans);
	}

	enemy1->Draw(trans);
	enemy2->Draw(trans);
	enemy3->Draw(trans);
	enemy4->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans, 0, D3DXVECTOR2(), D3DXCOLOR());
	enemy5->Draw(trans);
	mMap->DrawFront(); //Ve mat truoc cua Map
	EatItem->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
	Fired1->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
	Fired2->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
	mUI->Draw(); // Ve UI tren tat ca
}

void MainScene::OnKeyDown(int keyCode)
{
	keys[keyCode] = true;
	if (keyCode != VK_NUMPAD5) lastKey = keyCode;

	if (keyCode == VK_NUMPAD5)
	{
		mPlayer->HPCount = 0;
		CurTime = mUI->CurTime;
		SceneManager::GetInstance()->ReplaceScene(mDieScene);

	}
	if (keyCode == VK_UP)
		CheckUp = true;


	mPlayer->OnKeyPressed(keyCode);






}

void MainScene::OnKeyUp(int keyCode)
{

	keys[keyCode] = false;
	mPlayer->OnKeyUp(keyCode);


}

void MainScene::OnMouseDown(float x, float y)
{
}
void MainScene::CheckCameraAndWorldMap()
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


void MainScene::checkCollision()
{
	Entity::EntityTypes tag = Entity::None;




#pragma region -Check Collision Enemy1-
	//Check Enemy1 vs Player
	Entity::CollisionReturn re = GameCollision::RecteAndRect(enemy1->GetBound(), mPlayer->GetBound());
	if (re.IsCollided)
	{
		enemy1->OnCollision(mPlayer, re, Entity::NotKnow);
	}

	//Check Apple va cham voi Enemy
	for (int i = 0; i < mPlayer->listWeapon.size(); i++)
	{

		Entity::CollisionReturn re = GameCollision::RecteAndRect(mPlayer->listWeapon.at(i)->GetBound(), enemy1->GetBound());

		if (re.IsCollided)
		{

			enemy1->OnCollision(mPlayer->listWeapon.at(i), re, Entity::NotKnow);
			mPlayer->listWeapon.at(i)->OnCollision(enemy1, re, Entity::NotKnow);
		}
	}
#pragma endregion


#pragma region -Check Collision Enemy2-
	//Check Enemy2 vs Player
	Entity::CollisionReturn re1 = GameCollision::RecteAndRect(enemy2->GetBound(), mPlayer->GetBound());
	if (re1.IsCollided)
	{
		enemy2->OnCollision(mPlayer, re1, Entity::NotKnow);
	}

	//Check Apple va cham voi Enemy
	for (int i = 0; i < mPlayer->listWeapon.size(); i++)
	{

		Entity::CollisionReturn re1 = GameCollision::RecteAndRect(mPlayer->listWeapon.at(i)->GetBound(), enemy2->GetBound());

		if (re1.IsCollided)
		{

			enemy2->OnCollision(mPlayer->listWeapon.at(i), re1, Entity::NotKnow);
			mPlayer->listWeapon.at(i)->OnCollision(enemy2, re1, Entity::NotKnow);
		}
	}




#pragma region -Check Collision Enemy3-
	//Check Enemy3 vs Player
	Entity::CollisionReturn re3 = GameCollision::RecteAndRect(enemy3->GetBound(),
		mPlayer->GetBound());
	if (re3.IsCollided)
	{
		enemy3->OnCollision(mPlayer, re3, Entity::NotKnow);
	}

	//Check Apple va cham voi Enemy
	for (int i = 0; i < mPlayer->listWeapon.size(); i++)
	{

		Entity::CollisionReturn re1 = GameCollision::RecteAndRect(mPlayer->listWeapon.at(i)->GetBound(), enemy3->GetBound());

		if (re1.IsCollided)
		{

			enemy3->OnCollision(mPlayer->listWeapon.at(i), re1, Entity::NotKnow);
			mPlayer->listWeapon.at(i)->OnCollision(enemy3, re1, Entity::NotKnow);
		}
	}


	Entity::CollisionReturn Split_En3 = GameCollision::RecteAndRect(mPlayer->mSplit->GetBound(), enemy3->GetBound());

	if (Split_En3.IsCollided)
	{

		enemy3->OnCollision(mPlayer->mSplit, Split_En3, Entity::NotKnow);
		mPlayer->mSplit->OnCollision(enemy3, Split_En3, Entity::NotKnow);
	}
	//Check Knife Enemy3 with Map Object
	vector<Entity*> listCollisionKnife;
	mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionKnife, enemy3->mKnife);
	for (int i = 0; i < listCollisionKnife.size(); i++)
	{
		Entity::CollisionReturn re = GameCollision::RecteAndRect(enemy3->mKnife->GetBound(),
			listCollisionKnife.at(i)->GetBound());
		if (re.IsCollided)
			enemy3->mKnife->OnCollision(listCollisionKnife.at(i), re, Entity::NotKnow);
	}

	//Check Knife Enemy3 with Player
	if (enemy3->mKnife->GetCurrentState() == WeaponState::Flying)
	{
		Entity::CollisionReturn re = GameCollision::RecteAndRect(enemy3->mKnife->GetBound(),
			mPlayer->GetBound());
		if (re.IsCollided)
		{
			enemy3->mKnife->OnCollision(mPlayer, re, Entity::NotKnow);

			mPlayer->OnCollision(enemy3->mKnife, re, Entity::NotKnow);
		}

	}





#pragma endregion
#pragma region - Check Collision Enemy4 Knife
	//Check Coliison with Object Map
	vector<Entity*> listCollisionKnife4;
	mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionKnife4, enemy4->mCurrentKnife);
	for (int i = 0; i < listCollisionKnife4.size(); i++)
	{
		Entity::CollisionReturn re = GameCollision::RecteAndRect(enemy4->mCurrentKnife->GetBound(),
			listCollisionKnife4.at(i)->GetBound());
		if (re.IsCollided)
		{
			enemy4->mCurrentKnife->OnCollision(listCollisionKnife4.at(i), re, Entity::NotKnow);
		}
	}

	//Check Knife Collision with Player
	Entity::CollisionReturn reEnemy3 = GameCollision::RecteAndRect(enemy4->mCurrentKnife->GetBound(),
		mPlayer->GetBound());
	if (reEnemy3.IsCollided && enemy4->mCurrentKnife->GetCurrentState() == WeaponState::Flying)
	{
		enemy4->mCurrentKnife->OnCollision(mPlayer, re, Entity::NotKnow);
		mPlayer->OnCollision(enemy4->mCurrentKnife, re, Entity::NotKnow);
	}

	//Check Fight with Player
	Entity::CollisionReturn reEnemy4 = GameCollision::RecteAndRect(enemy4->GetBound(),
		mPlayer->GetBound());
	if (reEnemy4.IsCollided)
	{

		enemy4->OnCollision(mPlayer, re, Entity::NotKnow);
		//mPlayer->OnCollision(enemy4->mCurrentKnife, re, Entity::NotKnow);
	}

	//Check with Apple
	for (int i = 0; i < mPlayer->listWeapon.size(); i++)
	{

		Entity::CollisionReturn re = GameCollision::RecteAndRect(mPlayer->listWeapon.at(i)->GetBound(), enemy4->GetBound());

		if (re.IsCollided)
		{

			enemy4->OnCollision(mPlayer->listWeapon.at(i), re, Entity::NotKnow);
			mPlayer->listWeapon.at(i)->OnCollision(enemy4, re, Entity::NotKnow);
		}
	}
#pragma endregion

#pragma region -Check Collision Enemy5-
	//Check Enemy5 vs Player
	Entity::CollisionReturn re_enemy5 = GameCollision::RecteAndRect(enemy5->GetBound(),
		mPlayer->GetBound());
	if (re_enemy5.IsCollided)
	{
		enemy5->OnCollision(mPlayer, re_enemy5, Entity::NotKnow);
	}

	//Check Apple va cham voi Enemy
	for (int i = 0; i < mPlayer->listWeapon.size(); i++)
	{

		Entity::CollisionReturn re_enemy51 = GameCollision::RecteAndRect(mPlayer->listWeapon.at(i)->GetBound(), enemy5->GetBound());

		if (re_enemy51.IsCollided)
		{

			enemy5->OnCollision(mPlayer->listWeapon.at(i), re_enemy51, Entity::NotKnow);
			mPlayer->listWeapon.at(i)->OnCollision(enemy5, re_enemy51, Entity::NotKnow);
		}
	}




#pragma endregion
	//Check player vs DropBrick
	for (int i = 0; i < mMap->listDropBrick.size(); i++)
	{

		Entity::CollisionReturn re = GameCollision::RecteAndRect(mMap->listDropBrick.at(i)->GetBound(),
			mPlayer->GetBound());
		if (re.IsCollided)
		{
			Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, re);
			mMap->listDropBrick.at(i)->OnCollision(mPlayer, re, Entity::NotKnow);
			mPlayer->OnCollision(mMap->listDropBrick.at(i), re, sidePlayer);
			tag = Entity::BrickDrop;

		}

	}

	//Check Apple va cham voi object
	for (int i = 0; i < mPlayer->listWeapon.size(); i++)
	{
		mPlayer->listWeapon.at(i)->Update(0);
		if (mPlayer->listWeapon.at(i)->mCurrentAnim == nullptr || mPlayer->listWeapon.at(i)->curState == nullptr) continue;
		vector<Entity*> listCollisionApple;
		mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionApple, mPlayer->listWeapon.at(i));

		for (size_t j = 0; j < listCollisionApple.size(); j++)
		{
			if (listCollisionApple.at(j)->Tag != Entity::EntityTypes::Land && listCollisionApple.at(j)->Tag != Entity::EntityTypes::LandWood
				&& listCollisionApple.at(j)->Tag != Entity::EntityTypes::Wall)
				continue;

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





	//Check bowl Collision voi Map

	if (Bowl1->mCurrentWeapon->GetCurrentState() != WeaponState::NONE)
	{
		vector<Entity*> listCollisionWithBowl;
		mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionWithBowl, Bowl1->mCurrentWeapon);

		for (size_t i = 0; i < listCollisionWithBowl.size(); i++)
		{
			if (listCollisionWithBowl.at(i)->Tag == Entity::AppleObject) continue;
			Entity::CollisionReturn r = GameCollision::RecteAndRect(Bowl1->mCurrentWeapon->GetBound(),
				listCollisionWithBowl.at(i)->GetBound());
			if (r.IsCollided)
				Bowl1->mCurrentWeapon->OnCollision(listCollisionWithBowl.at(i), r, Entity::NotKnow);
		}
	}


	if (Bowl2->mCurrentWeapon->GetCurrentState() != WeaponState::NONE)
	{
		vector<Entity*> listCollisionWithBowl;
		mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionWithBowl, Bowl2->mCurrentWeapon);

		for (size_t i = 0; i < listCollisionWithBowl.size(); i++)
		{
			if (listCollisionWithBowl.at(i)->Tag == Entity::AppleObject) continue;
			Entity::CollisionReturn r = GameCollision::RecteAndRect(Bowl2->mCurrentWeapon->GetBound(),
				listCollisionWithBowl.at(i)->GetBound());
			if (r.IsCollided)
				Bowl2->mCurrentWeapon->OnCollision(listCollisionWithBowl.at(i), r, Entity::NotKnow);
		}
	}

	//Check bowl Collision voi Player
	if (Bowl1->mCurrentWeapon->GetCurrentState() == WeaponState::Flying)
	{
		Entity::CollisionReturn r = GameCollision::RecteAndRect(Bowl1->mCurrentWeapon->GetBound(), mPlayer->GetBound());
		if (r.IsCollided)
		{
			mPlayer->OnCollision(Bowl1->mCurrentWeapon, r, Entity::NotKnow);
			Bowl1->mCurrentWeapon->OnCollision(mPlayer, r, Entity::NotKnow);
		}
	}

	if (Bowl2->mCurrentWeapon->GetCurrentState() == WeaponState::Flying)
	{
		Entity::CollisionReturn r = GameCollision::RecteAndRect(Bowl2->mCurrentWeapon->GetBound(), mPlayer->GetBound());
		if (r.IsCollided)
		{
			mPlayer->OnCollision(Bowl2->mCurrentWeapon, r, Entity::NotKnow);
			Bowl2->mCurrentWeapon->OnCollision(mPlayer, r, Entity::NotKnow);
		}
	}
	//Peddler va cham voi Player
	/*Entity::CollisionReturn r = GameCollision::RecteAndRect(Pedder->GetBound(), mPlayer->GetBound());
	if (r.IsCollided)
	{
		mPlayer->OnCollision(Bowl1->mCurrentWeapon, r, Entity::NotKnow);
		Pedder->OnCollision(mPlayer, r, Entity::NotKnow);
	}*/
	//Check Bowl1 va cham Player
	Entity::CollisionReturn r1 = GameCollision::RecteAndRect(Bowl1->GetBound(),
		mPlayer->GetBound());
	if (r1.IsCollided)
	{

		Bowl1->OnCollision(mPlayer, re, Entity::NotKnow);
	}
	//va cham tao
	for (int i = 0; i < mPlayer->listWeapon.size(); i++)
	{
		Entity::CollisionReturn r1 = GameCollision::RecteAndRect(mPlayer->listWeapon.at(i)->GetBound(), Bowl1->GetBound());

		if (r1.IsCollided)
		{

			Bowl1->OnCollision(mPlayer->listWeapon.at(i), re, Entity::NotKnow);
			mPlayer->listWeapon.at(i)->OnCollision(Bowl1, re, Entity::NotKnow);
		}
	}

	//////////Cua bowl2
	//Check Bowl2 va cham Player
	Entity::CollisionReturn r2 = GameCollision::RecteAndRect(Bowl2->GetBound(),
		mPlayer->GetBound());
	if (r2.IsCollided)
	{

		Bowl2->OnCollision(mPlayer, re, Entity::NotKnow);
	}
	///Va cham tao
	for (int i = 0; i < mPlayer->listWeapon.size(); i++)
	{

		Entity::CollisionReturn r2 = GameCollision::RecteAndRect(mPlayer->listWeapon.at(i)->GetBound(), Bowl2->GetBound());

		if (r2.IsCollided)
		{

			Bowl2->OnCollision(mPlayer->listWeapon.at(i), re, Entity::NotKnow);
			mPlayer->listWeapon.at(i)->OnCollision(Bowl2, re, Entity::NotKnow);
		}
	}


	/*su dung de kiem tra xem khi nao mario khong dung tren 1 object hoac
	dung qua sat mep trai hoac phai cua object do thi se chuyen state la falling*/
	int widthBottom = 0;

	vector<Entity*> listCollision;
	//Check player va cham voi object
	mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mPlayer);

	for (size_t i = 0; i < listCollision.size(); i++)
	{

		Entity::CollisionReturn r = GameCollision::RecteAndRect(mPlayer->GetBound(),
			listCollision.at(i)->GetBound());
		if (r.IsCollided)
		{

			//lay phia va cham cua Entity so voi Player
			Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, r);
			//lay phia va cham cua Player so voi Entity
			Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollision.at(i), r);

			//goi den ham xu ly collision cua Player va Entity
			if (listCollision.at(i)->Tag == Entity::AppleObject)
			{
				mPlayer->Score += 10;
				mPlayer->AppleCount++;
				EatItem->SetPosition(listCollision.at(i)->GetPosition());
				Sound::getInstance()->play("AladdinEatApple", false, 1);
			}
			else if (listCollision.at(i)->Tag == Entity::Heart)
			{
				mPlayer->Score += 50;
				mPlayer->HPCount += 5;
				EatItem->SetPosition(listCollision.at(i)->GetPosition());
				Sound::getInstance()->play("AladdinEatHealth", false, 1);

			}
			else if (listCollision.at(i)->Tag == Entity::Lamp)
			{
				EatItem->SetPosition(listCollision.at(i)->GetPosition());
				Sound::getInstance()->play("AladdinEatLamp", false, 1);

				//if (enemy3->isInCamera(mCamera))
					//enemy3->Heal = 0;
				if (enemy3->GetPosition().x < 2000 && enemy3->GetPosition().x>1770 && enemy3->GetPosition().y > 290 && enemy3->GetPosition().y < 466)
					enemy3->Heal = 0;
				if (enemy4->GetPosition().x < 2700 && enemy3->GetPosition().x>2360 && enemy3->GetPosition().y > 400 && enemy3->GetPosition().y < 620) {
					enemy4->HP = 0;
				}
				if (enemy3->GetPosition().x < 3050 && enemy3->GetPosition().x>2927 && enemy3->GetPosition().y > 330 && enemy3->GetPosition().y < 480) {
					enemy3->Heal = 0;
				}
				//if (Bowl1->isInCamera(mCamera))
					//Bowl1->HP = 0;
				//if (Bowl2->isInCamera(mCamera))
					//Bowl2->HP = 0;
				//Sound::getInstance()->play("AladdinEatHealth", false, 1);//Thiếu Sound

			}
			else if (listCollision.at(i)->Tag == Entity::_1Up)
			{
				mPlayer->Score += 100;
				mPlayer->PlayerLiveCount++;
				EatItem->SetPosition(listCollision.at(i)->GetPosition());
				Sound::getInstance()->play("AladdinEatLive", false, 1);
			}
			else if (listCollision.at(i)->Tag == Entity::RedRock)
			{
				mPlayer->Score += 20;
				mPlayer->RockCount++;
				EatItem->SetPosition(listCollision.at(i)->GetPosition());
				Sound::getInstance()->play("AladdinEatRock", false, 1);
			}
			else if (listCollision.at(i)->Tag == Entity::GenieBonus)
			{
				mPlayer->Score += 300;
				mPlayer->haveGenieBonus++;
				EatItem->SetPosition(listCollision.at(i)->GetPosition());
				Sound::getInstance()->play("AladdinEatBonus", false, 1);
			}
			else if (listCollision.at(i)->Tag == Entity::AbuBonus)
			{
				mPlayer->Score += 400;
				mPlayer->haveAbuBonus = true;
				EatItem->SetPosition(listCollision.at(i)->GetPosition());
				Sound::getInstance()->play("AladdinEatBonus", false, 1);
			}


			else if (CheckUp && mPlayer->GetPosition().x < 3905 && mPlayer->GetPosition().x>3880 && Pedder->AllowSell2)
				{
					if (mPlayer->RockCount >= 5) {
						mPlayer->RockCount -= 5;
						mPlayer->PlayerLiveCount++;
					}
				
				//EatItem->SetPosition(listCollision.at(i)->GetPosition());
				//Sound::getInstance()->play("AladdinEatBonus", false, 1);
			}
			else if (listCollision.at(i)->Tag == Entity::Camel)
			{
				//if ((sidePlayer == Entity::Bottom || sidePlayer == Entity::BottomRight || sidePlayer == Entity::BottomLeft )
				//	&& sideImpactor == Entity::Top)
				//	//mPlayer->listWeapon.at(2)->SetPosition(listCollision.at(i)->GetPosition().x + 50, listCollision.at(i)->GetPosition().y-50);
				//	//mPlayer->listWeapon.at(2)->SetState(AppleState::Flying);
				//{
				if (mPlayer->GetPosition().y < 640)
				{
					mPlayer->mSplit->SetPosition(listCollision.at(i)->GetPosition().x + 50, listCollision.at(i)->GetPosition().y - 20);
					mPlayer->mSplit->SetState(WeaponState::Flying);
					Sound::getInstance()->play("CamelSpit", false, 1);
				}/*
				else
				{
					mPlayer->mSplit->SetPosition(listCollision.at(i)->GetPosition().x + 50, listCollision.at(i)->GetPosition().y - 20);
					mPlayer->mSplit->SetState(AppleState::Flying);
				}*/
			}
			else if (listCollision.at(i)->Tag == Entity::Fired)
			{
				mPlayer->PlayerLiveCount++;
				Fired1->SetPosition(mPlayer->GetPosition().x - 12, mPlayer->GetPosition().y - 12);
				Fired2->SetPosition(mPlayer->GetPosition().x + 12, mPlayer->GetPosition().y - 12);
				if (mPlayer->mCurrentState != PlayerState::Standing) {
					mPlayer->HPCount--;
					mUI->Update();
					mUI->Draw();
				}
				Sound::getInstance()->play("CoalFire", false, 1);
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


	if (tag == Entity::Rope || tag == Entity::BrickDrop || tag == Entity::flagPole || tag == Entity::stair) return;
	if (mPlayer->getState() == PlayerState::JumpPole ||
		mPlayer->getState() == PlayerState::ClimbingHori ||
		mPlayer->getState() == PlayerState::ThrowClimb ||
		mPlayer->getState() == PlayerState::Revive) return;
	//Neu mario dung ngoai mep thi luc nay cho mario rot xuong duoi dat 
	if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
	{
		mPlayer->OnNoCollisionWithBottom();
	}
}