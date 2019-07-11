#include "Intro1Scene.h"
#include "MainScene.h"
#include "Intro2Scene.h"

IntroScene::IntroScene()
{
	LoadContent();
	nextScene = NULL;
}


IntroScene::~IntroScene()
{

}

vector<Rect> IntroScene::loadRect(bool state)
{
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);
	vector<Rect> listRect;
	if (state)
	{
		/*listRect = ReadResource::Instance()->LoadXML(_animationXMLIntro, "Intro2");*/
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "Intro3");
	}
	/*else {
		listRect = ReadResource::Instance()->LoadXML(_animationXMLIntro, "Intro1");
	}*/
	return listRect;
}

void IntroScene::LoadContent()
{
	//Khong co nhac nen
	ResourceManager::GetInstance()->playSound("null", true, 0);


	/*Intro2 = new Animation("Resources/IntroScene.png", 8, loadRect(true), (float)1 / 0.2, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	Intro2->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	Intro2->GetSprite()->SetScale(D3DXVECTOR2(1, 1));*/

	Intro1 = new Animation(ResourceManager::GetInstance()->GetTextureIntro(), 42, loadRect(true), (float)1 / 0.2, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	//Intro1->SetPosition(100 + GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	Intro1->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	Intro1->GetSprite()->SetScale(D3DXVECTOR2(1, 1));
}

void IntroScene::Update(float dt)
{

	Intro1->Update(1);
	if (Intro1->GetCurrentFrame() == 4)
	{
		ResourceManager::GetInstance()->playSound("StartGun", false, 1);
	}
	else if (Intro1->GetCurrentFrame() == 6)
	{
		ResourceManager::GetInstance()->playSound("IagoSquawk", false, 1);
	}
	else if (Intro1->GetCurrentFrame() == 11)
	{
		ResourceManager::GetInstance()->playSound("StonesCrumble", false, 1);
	}
	else if (Intro1->GetCurrentFrame() == 41 && i == 0) 
	{
		SceneManager::GetInstance()->ReplaceScene(nextScene = new Intro2Scene());
	}
	
}
void IntroScene::Draw()
{
	Intro1->Draw();
}
void IntroScene::OnKeyDown(int keyCode)
{
	if (keyCode == VK_RETURN)
		SceneManager::GetInstance()->ReplaceScene(nextScene = new Intro2Scene());
}

void IntroScene::OnKeyUp(int keyCode)
{

}