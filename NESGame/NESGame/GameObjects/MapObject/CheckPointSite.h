#pragma once

#include "AppleObject.h"
class CheckPointSite : public SimpleObject
{
public:
	CheckPointSite();
	~CheckPointSite();
	Rect GetBound();
	vector<Rect> LoadRect();
	void OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side);
	void Update();
};



