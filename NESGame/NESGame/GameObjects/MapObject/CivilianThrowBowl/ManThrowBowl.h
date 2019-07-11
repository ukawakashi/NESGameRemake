#pragma once
#include "../../../GameComponents/Animation.h"
#include "../../Entity.h"
#include "../../Weapon/Weapon.h"
#include "../../Player/Player.h"
class ManThrowBowl:public Entity
{
public:
	ManThrowBowl(vector<D3DXVECTOR2> listpos);
	~ManThrowBowl();
	Animation* ThrowAnimate,*DieAnimate;
	Animation* mCurrentAnimate;
	bool AllowThrow = true;
	void Update(Entity* player);
	vector<Rect> LoadRect(bool flag);
	void CheckSite(Entity* player);
	void Draw(D3DXVECTOR3 position, Rect sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey);
	int HP = 2;
	void OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side);
	vector<D3DXVECTOR2> mListPosition;
	Weapon* mWeapon;
	Weapon* mCurrentWeapon;
	Player* mPlayer;

	Rect GetBound();
};

