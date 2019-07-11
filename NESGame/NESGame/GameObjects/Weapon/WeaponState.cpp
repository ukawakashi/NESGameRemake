#include "WeaponState.h"



WeaponState::WeaponState()
{
}


WeaponState::~WeaponState()
{
}
void WeaponState::Update(float dt)
{

}
D3DXVECTOR3 WeaponState::getPos()
{
	return pos;
}

WeaponState::StateName WeaponState::GetNameState()
{
	return StateName::NONE;
}
void WeaponState::SetVx(float x)
{
	vX = x;
}