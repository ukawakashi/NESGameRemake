#include "LevelCompleteScene.h"
#include "MenuScene.h"

LevelCompleteScene::LevelCompleteScene(Player* pl, UI* ui)
{
	this->pl = pl;
	this->ui = ui;
	LoadContent();
	nextScene = NULL;
}


LevelCompleteScene::~LevelCompleteScene()
{
}

vector<Rect> LevelCompleteScene::loadRect()
{
	mBackColor = D3DCOLOR_XRGB(0, 0, 0);
	vector<Rect> listRect;
	listRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLIntro(), "LevelComplete");
	return listRect;
}

void LevelCompleteScene::LoadContent()
{

	//Choi nhac nen
	ResourceManager::GetInstance()->playSound("StageClear", true, 0);

	backGround = new Animation("Resources/Scenes/LevelComplete.png", 51, loadRect(), (float)1 / 0.15, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255));
	backGround->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
	backGround->GetSprite()->SetScale(D3DXVECTOR2(1, 1));

}

void LevelCompleteScene::Update(float dt)
{

	if (backGround->GetCurrentFrame() == 50)
	{
		ResourceManager::GetInstance()->stopSound("StageClear");
		SceneManager::GetInstance()->ReplaceScene(nextScene = new BossScene(pl, ui));
	}
	backGround->Update(1);
}
void LevelCompleteScene::Draw()
{
	backGround->Draw();
}
void LevelCompleteScene::OnKeyDown(int keyCode)
{
	if (keyCode == VK_RETURN) {
		ResourceManager::GetInstance()->stopSound("StageClear");
		SceneManager::GetInstance()->ReplaceScene(nextScene = new BossScene(pl, ui));
	}
}

void LevelCompleteScene::OnKeyUp(int keyCode)
{




}