#pragma once
#ifndef _MY_RECT_H__
#define _MY_RECT_H__
#include <d3dx9.h>
#include <d3d9.h>
#include "GameGlobal.h"
class Rect :public RECT
{
public:
	Rect();
	Rect(float top, float left, float right, float bottom, D3DXVECTOR3 center = D3DXVECTOR3(-1, -1, 0));
	~Rect();
	void					Set(float top, float left, float right, float bottom, D3DXVECTOR3 center = D3DXVECTOR3(0, 0, 0));
	void					SetCenter(float x = 0, float y = 0, float z = 0);
	bool					IsCollision(Rect rect);
	D3DXVECTOR3				mCenter;
};

#endif _MY_RECT_H__