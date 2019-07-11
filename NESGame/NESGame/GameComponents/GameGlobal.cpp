#include "GameGlobal.h"

HINSTANCE GameGlobal::mHInstance = NULL;
HWND GameGlobal::mHwnd = NULL;
LPD3DXSPRITE GameGlobal::mSpriteHandler = NULL;
int GameGlobal::mWidth = 320; //900 test //400
int GameGlobal::mHeight = 240; //600 test  //225
LPDIRECT3DDEVICE9 GameGlobal::mDevice = nullptr;
bool GameGlobal::isGameRunning = true;
IDirect3DSurface9* GameGlobal::backSurface = nullptr;
LPDIRECT3DTEXTURE9 GameGlobal::mAladdintexture = NULL;
LPDIRECT3DTEXTURE9 GameGlobal::mEnemytexture = NULL;
LPDIRECT3DTEXTURE9 GameGlobal::mMaptexture = NULL;
LPDIRECT3DTEXTURE9 GameGlobal::mFlaretexture = NULL;
LPDIRECT3DTEXTURE9 GameGlobal::mCiviliantexture = NULL;
LPDIRECT3DTEXTURE9 GameGlobal::mCameltexture = NULL;
LPDIRECT3DTEXTURE9 GameGlobal::mFlagPoletexture = NULL;
LPDIRECT3DTEXTURE9 GameGlobal::mItemtexture = NULL;
LPDIRECT3DTEXTURE9 GameGlobal::mNumbertexture = NULL;
LPDIRECT3DTEXTURE9 GameGlobal::mJafartexture = NULL;
LPDIRECT3DTEXTURE9 GameGlobal::mPeddlertexture = NULL;
GameGlobal::GameGlobal()
{
	if (mSpriteHandler)
	{

		LPDIRECT3DDEVICE9 device;
		mSpriteHandler->GetDevice(&device);


		D3DXCreateTextureFromFileExA(
			device,
			"Resources/Aladdin.png",
			1121,
			2718,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(255, 0, 255),
			NULL,
			NULL,
			&mAladdintexture);


		D3DXCreateTextureFromFileExA(
			device,
			"Resources/guard.png",
			498,
			1053,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(120, 193, 152),
			NULL,
			NULL,
			&mEnemytexture);

		D3DXCreateTextureFromFileExA(
			device,
			"Resources/AgrabahMarket.png",
			4773,
			1383,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(63, 72, 204),
			NULL,
			NULL,
			&mMaptexture);

		D3DXCreateTextureFromFileExA(
			device,
			"Resources/flare.png",
			658,
			324,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(186, 254, 202),
			NULL,
			NULL,
			&mFlaretexture);


		D3DXCreateTextureFromFileExA(
			device,
			"Resources/civilian.png",
			1065,
			588,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(120, 193, 152),
			NULL,
			NULL,
			&mCiviliantexture);


		D3DXCreateTextureFromFileExA(
			device,
			"Resources/Items/Camel.png",
			882,
			99,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(248, 0, 248),
			NULL,
			NULL,
			&mCameltexture);

		D3DXCreateTextureFromFileExA(
			device,
			"Resources/FlagPole.png",
			171,
			36,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(255, 0, 255),
			NULL,
			NULL,
			&mFlagPoletexture);


		D3DXCreateTextureFromFileExA(
			device,
			"Resources/item.png",
			664,
			474,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(248, 0, 248),
			NULL,
			NULL,
			&mItemtexture);

		D3DXCreateTextureFromFileExA(
			device,
			"Resources/Items/Peddler.png",
			943,
			482,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(255, 0, 255),
			NULL,
			NULL,
			&mPeddlertexture);



		D3DXCreateTextureFromFileExA(
			device,
			"Resources/number.png",
			989,
			121,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(255, 0, 255),
			NULL,
			NULL,
			&mNumbertexture);

		D3DXCreateTextureFromFileExA(
			device,
			"Resources/jafar.png",
			863,
			348,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(186, 254, 202),
			NULL,
			NULL,
			&mJafartexture);



	}

}


GameGlobal::~GameGlobal()
{
}

void GameGlobal::SetCurrentDevice(LPDIRECT3DDEVICE9 device)
{
	mDevice = device;
}

LPDIRECT3DDEVICE9 GameGlobal::GetCurrentDevice()
{
	return mDevice;
}


HINSTANCE GameGlobal::GetCurrentHINSTACE()
{
	return mHInstance;
}

HWND GameGlobal::getCurrentHWND()
{
	return mHwnd;
}

void GameGlobal::SetCurrentHINSTACE(HINSTANCE hInstance)
{
	mHInstance = hInstance;
}

void GameGlobal::SetCurrentHWND(HWND hWnd)
{
	mHwnd = hWnd;
}

void GameGlobal::SetCurrentSpriteHandler(LPD3DXSPRITE spriteHandler)
{
	mSpriteHandler = spriteHandler;
}

LPD3DXSPRITE GameGlobal::GetCurrentSpriteHandler()
{
	return mSpriteHandler;
}

void GameGlobal::SetWidth(int width)
{
	mWidth = width;
}

int GameGlobal::GetWidth()
{
	return mWidth;
}

void GameGlobal::SetHeight(int height)
{
	mHeight = height;
}

int GameGlobal::GetHeight()
{
	return mHeight;
}
