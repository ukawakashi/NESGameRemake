#pragma once
#ifndef __GAME_GLOBAL__
#define __GAME_GLOBAL__
#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>
#include "Scene.h"
class GameGlobal
{
public:
	GameGlobal();
	~GameGlobal();

	static HINSTANCE GetCurrentHINSTACE();
	static HWND getCurrentHWND();

	static void SetCurrentHINSTACE(HINSTANCE hInstance);
	static void SetCurrentHWND(HWND hWnd);

	static void SetCurrentSpriteHandler(LPD3DXSPRITE spriteHandler);
	static LPD3DXSPRITE GetCurrentSpriteHandler();

	static void SetCurrentDevice(LPDIRECT3DDEVICE9 device);
	static LPDIRECT3DDEVICE9 GetCurrentDevice();

	static void SetWidth(int width);
	static int GetWidth();

	static void SetHeight(int height);
	static int GetHeight();

	static LPDIRECT3DSURFACE9 backSurface;

	static bool isGameRunning; //trang thai xem game co dang chay khong
	static LPDIRECT3DTEXTURE9 mAladdintexture;
	static LPDIRECT3DTEXTURE9 mEnemytexture;
	static LPDIRECT3DTEXTURE9 mMaptexture;
	static LPDIRECT3DTEXTURE9 mFlaretexture;
	static LPDIRECT3DTEXTURE9 mCiviliantexture;
	static LPDIRECT3DTEXTURE9 mCameltexture;
	static LPDIRECT3DTEXTURE9 mFlagPoletexture;
	static LPDIRECT3DTEXTURE9 mItemtexture;
	static LPDIRECT3DTEXTURE9 mNumbertexture;
	static LPDIRECT3DTEXTURE9 mJafartexture;
	static LPDIRECT3DTEXTURE9 mPeddlertexture;
	//static LPDIRECT3DTEXTURE9 mScenetexture;
private:
	static HINSTANCE mHInstance; //hInstance của windows hiện tại
	static HWND mHwnd; // hwnd hiện tại
	static LPD3DXSPRITE mSpriteHandler; //spriteHanlder hiện tại
	static int mWidth, mHeight; //size của cửa sổ
	static LPDIRECT3DDEVICE9 mDevice; //device directX hiện tại



};

#endif

