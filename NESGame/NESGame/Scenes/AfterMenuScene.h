#pragma once
#include "../GameComponents/Scene.h"
#include "../GameComponents/Animation.h"
#include "../GameControllers/SceneManager.h"
#include "MainScene.h"

class AfterMenuScene : public Scene
{
public:
	AfterMenuScene();
	~AfterMenuScene();
	void Update(float dt);
	void LoadContent();
	void Draw();
	Animation *mBug, *mExplain, *mCutscene, *mCur;
	Scene *nextScene;
	int i = 0;
	enum CutScene {
		Bug = 1, 
		Explain = 2,
		cutScene = 3
	} current;

	vector<Rect> loadRect(int state);

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

};

