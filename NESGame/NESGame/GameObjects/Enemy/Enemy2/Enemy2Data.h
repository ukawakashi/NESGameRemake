#pragma once
class Enemy2State;
class Enemy2;
class Enemy2Data
{
public:
	Enemy2Data();
	~Enemy2Data();
	Enemy2      *enemy = nullptr;
	Enemy2State *state = nullptr;
	void Update();
};



