#include "DieScene.h"


DieScene::DieScene(Scene* sc)
{
	LoadContent();
	preScene = sc;
}


DieScene::~DieScene()
{
	preScene = NULL;
	die = abu = NULL;
	delete preScene, die, abu;
}

vector<Rect> DieScene::loadRect(bool state)
{
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);
	vector<Rect> listRect;
	Rect rect;
	if (state)
	{
		listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Die");
	}
	else {
		rect.left = 0; rect.top = 0; rect.right = rect.left + 68; rect.bottom = rect.top + 29; listRect.push_back(rect);
		rect.left = 64; rect.top = 55; rect.right = rect.left + 57; rect.bottom = rect.top + 36; listRect.push_back(rect);
		rect.left = 0; rect.top = 79; rect.right = rect.left + 57; rect.bottom = rect.top + 44; listRect.push_back(rect);
		rect.left = 69; rect.top = 0; rect.right = rect.left + 58; rect.bottom = rect.top + 54; listRect.push_back(rect);
		rect.left = 128; rect.top = 0; rect.right = rect.left + 51; rect.bottom = rect.top + 53; listRect.push_back(rect);
		rect.left = 0; rect.top = 30; rect.right = rect.left + 63; rect.bottom = rect.top + 48; listRect.push_back(rect);
	}
	return listRect;
}

void DieScene::LoadContent()
{
	die = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 38, loadRect(true), (float)1 / 0.2, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	die->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	die->GetSprite()->SetScale(D3DXVECTOR2(1, 1));

	abu = new Animation("Resources/abu.png", 6, loadRect(false), (float)1 / 0.2, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	abu->SetPosition(GameGlobal::GetWidth() * 2 / 3, GameGlobal::GetHeight() * 2 / 3);
	die->GetSprite()->SetScale(D3DXVECTOR2(1, 1));
}

void DieScene::Update(float dt)
{
	die->Update(1);
	abu->Update(1);

	if (abu->GetCurrentFrame() == 4)
		ResourceManager::GetInstance()->playSound("abu", false, 1);

	if (die->GetCurrentFrame() == 28)
		ResourceManager::GetInstance()->playSound("genie", false, 1);

	if (die->GetCurrentFrame() == 37)
		SceneManager::GetInstance()->ReplaceScene(preScene);
}
void DieScene::Draw()
{
	die->Draw();
	abu->Draw();
}

void DieScene::OnKeyDown(int keyCode)
{

}

void DieScene::OnKeyUp(int keyCode)
{




}