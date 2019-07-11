#pragma once
#include "AppleObject.h"
class FlagPole: public SimpleObject
{
public:
	FlagPole();
	~FlagPole();

	Rect GetBound();
	vector<Rect> LoadRect();
	void OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side);
	void Update();
};



