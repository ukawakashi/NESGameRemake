#pragma once
#ifndef __GAME_MAP__
#define __GAME_MAP__

#include "../GameComponents/Sprite.h"
#include "../MapReader/Tmx.h.in"
#include "Camera.h"
#include "GameGlobal.h"
#include "GameCollision.h"
#include "QuadTree.h"
#include <iostream>
#include <sstream>
#include "../GameObjects/MapObject/Camel.h"
//#include "../AppleObject.h"
#include "../GameObjects/MapObject/DropBrick.h"
#include "../GameObjects/MapObject/FlagPole.h"
#include "../GameObjects/MapObject/CheckPointSite.h"
using namespace std;
class GameMap
{
public:
	GameMap(string filePath);

	Tmx::Map* GetMap();
	void Update(float dt);

	void SetCamera(Camera *camera);

	void Draw();

	RECT GetWorldMapBound();
	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();
	std::map<int, Sprite*> getListTileSet();

	bool IsBoundLeft(); //kiem tra luc nay Camera o vi bien ben trai so voi WorldMap
	bool IsBoundRight(); // kiem tra xem co o vi tri bien ben phai worldmap khong
	bool IsBoundTop(); // kiem tra xem co o vi tri bien ben trai worldmap khong
	bool IsBoundBottom(); // kiem tra xem co o vi tri bien ben phai worldmap khong

	QuadTree* GetQuadTree();
	~GameMap();
	void DrawFront();
	vector<Camel*> listCamel;
	vector<AppleObject*> listAppleObject;
	vector<AppleObject*> listHeart;
	vector<AppleObject*> listLamp;
	vector<AppleObject*> list1Up;
	vector<AppleObject*> listRedRock;
	vector<AppleObject*> listGenieBonus;
	vector<AppleObject*> listAbuBonus;
	vector<D3DXVECTOR2> listBowlPosition1;
	vector<D3DXVECTOR2> listBowlPosition2;
	vector<D3DXVECTOR2> listPeddlerPosition1;

	vector<D3DXVECTOR2> listEnemy1Position;
	vector<D3DXVECTOR2> listEnemy2Position;
	vector<D3DXVECTOR2> listEnemy3Position;
	vector<D3DXVECTOR2> listEnemy4Position;
	vector<D3DXVECTOR2> listEnemy5Position;
	vector<DropBrick*> listDropBrick;
	vector<FlagPole*>	listFlagPole;
	vector<CheckPointSite*>	listCheckPointSite;

	D3DXVECTOR2 startStair1, endStair1;
	D3DXVECTOR2 startStair2, endStair2;
	D3DXVECTOR2 posStartEnemy11;
private:
	void LoadMap(string filePath);
	QuadTree                        *mQuadTree;
	bool isContain(RECT rect1, RECT rect2);

	Tmx::Map                        *mMap;
	std::map<int, Sprite*>          mListTileset;
	Camera *mCamera;

};

#endif

