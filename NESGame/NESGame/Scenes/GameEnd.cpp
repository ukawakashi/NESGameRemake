#include "GameEnd.h"
#include "MenuScene.h"

GameEnd::GameEnd()
{
	LoadContent();
	mCur = mMoon;
}


GameEnd::~GameEnd()
{
}

vector<Rect> GameEnd::loadRect(bool state)
{
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);
	vector<Rect> listRect;
	if (state)
	{
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "MoonScene");
	}
	else {
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "End.");
	}
	return listRect;
}

void GameEnd::LoadContent()
{

	//Choi nhac nen
	ResourceManager::GetInstance()->playSound("MenuTheme", true, 0);

	mMoon = new Animation("Resources/Scenes/MoonScene.png", 57, loadRect(true), (float)1 / 0.15, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	mMoon->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	mMoon->GetSprite()->SetScale(D3DXVECTOR2(1, 1));

	mEnd = new Animation("Resources/Scenes/TheEnd.png", 280, loadRect(false), (float)1 / 0.1, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	mEnd->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	mEnd->GetSprite()->SetScale(D3DXVECTOR2(1, 1));

}

void GameEnd::Update(float dt)
{

	if (isMoon)
	{
		if (mCur->GetCurrentFrame() == 56)
		{
			mCur = mEnd;
			isMoon = false;
		}
		mCur->Update(1);
	}
	else if (mCur->GetCurrentFrame() == 279)
	{
		ResourceManager::GetInstance()->stopSound("MenuTheme");
	}
	else
		mCur->Update(1);

}
void GameEnd::Draw()
{
	mCur->Draw();
}
void GameEnd::OnKeyDown(int keyCode)
{
	
}

void GameEnd::OnKeyUp(int keyCode)
{
	//if (keyCode == VK_RETURN)
	//return;
}