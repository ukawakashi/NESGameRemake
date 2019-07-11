#pragma once
#include "WeaponState.h"

class WeaponFlyState:public WeaponState
{
public:
	WeaponFlyState(D3DXVECTOR3 pos,bool Reverse, Entity::EntityTypes type);
	~WeaponFlyState();
	void Update(float dt);
	WeaponState::StateName GetNameState();
	bool Reverse;
};

