#pragma once
class Enemy3State;
class Enemy3;
class Enemy3Data
{
public:
	Enemy3Data();
	~Enemy3Data();
	Enemy3      *enemy = nullptr;
	Enemy3State *state = nullptr;
	void Update();
};



