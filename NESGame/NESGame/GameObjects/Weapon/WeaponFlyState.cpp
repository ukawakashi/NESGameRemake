#include "WeaponFlyState.h"
#include <ctime>


WeaponFlyState::WeaponFlyState(D3DXVECTOR3 pos,bool reverse, Entity::EntityTypes type)
{
	this->pos = pos;
	if (type == Entity::AppleThrow || type == Entity::KnifeEnemy3)
	{
		acceX = 3.2f;
		acceY = 0.025f;
	}
	else if(type==Entity::Bowl)
	{
		acceX = 0.2f;
		acceY = 0.4f;
	}
	else if (type == Entity::CamelSpit)
	{
		acceX =8.0f;
		acceY = 0.0f;
	}
	Reverse = reverse;
}
void WeaponFlyState::Update(float dt)
{

	vY += acceY;
	pos.y += vY;
	if(!Reverse)
	pos.x += acceX;
	else pos.x -= acceX;
}

WeaponFlyState::~WeaponFlyState()
{

}

WeaponState::StateName WeaponFlyState::GetNameState()
{
	return WeaponState::Flying;
}