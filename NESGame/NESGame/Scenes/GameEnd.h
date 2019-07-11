#pragma once
#include "../GameComponents/Scene.h"
#include "../GameComponents/Animation.h"
#include "../GameControllers/SceneManager.h"
#include "BossScene.h"

class GameEnd : public Scene
{
public:
	GameEnd();
	~GameEnd();
	void Update(float dt);
	void LoadContent();
	void Draw();
	Animation *mMoon, *mEnd, *mCur;
	bool isMoon = true;

	vector<Rect> loadRect(bool state);

	bool clicked = false;
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

};

