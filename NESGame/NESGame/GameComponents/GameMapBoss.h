#pragma once
#include "../GameComponents/Sprite.h"
#include "../MapReader/Tmx.h.in"
#include "Camera.h"
#include "GameGlobal.h"
#include "GameCollision.h"
#include "QuadTree.h"
#include <iostream>
#include <sstream>
using namespace std;
class GameMapBoss
{
public:
	GameMapBoss(string filePath);
	~GameMapBoss();
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
	vector<D3DXVECTOR3> listPosApp1;
	vector<D3DXVECTOR3> listPosApp2;
	vector<D3DXVECTOR3> listPosApp3;
private:
	void LoadMap(string filePath);
	QuadTree                        *mQuadTree;
	bool isContain(RECT rect1, RECT rect2);

	Tmx::Map                        *mMap;
	std::map<int, Sprite*>          mListTileset;
	Camera *mCamera;
};







