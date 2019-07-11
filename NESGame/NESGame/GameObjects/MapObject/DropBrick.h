#pragma once
#include "../Entity.h"
#include "../../GameComponents/Sprite.h"
class DropBrick:public Entity
{
public:
	DropBrick(D3DXVECTOR2 startPOS);
	~DropBrick();
	void Draw(D3DXVECTOR2 tran, D3DXVECTOR2 Scale);
	void Update();
	void OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side);
	Sprite* Brick;
	D3DXVECTOR2 mStartPOS;
	bool FlagActive = false, check = false;
	int mDelay = 0;
};

