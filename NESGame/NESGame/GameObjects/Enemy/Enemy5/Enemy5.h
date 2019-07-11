#pragma once
#include "../../Entity.h"
#include "../../Player/Player.h"
#include "Enemy5State.h"
#include "Enemy5Data.h"
#include "../../../GameComponents/Animation.h"
#include "Enemy5Running.h"
#include "Enemy5Attacked.h"
#include "Enemy5Fighting.h"
#include "Enemy5Die.h"

class Enemy5 :public Entity
{
public:
	Enemy5();
	Enemy5(Player *player, vector<D3DXVECTOR2> listpos);
	~Enemy5();
	void Update();

	void Draw(D3DXVECTOR2 transform = D3DXVECTOR2());

	void SetState(Enemy5State *newState);


	vector<D3DXVECTOR2> mListPosition;
	vector<int> positionted;
	int CurrentPosIndex = -1;
	Rect GetBound();

	Enemy5State::StateName getState();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
	Enemy5Data *mData;
	bool CheckRunning = false;
	bool CheckFire = false;
	bool Reverse = false;

	Animation* GetCurrentAnimation();
	void CheckAction();
	int Heal = 3;

	Enemy5State::StateName mCurrentState;
	Animation  *mCurrentAnimation;
	Weapon *mKnife;
private:
	vector<Rect> LoadRECT(Enemy5State::StateName state);

	Player* mPlayer;
	Animation
		*mAnimationRunning,
		*mAnimationAttack,
		*mAnimationAttacked,
		*mAnimationDied;
	Sprite *mSprite;


	void changeAnimation(Enemy5State::StateName state);
};





