#pragma once
#include "../../../GameComponents/Animation.h"
#include "../../Entity.h"
#include "../../Weapon/Weapon.h"
#include "../../Player/Player.h"
#include "PeddlerData.h"
#include "PeddlerSell.h"
#include "PeddlerStand1.h"
#include "PeddlerStand2.h"
#include "PeddlerState.h"
class Peddler:public Entity
{
public:
	Peddler();
	Peddler(Player *player, vector<D3DXVECTOR2> list);
	~Peddler();
	//Animation* StandAnimate,*ShellAnimate;
	//Animation* mCurrentAnimate;
	//bool AllowStand = true;
	//bool AllowShell = false;
	//void Update(Entity* player);
	//vector<Rect> LoadRect(bool flag);
	//void CheckSite(Entity* player);
	//void Draw(D3DXVECTOR3 position, Rect sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey);
	//void OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side);
	//vector<D3DXVECTOR2> mListPosition;
	void Update();

	void Draw(D3DXVECTOR2 transform = D3DXVECTOR2());

	void SetState(PeddlerState *newState);


	vector<D3DXVECTOR2> mListPosition;
	vector<int> positionted;

	int CurrentPosIndex = -1;
	Rect GetBound();
	PeddlerState::StateName getState();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
	PeddlerData *mData;
	bool CheckStand1 = false;
	bool CheckStand2 = false;
	bool Reverse = false;
	bool CheckSell = false;

	Animation* GetCurrentAnimation();
	void CheckAction();
	int Heal = 3;

	PeddlerState::StateName mCurrentState;
	Animation  *mCurrentAnimation,*mTemp;
	PeddlerState *randomState;
private:
	vector<Rect> LoadRECT(PeddlerState::StateName state);

	Player* mPlayer;
	Animation
		*mAnimationStand1,
		*mAnimationStand2,
		*mAnimationSell;

	Sprite *mSprite;


	void changeAnimation(PeddlerState::StateName state);
};

