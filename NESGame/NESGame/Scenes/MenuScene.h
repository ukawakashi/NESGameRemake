#pragma once
#include "../GameComponents/Scene.h"
#include "../GameComponents/Animation.h"
#include "../GameControllers/SceneManager.h"
#include "BossScene.h"

class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();
	void Update(float dt);
	void LoadContent();
	void Draw();
	/*Animation *menuScene;*/
	Animation* Knife;
	/*Animation *mCurrent, *mStart, *mOption, *mDiffNormal, *mDiffDifficult,
		*mMusic, *mSound, *mSoundTest, *mTrigger, *mExit;*/
	Sprite *menuScene1, *menuScene2, *currentMenu;
	bool isStartMenu = true,isClicked = false;
	Scene *nextScene;

	enum MenuState {
		Start,
		Option,
		DiffNormal,
		DiffDifficult,
		Music,
		Sound,
		SoundTest,
		Trigger,
		Exit
	};

	vector<Rect> loadRect(MenuState state);

	MenuState mCurrentState;

	bool clicked = false;
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

	const float MENU_START_X = 80;
	const float MENU_OPTION_X = 50;

	const float MENU_START_Y = 150;
	const float MENU_OPTION_Y = 165;

	const float MENU_DIFF_Y = 135;
	const float MENU_MUSIC_Y = 150;
	const float MENU_SOUND_Y = 165;
	const float MENU_SOUNDTEST_Y = 180;
	const float MENU_TRIGGER_Y = 195;
	const float MENU_EXIT_Y = 210;

};

