
#pragma once

#include "Sprite.h"
#include "../GameObjects/Player/Player.h"
class UI
{
public:
	UI(Player* player);
	void Update();
	void Draw();
	int mHP, mAppleCount, mRockCount, mLiveCount, mScore;
	Player* mplayer;
	Sprite *apple1, *apple2, *apple,
		*rock1, *rock2, *rock,
		*Snum1, *Snum2, *Snum3, *Snum4,
		*GoldenLamp, *Live, *LiveCount;


	~UI();
	Animation *health1, *health2, *health3, *health4, *health5, *health6, *health7, *health8, *health9, *health10, *health0, *curHealth;
	ID3DXFont				*myFont;
	RECT myRect;
	LPD3DXSPRITE mSpriteHandler = GameGlobal::GetCurrentSpriteHandler();
	int startTime;
	int EndTime;
	float CurTime = 0;
	std::string message;

};

