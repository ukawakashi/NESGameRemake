#include "Intro2Scene.h"
#include "MenuScene.h"

Intro2Scene::Intro2Scene()
{
	LoadContent();
	nextScene = NULL;
}


Intro2Scene::~Intro2Scene()
{
}

vector<Rect> Intro2Scene::loadRect(bool state)
{
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);
	vector<Rect> listRect;
	if (state)
	{
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "Intro2");
	}
	else {
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "Background_Intro2");
	}
	return listRect;
}

void Intro2Scene::LoadContent()
{

	//Choi nhac nen
	ResourceManager::GetInstance()->playSound("MenuTheme", true, 0);

	Intro2 = new Animation(ResourceManager::GetInstance()->GetTextureIntroScene(), 8, loadRect(true), (float)1 / 0.15, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	Intro2->SetPosition(0, GameGlobal::GetHeight() / 2 - 20);
	Intro2->GetSprite()->SetScale(D3DXVECTOR2(1, 1));

	background_Intro2 = new Animation(ResourceManager::GetInstance()->GetTextureIntro2(), 3, loadRect(false), (float)1 / 0.1, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	background_Intro2->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	background_Intro2->GetSprite()->SetScale(D3DXVECTOR2(1, 1));

}

void Intro2Scene::Update(float dt)
{

	Intro2->GetSprite()->SetPosition(Intro2->GetSprite()->GetPosition().x + 2, GameGlobal::GetHeight() / 2 - 20);
	Intro2->Update(1);
	if (Intro2->GetSprite()->GetPosition().x > 360)
		background_Intro2->Update(1);

	if (Intro2->GetSprite()->GetPosition().x > GameGlobal::GetWidth() + 120) {
		SceneManager::GetInstance()->ReplaceScene(nextScene = new MenuScene());
	}
}
void Intro2Scene::Draw()
{
	background_Intro2->Draw();
	Intro2->Draw();
}
void Intro2Scene::OnKeyDown(int keyCode)
{
	if (keyCode == VK_RETURN)
		if (Intro2->GetSprite()->GetPosition().x <= GameGlobal::GetWidth() + 120)
			SceneManager::GetInstance()->ReplaceScene(nextScene = new MenuScene());
}

void Intro2Scene::OnKeyUp(int keyCode)
{




}