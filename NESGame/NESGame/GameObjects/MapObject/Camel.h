#pragma once
#include "AppleObject.h"
class Camel: public SimpleObject
{

public:
	Camel(const char* filePath,
	float timePerFrame = 1 / 20,
	D3DXVECTOR2 center = D3DXVECTOR2(0.5, 0.5));
	vector<Rect> LoadRect();
	void OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side);
	void Update();
	Rect GetBound();
	~Camel();
};

