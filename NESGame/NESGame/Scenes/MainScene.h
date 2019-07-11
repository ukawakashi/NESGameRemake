#pragma once

#include <math.h>
#include <vector>
#include <d3dx9.h>
#include <d3d9.h>

#include "../GameComponents/Scene.h"
#include "../GameComponents/Sprite.h"
#include "../GameComponents/Animation.h"
#include "../GameComponents/GameMap.h"
#include "../GameComponents/Camera.h"
#include "../GameObjects/Player/Player.h"
#include "../GameDefines/GameDefine.h"
//#include "../GameObjects/Apple/Apple.h"
#include "../GameObjects/MapObject/CivilianThrowBowl/ManThrowBowl.h"
#include "../GameObjects/Enemy/Enemy1/Enemy1.h"
#include "../GameObjects/Enemy/Enemy2/Enemy2.h"
#include "../GameObjects/Enemy/Enemy3/Enemy3.h"
#include "../GameObjects/Enemy/Enemy4/Enemy4.h"
#include "../GameObjects/Enemy/Enemy5/Enemy5.h"
#include "../GameObjects/MapObject/FlagPole.h"
#include "../GameObjects/MapObject/Peddler/Peddler1.h"
#include "../GameControllers/SceneManager.h"
#include "DieScene.h"
#include "../GameComponents/UI.h"
#include "LevelCompleteScene.h"
#include "MenuScene.h"
class MainScene : public Scene
{
public:
    MainScene();
	~MainScene();

    void Update(float dt);
    void LoadContent();
    void Draw();

    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);
    void OnMouseDown(float x, float y);
	DieScene *mDieScene;
	int lastKey;

protected:
	UI* mUI;
	Animation *EatItem,*Fired1,*Fired2;
    GameMap *mMap;
    Camera *mCamera;
	Player *mPlayer;
	bool CheckUp = false;
    float mTimeCounter;
	void CheckCameraAndWorldMap();

	void checkCollision();

    std::map<int, bool> keys;


};

