#pragma once
#include "../GameComponents/Scene.h"
#include "../GameComponents/Animation.h"
#include "../GameControllers/SceneManager.h"
#include "BossScene.h"

class IntroScene : public Scene
{
public:
	IntroScene();
	~IntroScene();
	void Update(float dt);
	void LoadContent();
	void Draw();
	Animation *Intro1;
	Scene *nextScene;
	int i = 0;

	vector<Rect> loadRect(bool state);

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

};

