#include "WeaponState.h"
class WeaponBreakState :public WeaponState
{
public:
	WeaponBreakState(D3DXVECTOR3 pos);
	~WeaponBreakState();
	void Update(float dt);
	WeaponState::StateName GetNameState();
};

