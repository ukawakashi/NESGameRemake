#include "WeaponBreakState.h"



WeaponBreakState::WeaponBreakState(D3DXVECTOR3 pos)
{
	this->pos = pos;
}
void WeaponBreakState::Update(float dt)
{


}

WeaponBreakState::~WeaponBreakState()
{
}

WeaponState::StateName WeaponBreakState::GetNameState()
{
	return WeaponState::Breaking;
}