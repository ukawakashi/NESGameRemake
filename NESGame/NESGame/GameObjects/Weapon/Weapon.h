#pragma once
#include "../../GameComponents/Animation.h"

#include "WeaponFlyState.h"
#include "WeaponBreakState.h"
class Weapon: public Entity
{
public:
	Weapon(EntityTypes type);
	~Weapon();
	void Update(float dt);
	void SetState(WeaponState::StateName newState/*, EntityTypes type = EntityTypes::None*/);
	
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), Rect sourceRect = Rect(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	Rect GetBound();
	void changeAnim(WeaponState::StateName state);
	void OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side);
	Animation *mCurrentAnim;
	WeaponState* curState;


	vector<Rect> LoadRECT(WeaponState::StateName state);
	bool mReverse;

	WeaponState::StateName GetCurrentState();
private:
	Animation *FlyingAnim,*BreakingAnim;
	

};

