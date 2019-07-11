#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>

#include "../GameComponents/Scene.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/GameMapBoss.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/Player.h"
#include "../GameDefines/GameDefine.h"
#include "../GameComponents/Scene.h"
#include "../GameObjects/Boss/Boss.h"
#include "../GameComponents/UI.h"
#include "GameEnd.h"
class BossScene : public Scene
{
public:
	BossScene(Player *player,UI* ui);
	~BossScene();
	void Update(float dt);
	void LoadContent();
	void Draw();
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	vector<Rect> loadRect(bool flag);
protected:
	Player* mPlayer;
	UI* mUI;
	Boss* mBoss;
	Animation *EatItem,*Damage;
	GameMapBoss *mMap;
	Camera *mCamera;

	float mTimeCounter;
	void CheckCameraAndWorldMap();

	void checkCollision();
	void AppleObjectHandle();
	AppleObject *app1, *app2, *app3;
	
	std::map<int, bool> keys;

	
	float lastTime = 0;
	ID3DXFont				*myFont;
	Rect myRect;
	
	bool isEnd = false;

};

