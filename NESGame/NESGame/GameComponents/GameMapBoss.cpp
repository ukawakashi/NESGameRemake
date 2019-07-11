#include "GameMapBoss.h"



GameMapBoss::GameMapBoss(string filePath)
{
	LoadMap(filePath);

}


GameMapBoss::~GameMapBoss()
{
	delete mMap;
}
void GameMapBoss::LoadMap(string filePath)
{
	
	mMap = new Tmx::Map();
	mMap->ParseFile(filePath);

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = this->GetWidth();
	r.bottom = this->GetHeight();

	mQuadTree = new QuadTree(1, r);

	for (size_t i = 0; i < mMap->GetNumTilesets(); i++)
	{
		const Tmx::Tileset *tileset = mMap->GetTileset(i);
		Sprite *sprite = new Sprite(tileset->GetImage()->GetSource().c_str(), Rect(), 0, 0, D3DCOLOR_XRGB(63, 72, 204),D3DXVECTOR2(0.5, 0.5), GameGlobal::mMaptexture);
		sprite->SetTransColor(D3DCOLOR_XRGB(63, 72, 204));
		mListTileset.insert(std::pair<int, Sprite*>(i, sprite));
	}


#pragma region -OBJECTGROUP, STATIC OBJECT-

	for (size_t i = 0; i < mMap->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *objectGroup = mMap->GetObjectGroup(i);

		Entity::EntityTypes tag = Entity::None;
		string name = objectGroup->GetName();
		if (name == "box")
			tag = Entity::box;
		if (name == "land")
			tag = Entity::Land;
		if (name == "wall")
				tag = Entity::Wall;

		for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
		{
			//lay object group chu khong phai layer
			//object group se chua nhung body
			
			Tmx::Object *object = objectGroup->GetObjects().at(j);
			
			if (name != "app1" && name != "app2" && name != "app3")
			{
				Entity *entity = new Entity();
				entity->SetPosition(object->GetX() + object->GetWidth() / 2,
					object->GetY() + object->GetHeight() / 2);
				entity->SetWidth(object->GetWidth());
				entity->SetHeight(object->GetHeight());

				if (tag == Entity::Rope)
				{
					float x = object->GetX() + object->GetWidth() / 2;
					float y = object->GetY() + object->GetHeight() / 2;
					float z = object->GetY() + object->GetHeight() / 2;
				}
				entity->Tag = tag;
				mQuadTree->insertEntity(entity);


			}
			
				if (name == "app1")
				{
					listPosApp1.push_back(D3DXVECTOR3(object->GetX() + object->GetWidth() / 2,
						object->GetY() + object->GetHeight() / 2, 0));
				}
				if (name == "app2")
				{
					listPosApp2.push_back(D3DXVECTOR3(object->GetX() + object->GetWidth() / 2,
						object->GetY() + object->GetHeight() / 2, 0));
				}
				if (name == "app3")
				{
					listPosApp3.push_back(D3DXVECTOR3(object->GetX() + object->GetWidth() / 2,
						object->GetY() + object->GetHeight() / 2, 0));
				}
		}
	
	}


#pragma endregion
}

bool GameMapBoss::isContain(RECT rect1, RECT rect2)
{
	if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
	{
		return false;
	}

	return true;
}

Tmx::Map* GameMapBoss::GetMap()
{
	return mMap;
}

int GameMapBoss::GetWidth()
{
	return mMap->GetWidth() * mMap->GetTileWidth();
}

int GameMapBoss::GetHeight()
{
	return mMap->GetHeight() * mMap->GetTileHeight();
}

int GameMapBoss::GetTileWidth()
{
	return mMap->GetTileWidth();
}

int GameMapBoss::GetTileHeight()
{
	return mMap->GetTileHeight();
}

void GameMapBoss::Draw()
{
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);

#pragma region DRAW TILESET
	for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
	{
		const Tmx::TileLayer *layer = mMap->GetTileLayer(i);

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
#pragma endregion

}

void GameMapBoss::SetCamera(Camera * camera)
{
	this->mCamera = camera;
}

RECT GameMapBoss::GetWorldMapBound()
{
	RECT bound;
	bound.left = bound.top = 0;
	bound.right = mMap->GetWidth() * mMap->GetTileWidth();
	bound.bottom = mMap->GetHeight() * mMap->GetTileHeight();

	return bound;
}


bool GameMapBoss::IsBoundLeft()
{
	return (mCamera->GetBound().left == 0);
}

bool GameMapBoss::IsBoundRight()
{
	return (mCamera->GetBound().right == this->GetWidth());
}

bool GameMapBoss::IsBoundTop()
{
	return (mCamera->GetBound().top == 0);
}

bool GameMapBoss::IsBoundBottom()
{
	return (mCamera->GetBound().bottom == this->GetHeight());
}

std::map<int, Sprite*> GameMapBoss::getListTileSet()
{
	return mListTileset;
}

QuadTree * GameMapBoss::GetQuadTree()
{
	return mQuadTree;
}
void GameMapBoss::Update(float dt)
{
}