#pragma once
#include "../GameComponents/Scene.h"
#include "../GameComponents/Animation.h"
#include "../GameControllers/SceneManager.h"
#include "BossScene.h"

class LevelCompleteScene : public Scene
{
public:
	LevelCompleteScene(Player* pl, UI* ui);
	~LevelCompleteScene();
	void Update(float dt);
	void LoadContent();
	void Draw();
	Animation *backGround;
	Scene *nextScene;

	vector<Rect> loadRect();
	Player* pl;
	UI* ui;
	bool clicked = false;
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

};

