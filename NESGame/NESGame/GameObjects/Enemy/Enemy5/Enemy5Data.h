#pragma once
class Enemy5State;
class Enemy5;
class Enemy5Data
{
public:
	Enemy5Data();
	~Enemy5Data();
	Enemy5      *enemy = nullptr;
	Enemy5State *state = nullptr;
	void Update();
};



