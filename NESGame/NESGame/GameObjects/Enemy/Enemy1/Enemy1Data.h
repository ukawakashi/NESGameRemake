#pragma once
class Enemy1State;
class Enemy1;

class Enemy1Data
{
public:
	Enemy1Data();
	~Enemy1Data();

	Enemy1      *enemy = nullptr;
	Enemy1State *state = nullptr;
	void Update();
};

