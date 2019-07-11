#pragma once
#include "../../../GameComponents/Animation.h"
#include "../../Entity.h"
#include "../../Weapon/Weapon.h"
#include "../../Player/Player.h"
class Peddler1:public Entity
{
public:
	Peddler1(vector<D3DXVECTOR2> listpos);
	~Peddler1();
	Animation* Stand1Animate, *Stand2Animate,*ShellAnimate,*Sell2Animate;
	Animation* mCurrentAnimate,*mTemp;
	bool AllowStand1 = false;
	bool AllowShell = false,AllowSell2=false;
	bool AllowStand2 = false;
	void Update(Entity* player);
	vector<Rect> LoadRect(int flag);
	void CheckSite(Entity* player);
	void Draw(D3DXVECTOR3 position, Rect sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey);
	void OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side);
	vector<D3DXVECTOR2> mListPosition;
	Player* mPlayer;
	bool isActive = false;
	Rect GetBound();
};

