#include "UI.h"

Rect LoadNumber(int i)
{
	Rect rect;
	switch (i)
	{
	case 0:
		rect.left = 41; rect.top = 13; rect.right = rect.left + 56; rect.bottom = rect.top + 76;
		break;
	case 1:
		rect.left = 144; rect.top = 14; rect.right = rect.left + 27;  rect.bottom = rect.top + 74;
		break;
	case 2:
		rect.left = 230; rect.top = 13; rect.right = rect.left + 51; rect.bottom = rect.top + 75;
		break;
	case 3:
		rect.left = 323; rect.top = 13; rect.right = rect.left + 49; rect.bottom = rect.top + 76;
		break;
	case 4:
		rect.left = 412; rect.top = 14; rect.right = rect.left + 57; rect.bottom = rect.top + 74;
		break;
	case 5:
		rect.left = 505; rect.top = 14; rect.right = rect.left + 56; rect.bottom = rect.top + 75;
		break;
	case 6:
		rect.left = 600; rect.top = 14; rect.right = rect.left + 54; rect.bottom = rect.top + 75;
		break;
	case 7:
		rect.left = 694; rect.top = 14;  rect.right = rect.left + 52; rect.bottom = rect.top + 74;
		break;
	case 8:
		rect.left = 788; rect.top = 13; rect.right = rect.left + 49;  rect.bottom = rect.top + 76;
		break;
	case 9:
		rect.left = 878;  rect.top = 14; rect.right = rect.left + 54;  rect.bottom = rect.top + 74;
		break;
	default:
		break;
	}
	return rect;
}
vector<Rect> loadHealth(int num)
{
	vector<Rect> listsourceRect;
	switch (num)
	{
	case 10:
		listsourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLItems(), "HealthBar1");
		break;
	case 9:
		listsourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLItems(), "HealthBar2");
		break;
	case 8:
		listsourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLItems(), "HealthBar3");
		break;
	case 7:
		listsourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLItems(), "HealthBar4");
		break;
	case 6:
		listsourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLItems(), "HealthBar5");
		break;
	case 5:
		listsourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLItems(), "HealthBar6");
		break;
	case 4:
		listsourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLItems(), "HealthBar7");
		break;
	case 3:
		listsourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLItems(), "HealthBar8");
		break;
	case 2:
		listsourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLItems(), "HealthBar9");
		break;
	case 1:
		listsourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLItems(), "HealthBar10");
		break;
	case 0:
		listsourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLItems(), "GoldenLamp");
		break;
	}
	return listsourceRect;
}
Rect LoadHP(int i)
{
	Rect rect;
	rect.top = 0;
	rect.bottom = 15;
	rect.right = 76;
	rect.left = 0;
	for (int j = 1; j <= 9; j++)
	{
		if (i == j)
		{
			rect.left = (9 - i)* (76 / 9);
			return rect;
		}
	}
	return rect;
}
UI::UI(Player* pl)
{
	/*startTime = GetTickCount();*/
	mplayer = pl;
	Rect rect;
	rect.left = 14; rect.top = 1; rect.right = rect.left + 97; rect.bottom = rect.top + 146;

	//so tao
	apple1 = new Sprite("Resources/number.png", Rect(), 0, 0, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5), GameGlobal::mNumbertexture);
	apple1->SetPosition(D3DXVECTOR2(GameGlobal::GetWidth() - 25, GameGlobal::GetHeight() - 8));
	apple1->SetScale(D3DXVECTOR2(0.2, 0.15));
	apple1->SetSourceRect(rect);
	apple1->SetWidth(rect.right - rect.left);
	apple1->SetHeight(rect.bottom - rect.top);

	rect.left = 14; rect.top = 1; rect.right = rect.left + 97; rect.bottom = rect.top + 146;
	apple2 = new Sprite("Resources/number.png", Rect(), 0, 0, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5), GameGlobal::mNumbertexture);
	apple2->SetPosition(D3DXVECTOR2(GameGlobal::GetWidth() - 15, GameGlobal::GetHeight() - 8));
	apple2->SetScale(D3DXVECTOR2(0.2, 0.15));
	apple2->SetSourceRect(rect);
	apple2->SetWidth(rect.right - rect.left);
	apple2->SetHeight(rect.bottom - rect.top);

	rect.left = 370; rect.top = 45; rect.right = rect.left + 14; rect.bottom = rect.top + 14;
	apple = new Sprite("Resources/Aladdin.png", Rect(), 0, 0, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5), GameGlobal::mAladdintexture);
	apple->SetPosition(D3DXVECTOR2(GameGlobal::GetWidth() - 50, GameGlobal::GetHeight() - 15));
	apple->SetScale(D3DXVECTOR2(1.5, 1.5));
	apple->SetSourceRect(rect);
	apple->SetWidth(rect.right - rect.left);
	apple->SetHeight(rect.bottom - rect.top);

	//so da do
	rect.left = 14; rect.top = 1; rect.right = rect.left + 97; rect.bottom = rect.top + 146;
	rock1 = new Sprite("Resources/number.png", Rect(), 0, 0, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5), GameGlobal::mNumbertexture);
	rock1->SetPosition(D3DXVECTOR2(GameGlobal::GetWidth() - 80, GameGlobal::GetHeight() - 8));
	rock1->SetScale(D3DXVECTOR2(0.2, 0.15));
	rock1->SetSourceRect(rect);
	rock1->SetWidth(rect.right - rect.left);
	rock1->SetHeight(rect.bottom - rect.top);

	rect.left = 14; rect.top = 1; rect.right = rect.left + 97; rect.bottom = rect.top + 146;
	rock2 = new Sprite("Resources/number.png", Rect(), 0, 0, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5), GameGlobal::mNumbertexture);
	rock2->SetPosition(D3DXVECTOR2(GameGlobal::GetWidth() - 70, GameGlobal::GetHeight() - 8));
	rock2->SetScale(D3DXVECTOR2(0.2, 0.15));
	rock2->SetSourceRect(rect);
	rock2->SetWidth(rect.right - rect.left);
	rock2->SetHeight(rect.bottom - rect.top);

	rect.left = 340; rect.top = 111; rect.right = rect.left + 17; rect.bottom = rect.top + 18;
	rock = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), Rect(), 0, 0, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5), GameGlobal::mItemtexture);
	rock->SetPosition(D3DXVECTOR2(GameGlobal::GetWidth() - 100, GameGlobal::GetHeight() - 15));
	rock->SetScale(D3DXVECTOR2(1.0, 1.0));
	rock->SetSourceRect(rect);
	rock->SetWidth(rect.right - rect.left);
	rock->SetHeight(rect.bottom - rect.top);

	//Mau cua nhan vat
	rect.left = 1037; rect.top = 75; rect.right = rect.left + 50; rect.bottom = rect.top + 26;
	health1 = new Animation(ResourceManager::GetInstance()->GetTextureItems(), 4, loadHealth(1), (float)1 / 0.5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(248, 0, 248));
	health1->SetPosition(35, 20);
	health2 = new Animation(ResourceManager::GetInstance()->GetTextureItems(), 4, loadHealth(2), (float)1 / 0.5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(248, 0, 248));
	health2->SetPosition(40, 20);
	health3 = new Animation(ResourceManager::GetInstance()->GetTextureItems(), 4, loadHealth(3), (float)1 / 0.5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(248, 0, 248));
	health3->SetPosition(45, 20);
	health4 = new Animation(ResourceManager::GetInstance()->GetTextureItems(), 4, loadHealth(4), (float)1 / 0.5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(248, 0, 248));
	health4->SetPosition(50, 20);
	health5 = new Animation(ResourceManager::GetInstance()->GetTextureItems(), 4, loadHealth(5), (float)1 / 0.5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(248, 0, 248));
	health5->SetPosition(55, 20);
	health6 = new Animation(ResourceManager::GetInstance()->GetTextureItems(), 4, loadHealth(6), (float)1 / 0.5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(248, 0, 248));
	health6->SetPosition(60, 20);
	health7 = new Animation(ResourceManager::GetInstance()->GetTextureItems(), 4, loadHealth(7), (float)1 / 0.5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(248, 0, 248));
	health7->SetPosition(65, 20);
	health8 = new Animation(ResourceManager::GetInstance()->GetTextureItems(), 4, loadHealth(8), (float)1 / 0.5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(248, 0, 248));
	health8->SetPosition(70, 20);
	health9 = new Animation(ResourceManager::GetInstance()->GetTextureItems(), 4, loadHealth(9), (float)1 / 0.5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(248, 0, 248));
	health9->SetPosition(75, 20);
	health10 = new Animation(ResourceManager::GetInstance()->GetTextureItems(), 4, loadHealth(10), (float)1 / 0.5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(248, 0, 248));
	health10->SetPosition(80, 20);
	health0 = new Animation(ResourceManager::GetInstance()->GetTextureItems(), 1, loadHealth(0), (float)1 / 0.5, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(248, 0, 248));
	health0->SetPosition(30, 20);
	curHealth = health10;
	mHP = -1;

	//so mang con lai
	rect.left = 340; rect.top = 140; rect.right = 362; rect.bottom = 163;
	Live = new Sprite(ResourceManager::GetInstance()->GetTextureItems(), Rect(), 0, 0, D3DCOLOR_XRGB(248, 0, 248));
	Live->SetPosition(D3DXVECTOR2(15, 220));
	Live->SetScale(D3DXVECTOR2(1, 1));
	Live->SetSourceRect(rect);
	Live->SetWidth(rect.right - rect.left);
	Live->SetHeight(rect.bottom - rect.top);

	rect.left = 14; rect.top = 1; rect.right = rect.left + 97; rect.bottom = rect.top + 146;
	LiveCount = new Sprite("Resources/number.png", Rect(), 0, 0, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5), GameGlobal::mNumbertexture);
	LiveCount->SetPosition(D3DXVECTOR2(40, 228));
	LiveCount->SetScale(D3DXVECTOR2(0.2, 0.15));
	LiveCount->SetSourceRect(rect);
	LiveCount->SetWidth(rect.right - rect.left);
	LiveCount->SetHeight(rect.bottom - rect.top);
	//Diem
	rect.left = 14; rect.top = 1; rect.right = rect.left + 97; rect.bottom = rect.top + 146;
	Snum1 = new Sprite("Resources/number.png", Rect(), 0, 0, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5), GameGlobal::mNumbertexture);
	Snum1->SetPosition(D3DXVECTOR2(278, 15));
	Snum1->SetScale(D3DXVECTOR2(0.2, 0.15));
	Snum1->SetSourceRect(rect);
	Snum1->SetWidth(rect.right - rect.left);
	Snum1->SetHeight(rect.bottom - rect.top);
	Snum2 = new Sprite("Resources/number.png", Rect(), 0, 0, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5), GameGlobal::mNumbertexture);
	Snum2->SetPosition(D3DXVECTOR2(290, 15));
	Snum2->SetScale(D3DXVECTOR2(0.2, 0.15));
	Snum2->SetSourceRect(rect);
	Snum2->SetWidth(rect.right - rect.left);
	Snum2->SetHeight(rect.bottom - rect.top);
	Snum3 = new Sprite("Resources/number.png", Rect(), 0, 0, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5), GameGlobal::mNumbertexture);
	Snum3->SetPosition(D3DXVECTOR2(302, 15));
	Snum3->SetScale(D3DXVECTOR2(0.2, 0.15));
	Snum3->SetSourceRect(rect);
	Snum3->SetWidth(rect.right - rect.left);
	Snum3->SetHeight(rect.bottom - rect.top);
	Snum4 = new Sprite("Resources/number.png", Rect(), 0, 0, D3DCOLOR_XRGB(255, 0, 255), D3DXVECTOR2(0.5, 0.5), GameGlobal::mNumbertexture);
	Snum4->SetPosition(D3DXVECTOR2(314, 15));
	Snum4->SetScale(D3DXVECTOR2(0.2, 0.15));
	Snum4->SetSourceRect(rect);
	Snum4->SetWidth(rect.right - rect.left);
	Snum4->SetHeight(rect.bottom - rect.top);

	myFont = NULL;

	HRESULT rs = D3DXCreateFont(GameGlobal::GetCurrentDevice(), 30, 10, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, (LPCWSTR) "Arial", &myFont);
	if (!SUCCEEDED(rs))
	{
		return;
	}
	myRect.left = 0;
	myRect.top = GameGlobal::GetHeight() - 30;
	myRect.bottom = myRect.top + 200;
	myRect.right = myRect.left + 200;


}


UI::~UI()
{
}

void UI::Update()
{

	if (mHP != mplayer->HPCount / 10)
	{
		mHP = mplayer->HPCount / 10;
		switch (mHP)
		{
		case 1:
			curHealth = health1;
			break;
		case 2:
			curHealth = health2;
			break;
		case 3:
			curHealth = health3;
			break;
		case 4:
			curHealth = health4;
			break;
		case 5:
			curHealth = health5;
			break;
		case 6:
			curHealth = health6;
			break;
		case 7:
			curHealth = health7;
			break;
		case 8:
			curHealth = health8;
			break;
		case 9:
			curHealth = health9;

			break;
		case 10:
			curHealth = health10;
			break;
		case 0:
			curHealth = health0;
			break;
		}
	}
	curHealth->Update(1);

	mRockCount = mplayer->RockCount;

	mAppleCount = mplayer->AppleCount;
	mLiveCount = mplayer->PlayerLiveCount;

	int applenum1 = mAppleCount / 10;
	int applenum2 = mAppleCount % 10;

	apple1->SetSourceRect(LoadNumber(applenum1));
	apple2->SetSourceRect(LoadNumber(applenum2));

	rock1->SetSourceRect(LoadNumber(mRockCount / 10));
	rock2->SetSourceRect(LoadNumber(mRockCount % 10));

	LiveCount->SetSourceRect(LoadNumber(mLiveCount));

	mScore = mplayer->Score;
	int inum1 = mScore / 1000;
	int inum2 = (mScore % 1000) / 100;
	int inum3 = mScore % 100 / 10;
	int inum4 = mScore % 10;
	Snum1->SetSourceRect(LoadNumber(inum1));
	Snum2->SetSourceRect(LoadNumber(inum2));
	Snum3->SetSourceRect(LoadNumber(inum3));
	Snum4->SetSourceRect(LoadNumber(inum4));
	/*EndTime = GetTickCount();
	CurTime += (float) (EndTime - startTime) / 1000;

	message = to_string(CurTime);
	message.replace(message.length()-3,message.length()," s");
	startTime = GetTickCount();*/

}
void UI::Draw()
{

	apple->Draw();
	apple1->Draw();
	apple2->Draw();

	rock->Draw();
	rock1->Draw();
	rock2->Draw();

	Snum1->Draw();
	Snum2->Draw();
	Snum3->Draw();
	Snum4->Draw();

	curHealth->Draw();
	Live->Draw();
	LiveCount->Draw();
	if (myFont)
	{
		myFont->DrawTextA(curHealth->GetSprite()->GetSpriteHandle(), message.c_str(), -1, &myRect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	}
}