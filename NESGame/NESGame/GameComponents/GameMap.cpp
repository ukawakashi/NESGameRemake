#include "GameMap.h"

GameMap::GameMap(char* filePath)
{
	LoadMap(filePath);

}


GameMap::~GameMap()
{
	delete mMap;
}
void GameMap::LoadMap(char* filePath)
{
	//Load Sprite cho Apple Object
	Rect rect;
	rect.left = 370; rect.top = 45; rect.right = rect.left + 14; rect.bottom = rect.top + 14;
	Sprite* appleSprite = new Sprite("Resources/Aladdin.png", rect, 0, 0, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5), GameGlobal::mAladdintexture);

	rect.left = 340; rect.top = 170; rect.right = rect.left + 24; rect.bottom = rect.top + 26;
	Sprite* heartSprite = new Sprite("Resources/Items/Items.png", rect, 0, 0, D3DCOLOR_XRGB(248, 0, 248), D3DXVECTOR2(0.5, 0.5), GameGlobal::mItemtexture);

	rect.left = 369; rect.top = 15; rect.right = rect.left + 32; rect.bottom = rect.top + 15;
	Sprite* lampSprite = new Sprite("Resources/Items/Items.png", rect, 0, 0, D3DCOLOR_XRGB(248, 0, 248), D3DXVECTOR2(0.5, 0.5), GameGlobal::mItemtexture);

	rect.left = 367; rect.top = 141; rect.right = rect.left + 24; rect.bottom = rect.top + 23;
	Sprite* UpSprite = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), rect, 0, 0, D3DCOLOR_XRGB(248, 0, 248), D3DXVECTOR2(0.5, 0.5), GameGlobal::mItemtexture);

	vector<Rect> listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLItems(), "rock");
	Animation* redRockAnimate = new Animation(ResourceManager::GetInstance()->GetTextureItems(), 9, listRect, (float)1 / 0.04, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(248, 0, 248), Entity::RedRock);

	listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLItems(), "GenieBonusLevel");
	Animation* GenieAnimate = new Animation(ResourceManager::GetInstance()->GetTextureItems(), 4, listRect, (float)1 / 0.04, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(248, 0, 248), Entity::GenieBonus);

	listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLItems(), "AbuBonusLevel");
	Animation* AbuAnimate = new Animation(ResourceManager::GetInstance()->GetTextureItems(), 10, listRect, (float)1 / 0.04, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(248, 0, 248), Entity::AbuBonus);
	mMap = new Tmx::Map();
	mMap->ParseFile(filePath);

	Rect r;
	r.left = 0;
	r.top = 0;
	r.right = this->GetWidth();
	r.bottom = this->GetHeight();

	mQuadTree = new QuadTree(1, r);

	for (size_t i = 0; i < mMap->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *tileset = mMap->GetTileset(i);

		Sprite *sprite = new Sprite(tileset->GetImage()->GetSource().c_str(), Rect(), 0, 0, D3DCOLOR_XRGB(63, 72, 204), D3DXVECTOR2(0.5, 0.5), GameGlobal::mMaptexture);
		sprite->SetTransColor(D3DCOLOR_XRGB(63, 72, 204));
		mListTileset.insert(std::pair<int, Sprite*>(i, sprite));
	}


#pragma region -OBJECTGROUP, STATIC OBJECT-

	for (size_t i = 0; i < mMap->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *objectGroup = mMap->GetObjectGroup(i);

		Entity::EntityTypes tag = Entity::None;
		string name = objectGroup->GetName();
		if (name == "rope")
			tag = Entity::Rope;
		if (name == "stringhori")
			tag = Entity::StringHori;
		if (name == "land")
			tag = Entity::Land;
		if (name == "landwood")
			tag = Entity::LandWood;
		if (name == "camel")
			tag = Entity::Camel;
		if (name == "apple")
			tag = Entity::AppleObject;
		if (name == "fired")
			tag = Entity::Fired;
		if (name == "stair1")
			tag = Entity::stair1;
		if (name == "stair2")
			tag = Entity::stair2;
		if (name == "heart")
			tag = Entity::Heart;
		if (name == "lamp")
			tag = Entity::Lamp;
		if (name == "stair")
			tag = Entity::stair;
		if (name == "1up")
			tag = Entity::_1Up;
		if (name == "stair")
			tag = Entity::stair;
		if (name == "wall")
			tag = Entity::Wall;
		if (name == "redrock")
			tag = Entity::RedRock;
		if (name == "Genie")
			tag = Entity::GenieBonus;
		if (name == "Abu")
			tag = Entity::AbuBonus;

		for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
		{
			//lay object group chu khong phai layer
			//object group se chua nhung body
			Tmx::Object *object = objectGroup->GetObjects().at(j);

			if (object->GetId() == 459) endStair2 = D3DXVECTOR2(object->GetX(), object->GetY());
			if (object->GetId() == 419) startStair2 = D3DXVECTOR2(object->GetX() + object->GetWidth(), object->GetY() + object->GetHeight());

			if (object->GetId() == 405) startStair1 = D3DXVECTOR2(object->GetX(), object->GetY() + object->GetHeight());
			if (object->GetId() == 252) endStair1 = D3DXVECTOR2(object->GetX() + object->GetWidth(), object->GetY());

			if (tag != Entity::Camel &&
				tag != Entity::Heart &&
				tag != Entity::Lamp &&
				tag != Entity::_1Up &&
				tag != Entity::RedRock&&
				tag != Entity::GenieBonus&&
				tag != Entity::AbuBonus&&
				tag != Entity::AppleObject &&
				name != "dropbrick" &&
				name != "civilianBowl" &&
				name != "civilianBowl2" &&
				name != "peddler" &&
				name != "flagpole" &&
				name != "checkpoint")
			{
				Entity *entity = new Entity();
				entity->SetPosition(object->GetX() + object->GetWidth() / 2,
					object->GetY() + object->GetHeight() / 2);
				entity->SetWidth(object->GetWidth());
				entity->SetHeight(object->GetHeight());
				entity->Tag = tag;
				mQuadTree->insertEntity(entity);

			}


			if (tag == Entity::Camel)
			{
				Camel *camel = new Camel("Resources/camel.png", (float)1 / 10, D3DXVECTOR2(0.5, 1.0));
				camel->SetPos(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				camel->Tag = tag;
				listCamel.push_back(camel);
				mQuadTree->insertEntity(camel);
			}

			if (tag == Entity::Heart)
			{


				AppleObject *heart = new AppleObject(heartSprite);
				heart->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				heart->SetWidth(heart->represent->GetWidth());
				heart->SetHeight(heart->represent->GetHeight());
				heart->Tag = tag;
				listHeart.push_back(heart);
				mQuadTree->insertEntity(heart);
			}
			if (tag == Entity::Lamp)
			{


				AppleObject *lamp = new AppleObject(lampSprite);
				lamp->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				lamp->SetWidth(lamp->represent->GetWidth());
				lamp->SetHeight(lamp->represent->GetHeight());
				lamp->Tag = tag;
				listLamp.push_back(lamp);
				mQuadTree->insertEntity(lamp);
			}
			if (tag == Entity::_1Up)
			{
				AppleObject *_1Up = new AppleObject(UpSprite);
				_1Up->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				_1Up->SetWidth(_1Up->represent->GetWidth());
				_1Up->SetHeight(_1Up->represent->GetHeight());
				_1Up->Tag = tag;
				list1Up.push_back(_1Up);
				mQuadTree->insertEntity(_1Up);
			}
			if (tag == Entity::RedRock)
			{
				AppleObject *redRock = new AppleObject(redRockAnimate);
				redRock->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				redRock->SetWidth(redRock->represent->GetWidth());
				redRock->SetHeight(redRock->represent->GetHeight());
				redRock->Tag = tag;
				listRedRock.push_back(redRock);
				mQuadTree->insertEntity(redRock);
			}
			if (tag == Entity::GenieBonus)
			{
				AppleObject *GenieSprite = new AppleObject(GenieAnimate);
				GenieSprite->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				GenieSprite->SetWidth(GenieSprite->represent->GetWidth());
				GenieSprite->SetHeight(GenieSprite->represent->GetHeight());
				GenieSprite->Tag = tag;
				listGenieBonus.push_back(GenieSprite);
				mQuadTree->insertEntity(GenieSprite);
			}
			if (tag == Entity::AbuBonus)
			{
				AppleObject *AbuSprite = new AppleObject(AbuAnimate);
				AbuSprite->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				AbuSprite->SetWidth(AbuSprite->represent->GetWidth());
				AbuSprite->SetHeight(AbuSprite->represent->GetHeight());
				AbuSprite->Tag = tag;
				listAbuBonus.push_back(AbuSprite);
				mQuadTree->insertEntity(AbuSprite);
			}
			if (tag == Entity::AppleObject)
			{


				AppleObject *apple = new AppleObject(appleSprite);
				apple->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				apple->SetWidth(apple->represent->GetWidth());
				apple->SetHeight(apple->represent->GetHeight());
				apple->Tag = tag;
				listAppleObject.push_back(apple);
				mQuadTree->insertEntity(apple);
			}
			if (name == "flagpole")
			{
				FlagPole* cb = new FlagPole();
				cb->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				cb->SetWidth(60);
				cb->SetHeight(10);
				listFlagPole.push_back(cb);
				mQuadTree->insertEntity(cb);
			}

			if (name == "dropbrick")
			{
				D3DXVECTOR2 pos = D3DXVECTOR2(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				DropBrick *temp = new DropBrick(pos);
				temp->SetWidth(object->GetWidth());
				temp->SetHeight(object->GetHeight());
				listDropBrick.push_back(temp);
			}

			if (name == "civilianBowl")
			{
				D3DXVECTOR2 pos = D3DXVECTOR2(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				listBowlPosition1.push_back(pos);
			}
			if (name == "civilianBowl2")
			{
				D3DXVECTOR2 pos = D3DXVECTOR2(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				listBowlPosition2.push_back(pos);

			}
			if (name == "peddler")
			{
				D3DXVECTOR2 pos = D3DXVECTOR2(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				listPeddlerPosition1.push_back(pos);
			}
			if (name == "enemy1")
			{
				D3DXVECTOR2 pos = D3DXVECTOR2(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				listEnemy1Position.push_back(pos);
			}

			if (name == "enemy2")
			{
				D3DXVECTOR2 pos = D3DXVECTOR2(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				listEnemy2Position.push_back(pos);
			}
			if (name == "enemy3")
			{
				D3DXVECTOR2 pos = D3DXVECTOR2(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				listEnemy3Position.push_back(pos);
			}

			if (name == "enemy4")
			{
				D3DXVECTOR2 pos = D3DXVECTOR2(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				listEnemy4Position.push_back(pos);
			}
			if (name == "enemy5")
			{
				D3DXVECTOR2 pos = D3DXVECTOR2(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				listEnemy5Position.push_back(pos);
			}
			if (name == "checkpoint")
			{
				CheckPointSite* cb = new CheckPointSite();
				cb->SetPosition(object->GetX() + object->GetWidth() / 2, object->GetY() + object->GetHeight() / 2);
				listCheckPointSite.push_back(cb);
				mQuadTree->insertEntity(cb);
			}

		}
	}

#pragma endregion
}

bool GameMap::isContain(RECT rect1, RECT rect2)
{
	if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
	{
		return false;
	}

	return true;
}

Tmx::Map* GameMap::GetMap()
{
	return mMap;
}

int GameMap::GetWidth()
{
	return mMap->GetWidth() * mMap->GetTileWidth();
}

int GameMap::GetHeight()
{
	return mMap->GetHeight() * mMap->GetTileHeight();
}

int GameMap::GetTileWidth()
{
	return mMap->GetTileWidth();
}

int GameMap::GetTileHeight()
{
	return mMap->GetTileHeight();
}
void GameMap::DrawFront()
{
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);

#pragma region DRAW TILESET
	for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mMap->GetTileLayer(i);
		if (layer->GetName() != "Tile Layer 3")
			continue;

		if (!layer->IsVisible())
		{
			continue;
		}

		for (size_t j = 0; j < mMap->GetNumTilesets(); j++)
		{
			const Tmx::Tileset *tileSet = mMap->GetTileset(j);

			Rect sourceRECT;

			int tileWidth = mMap->GetTileWidth();
			int tileHeight = mMap->GetTileHeight();

			int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
			int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

			for (size_t m = 0; m < layer->GetHeight(); m++)
			{
				for (size_t n = 0; n < layer->GetWidth(); n++)
				{
					if (layer->GetTileTilesetIndex(n, m) != -1)
					{
						int tileID = layer->GetTileId(n, m);

						int y = tileID / tileSetWidth;
						int x = tileID - y * tileSetWidth;

						sourceRECT.top = y * tileHeight;
						sourceRECT.bottom = sourceRECT.top + tileHeight;
						sourceRECT.left = x * tileWidth;
						sourceRECT.right = sourceRECT.left + tileWidth;

						Sprite* sprite = mListTileset[j];

						//tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
						//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
						D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

						if (mCamera != NULL)
						{
							RECT objRECT;
							objRECT.left = position.x - tileWidth / 2;
							objRECT.top = position.y - tileHeight / 2;
							objRECT.right = objRECT.left + tileWidth;
							objRECT.bottom = objRECT.top + tileHeight;

							if (!GameCollision::RecteAndRect(mCamera->GetBound(), objRECT).IsCollided)
								continue;
						}

						sprite->SetWidth(tileWidth);
						sprite->SetHeight(tileHeight);

						sprite->Draw(position, sourceRECT, D3DXVECTOR2(), trans);
					}
				}
			}
		}
	}
}

void GameMap::Draw()
{
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);

#pragma region DRAW TILESET
	for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mMap->GetTileLayer(i);
		if (layer->GetName() == "Tile Layer 3")
			continue;

		if (!layer->IsVisible())
		{
			continue;
		}

		for (size_t j = 0; j < mMap->GetNumTilesets(); j++)
		{
			const Tmx::Tileset *tileSet = mMap->GetTileset(j);

			RECT sourceRECT;

			int tileWidth = mMap->GetTileWidth();
			int tileHeight = mMap->GetTileHeight();

			int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
			int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

			for (size_t j = 0; j < mMap->GetNumTilesets(); j++)
			{
				const Tmx::Tileset *tileSet = mMap->GetTileset(j);

				Rect sourceRECT;

				int tileWidth = mMap->GetTileWidth();
				int tileHeight = mMap->GetTileHeight();

				int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
				int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

				for (size_t m = 0; m < layer->GetHeight(); m++)
				{
					for (size_t n = 0; n < layer->GetWidth(); n++)
					{
						if (layer->GetTileTilesetIndex(n, m) != -1)
						{
							int tileID = layer->GetTileId(n, m);

							int y = tileID / tileSetWidth;
							int x = tileID - y * tileSetWidth;

							sourceRECT.top = y * tileHeight;
							sourceRECT.bottom = sourceRECT.top + tileHeight;
							sourceRECT.left = x * tileWidth;
							sourceRECT.right = sourceRECT.left + tileWidth;

							Sprite* sprite = mListTileset[j];

							//tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
							//dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
							D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

							if (mCamera != NULL)
							{
								Rect objRECT;
								objRECT.left = position.x - tileWidth / 2;
								objRECT.top = position.y - tileHeight / 2;
								objRECT.right = objRECT.left + tileWidth;
								objRECT.bottom = objRECT.top + tileHeight;

								if (!GameCollision::RecteAndRect(mCamera->GetBound(), objRECT).IsCollided)
									continue;
							}

							sprite->SetWidth(tileWidth);
							sprite->SetHeight(tileHeight);

							sprite->Draw(position, sourceRECT, D3DXVECTOR2(), trans);
						}
					}
				}
			}
		}
		for (int i = 0; i < listCamel.size(); i++)
		{

			listCamel.at(i)->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
		}
		for (int i = 0; i < listAppleObject.size(); i++)
		{

			listAppleObject.at(i)->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
		}
		for (int i = 0; i < listHeart.size(); i++)
		{

			listHeart.at(i)->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
		}
		for (int i = 0; i < listLamp.size(); i++)
		{

			listLamp.at(i)->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
		}
		for (int i = 0; i < listLamp.size(); i++)
		{

			listLamp.at(i)->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
		}
		for (int i = 0; i < list1Up.size(); i++)
		{

			list1Up.at(i)->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
		}
		for (int i = 0; i < listRedRock.size(); i++)
		{

			listRedRock.at(i)->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
		}
		for (int i = 0; i < listGenieBonus.size(); i++)
		{

			listGenieBonus.at(i)->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
		}
		for (int i = 0; i < listAbuBonus.size(); i++)
		{

			listAbuBonus.at(i)->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
		}

	}
#pragma endregion

}

void GameMap::SetCamera(Camera * camera)
{
	this->mCamera = camera;
}

RECT GameMap::GetWorldMapBound()
{
	RECT bound;
	bound.left = bound.top = 0;
	bound.right = mMap->GetWidth() * mMap->GetTileWidth();
	bound.bottom = mMap->GetHeight() * mMap->GetTileHeight();

	return bound;
}


bool GameMap::IsBoundLeft()
{
	return (mCamera->GetBound().left == 0);
}

bool GameMap::IsBoundRight()
{
	return (mCamera->GetBound().right == this->GetWidth());
}

bool GameMap::IsBoundTop()
{
	return (mCamera->GetBound().top == 0);
}

bool GameMap::IsBoundBottom()
{
	return (mCamera->GetBound().bottom == this->GetHeight());
}

std::map<int, Sprite*> GameMap::getListTileSet()
{
	return mListTileset;
}

QuadTree * GameMap::GetQuadTree()
{
	return mQuadTree;
}
void GameMap::Update(float dt)
{
	for (int i = 0; i < listRedRock.size(); i++)
	{

		listRedRock.at(i)->Update();
	}
	for (int i = 0; i < listGenieBonus.size(); i++)
	{

		listGenieBonus.at(i)->Update();
	}
	for (int i = 0; i < listAbuBonus.size(); i++)
	{

		listAbuBonus.at(i)->Update();
	}
}