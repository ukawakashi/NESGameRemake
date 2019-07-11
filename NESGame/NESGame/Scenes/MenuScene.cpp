#include "MenuScene.h"
#include "AfterMenuScene.h"




MenuScene::MenuScene()
{
	LoadContent();
	nextScene = NULL;
}


MenuScene::~MenuScene()
{
	/*mCurrent = mStart = mOption = mDiffNormal = mDiffDifficult = mMusic = mSound = mSoundTest = mTrigger = mExit = NULL;
	delete mCurrent, mStart, mOption, mDiffNormal, mDiffDifficult, mMusic, mSound, mSoundTest, mTrigger, mExit;*/

	Knife = NULL; menuScene1 = menuScene2 = currentMenu = NULL; nextScene = NULL;
	delete Knife, menuScene1, menuScene2, currentMenu, nextScene;

}

vector<Rect> MenuScene::loadRect(MenuState state)
{
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);
	vector<Rect> listRect;

	switch (state)
	{
	case MenuScene::Start:
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "MenuStart");
		break;
	case MenuScene::Option:
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "MenuOption");
		break;
	case MenuScene::DiffNormal:
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "MenuDiffNormal");
		break;
	case MenuScene::DiffDifficult:
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "MenuDiffDifficult");
		break;
	case MenuScene::Music:
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "MenuMusic");
		break;
	case MenuScene::Sound:
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "MenuSound");
		break;
	case MenuScene::SoundTest:
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "MenuSoundTest");
		break;
	case MenuScene::Trigger:
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "MenuTrigger");
		break;
	case MenuScene::Exit:
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "MenuExit");
		break;
	default:
		break;
	}
	return listRect;
}

void MenuScene::LoadContent()
{
	/*Intro1 = new Animation("Resources/MenuScene.png", 42, loadRect(false), (float)1 / 0.2, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	Intro1->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	Intro1->GetSprite()->SetScale(D3DXVECTOR2(1, 1));*/

	Rect rect = { 0,0,320,240 };
	menuScene1 = new Sprite("Resources/Menu.png", rect, 320, 240, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5));// , GameGlobal::mScenetexture);
	menuScene1->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	currentMenu = menuScene1;

	menuScene2 = new Sprite("Resources/Menu2.jpg", rect, 320, 240, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5));// , GameGlobal::mScenetexture);
	menuScene2->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);

	rect = { 0,0,222,89 };
	vector<Rect> listRect;
	listRect.push_back(rect);
	Knife = new Animation(ResourceManager::GetInstance()->GetTextureKnife(), 1, listRect, (float)1 / 0.1, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 255, 255));
	Knife->SetPosition(MENU_START_X, MENU_START_Y);
	Knife->GetSprite()->SetScale(D3DXVECTOR2(0.15, 0.15));

	/*mStart = new Animation(ResourceManager::GetInstance()->GetTextureMenu(),24 , loadRect(MenuState::Start), (float)1 /  5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255), Entity::Entity::EntityTypes::Menu);
	mStart->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	mStart->GetSprite()->SetScale(D3DXVECTOR2(1, 1));
	mOption = new Animation(ResourceManager::GetInstance()->GetTextureMenu(), 9, loadRect(MenuState::Option), (float)1 /  5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255), Entity::Entity::EntityTypes::Menu);
	mOption->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	mOption->GetSprite()->SetScale(D3DXVECTOR2(1, 1));
	mDiffNormal = new Animation(ResourceManager::GetInstance()->GetTextureMenu(), 5, loadRect(MenuState::DiffNormal), (float)1 /  5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255), Entity::Entity::EntityTypes::Menu);
	mDiffNormal->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	mDiffNormal->GetSprite()->SetScale(D3DXVECTOR2(1, 1));
	mDiffDifficult = new Animation(ResourceManager::GetInstance()->GetTextureMenu(), 6, loadRect(MenuState::DiffDifficult), (float)1 /  5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255), Entity::Entity::EntityTypes::Menu);
	mDiffDifficult->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	mDiffDifficult->GetSprite()->SetScale(D3DXVECTOR2(1, 1)); mMusic = new Animation(ResourceManager::GetInstance()->GetTextureMenu(), 3, loadRect(MenuState::Music), (float)1 /  5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255), Entity::Entity::EntityTypes::Menu);
	mSound = new Animation(ResourceManager::GetInstance()->GetTextureMenu(), 6, loadRect(MenuState::Sound), (float)1 /  5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255), Entity::Entity::EntityTypes::Menu);
	mSound->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	mSound->GetSprite()->SetScale(D3DXVECTOR2(1, 1));
	mSoundTest = new Animation(ResourceManager::GetInstance()->GetTextureMenu(), 4, loadRect(MenuState::SoundTest), (float)1 /  5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255), Entity::Entity::EntityTypes::Menu);
	mSoundTest->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	mSoundTest->GetSprite()->SetScale(D3DXVECTOR2(1, 1));
	mTrigger = new Animation(ResourceManager::GetInstance()->GetTextureMenu(), 3, loadRect(MenuState::Trigger), (float)1 /  5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255), Entity::Entity::EntityTypes::Menu);
	mTrigger->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	mTrigger->GetSprite()->SetScale(D3DXVECTOR2(1, 1));
	mExit = new Animation(ResourceManager::GetInstance()->GetTextureMenu(), 4, loadRect(MenuState::Exit), (float)1 /  5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255), Entity::Entity::EntityTypes::Menu);
	mExit->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	mExit->GetSprite()->SetScale(D3DXVECTOR2(1, 1));

	mCurrent = mStart;
	mCurrentState = MenuState::Start;*/

}

void MenuScene::Update(float dt)
{
	/*menuScene->Update(1);*/
	/*if (Intro1->GetCurrentFrame() == 42) {
	SceneManager::GetInstance()->ReplaceScene(nextScene);
	}*/
	/*if (Intro2->GetCurrentFrame() == 8)
	SceneManager::GetInstance()->ReplaceScene(nextScene);*/
	//mCurrent->Update(1);
	float posX = Knife->GetSprite()->GetPosition().x + 0.5, posY = Knife->GetSprite()->GetPosition().y;

	if (isStartMenu)
	{
		if (posX == 95)
		{
			posX = MENU_START_X;
		}
	}
	else {
		if (posX == 65)
		{
			posX = MENU_OPTION_X;
		}
	}
	Knife->GetSprite()->SetPosition(posX, posY);
	Knife->Update(1);
}
void MenuScene::Draw()
{
	//mCurrent->Draw();
	currentMenu->Draw();
	Knife->Draw();
}
void MenuScene::OnKeyDown(int keyCode)
{
	if (keyCode == VK_DOWN)
	{
		if (isStartMenu)
		{
			if (Knife->GetSprite()->GetPosition().y == MENU_START_Y)
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_OPTION_Y);
			}
			else
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_START_Y);
			}
		}
		else {
			if (Knife->GetSprite()->GetPosition().y == MENU_DIFF_Y)
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_MUSIC_Y);
			}
			else if (Knife->GetSprite()->GetPosition().y == MENU_MUSIC_Y)
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_SOUND_Y);
			}
			else if (Knife->GetSprite()->GetPosition().y == MENU_SOUND_Y)
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_SOUNDTEST_Y);
			}
			else if (Knife->GetSprite()->GetPosition().y == MENU_SOUNDTEST_Y)
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_TRIGGER_Y);
			}
			else if (Knife->GetSprite()->GetPosition().y == MENU_TRIGGER_Y)
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_EXIT_Y);
			}
			else if (Knife->GetSprite()->GetPosition().y == MENU_EXIT_Y)
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_DIFF_Y);
			}
		}
	}
	
	else if (keyCode == VK_UP)
	{
		if (isStartMenu)
		{
			if (Knife->GetSprite()->GetPosition().y == MENU_START_Y)
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_OPTION_Y);
			}
			else
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_START_Y);
			}
		}
		else {
			if (Knife->GetSprite()->GetPosition().y == MENU_DIFF_Y)
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_EXIT_Y);
			}
			else if (Knife->GetSprite()->GetPosition().y == MENU_MUSIC_Y)
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_DIFF_Y);
			}
			else if (Knife->GetSprite()->GetPosition().y == MENU_SOUND_Y)
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_MUSIC_Y);
			}
			else if (Knife->GetSprite()->GetPosition().y == MENU_SOUNDTEST_Y)
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_SOUND_Y);
			}
			else if (Knife->GetSprite()->GetPosition().y == MENU_TRIGGER_Y)
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_SOUNDTEST_Y);
			}
			else if (Knife->GetSprite()->GetPosition().y == MENU_EXIT_Y)
			{
				Knife->SetPosition(Knife->GetSprite()->GetPosition().x, MENU_TRIGGER_Y);
			}
		}
	}
}

void MenuScene::OnKeyUp(int keyCode)
{
	if (keyCode == VK_RETURN)
	{
		if (isClicked)
		{
			if (isStartMenu)
			{
				if (Knife->GetSprite()->GetPosition().y == MENU_START_Y)
				{
					ResourceManager::GetInstance()->stopSound("MenuTheme");
					SceneManager::GetInstance()->ReplaceScene(nextScene = new AfterMenuScene());
				}
				else if (Knife->GetSprite()->GetPosition().y == MENU_OPTION_Y)
				{
					currentMenu = menuScene2;
					isStartMenu = false;
					Knife->SetPosition(MENU_OPTION_X, MENU_DIFF_Y);
				}
			}
			else {
				if (Knife->GetSprite()->GetPosition().y == MENU_EXIT_Y)
				{
					currentMenu = menuScene1;
					isStartMenu = true;
					Knife->SetPosition(MENU_START_X, MENU_START_Y);
				}
			}
		}
		else
			isClicked = true;
		

	}


}