#pragma once
class PeddlerState;
class Peddler;
class PeddlerData
{
public:
	PeddlerData();
	~PeddlerData();
	Peddler      *enemy = nullptr;
	PeddlerState *state = nullptr;
	void Update();
};



