#pragma once
#include "../GameComponents/Scene.h"
#include "../GameComponents/Animation.h"
#include "../GameControllers/SceneManager.h"
#include "BossScene.h"

class Intro2Scene : public Scene
{
public:
	Intro2Scene();
	~Intro2Scene();
	void Update(float dt);
	void LoadContent();
	void Draw();
	Animation *Intro2, *background_Intro2;
	Scene *nextScene;

	vector<Rect> loadRect(bool state);

	bool clicked = false;
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

};

