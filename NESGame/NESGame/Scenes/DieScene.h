#pragma once
#include "../GameComponents/Scene.h"
#include "../GameComponents/Animation.h"
#include "../GameControllers/SceneManager.h"
#include "BossScene.h"

class DieScene : public Scene
{
public:
	DieScene(Scene *preScene);
	~DieScene();
	void Update(float dt);
	void LoadContent();
	void Draw();
	Animation *die, *abu;
	Scene *preScene;

	vector<Rect> loadRect(bool state);

	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

};

