#include "AfterMenuScene.h"
#include "MainScene.h"

AfterMenuScene::AfterMenuScene()
{
	LoadContent();
	mCur = mBug;
	current = CutScene::Bug;
	nextScene = NULL;
}


AfterMenuScene::~AfterMenuScene()
{
}

vector<Rect> AfterMenuScene::loadRect(int state)
{
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);
	vector<Rect> listRect;
	switch (state)
	{
	case 1:
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "Bug");
		break;
	case 2:
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "Explain");
		break;
	case 3:
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "CutScene");
		break;
	default:
		break;
	}
	if (state)
	{

	}
	else {
	}
	return listRect;
}

void AfterMenuScene::LoadContent()
{

	//Nhac nen
	ResourceManager::GetInstance()->playSound("CutSceneTheme", true, 0);

	/*Intro2 = new Animation("Resources/IntroScene.png", 8, loadRect(true), (float)1 / 0.15, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	Intro2->SetPosition(0, GameGlobal::GetHeight() / 2-20);
	Intro2->GetSprite()->SetScale(D3DXVECTOR2(1, 1));

	background_Intro2 = new Animation("Resources/Intro2.png", 3, loadRect(false), (float)1 /0.1, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	background_Intro2->SetPosition(GameGlobal::GetWidth()/2, GameGlobal::GetHeight() / 2);
	background_Intro2->GetSprite()->SetScale(D3DXVECTOR2(1, 1));*/

	mBug = new Animation("Resources/Scenes/Bug.png", 14, loadRect(1), (float)1 / 0.15, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	mBug->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	mBug->GetSprite()->SetScale(D3DXVECTOR2(1, 1));

	mExplain = new Animation("Resources/Scenes/Explain.png", 16, loadRect(2), (float)1 / 0.15, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	mExplain->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	mExplain->GetSprite()->SetScale(D3DXVECTOR2(1, 1));

	mCutscene = new Animation("Resources/Scenes/CutScene.png", 86, loadRect(3), (float)1 / 0.15, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	mCutscene->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	mCutscene->GetSprite()->SetScale(D3DXVECTOR2(1, 1));
}

void AfterMenuScene::Update(float dt)
{

	/*Intro2->GetSprite()->SetPosition(Intro2->GetSprite()->GetPosition().x + 2, GameGlobal::GetHeight() / 2 - 20);
	Intro2->Update(1);
	if (Intro2->GetSprite()->GetPosition().x > 360  )
		background_Intro2->Update(1);
	
	if (Intro2->GetSprite()->GetPosition().x>GameGlobal::GetWidth()+120) {
		SceneManager::GetInstance()->ReplaceScene(nextScene);
	}*/
	switch (current)
	{
	case AfterMenuScene::Bug:
		if (mCur->GetCurrentFrame()==13)
		{
			mCur = mExplain;
			current = CutScene::Explain;
		}
		break;
	case AfterMenuScene::Explain:
		if (mCur->GetCurrentFrame() == 15)
		{
			mCur = mCutscene;
			current = CutScene::cutScene;
		}
		break;
	case AfterMenuScene::cutScene:
		if (mCur->GetCurrentFrame() == 85)
		{
			ResourceManager::GetInstance()->stopSound("CutSceneTheme");
			SceneManager::GetInstance()->ReplaceScene(nextScene = new MainScene());
		}
		break;
	default:
		break;
	}
	mCur->Update(1);

}
void AfterMenuScene::Draw()
{
	/*background_Intro2->Draw();
	Intro2->Draw();*/
	mCur->Draw();

}
void AfterMenuScene::OnKeyDown(int keyCode)
{

}

void AfterMenuScene::OnKeyUp(int keyCode)
{
	if (keyCode == VK_RETURN)
	{
		ResourceManager::GetInstance()->stopSound("CutSceneTheme");
		SceneManager::GetInstance()->ReplaceScene(nextScene = new MainScene());
	}


}