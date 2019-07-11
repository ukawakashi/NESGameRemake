#pragma once
#include "../../Entity.h"
#include "../../Player/Player.h"
#include "Enemy2State.h"
#include "Enemy2Data.h"
#include "../../../GameComponents/Animation.h"
#include "Enemy2Running.h"
#include "Enemy2Attacked.h"
#include "Enemy2Fighting.h"
#include "Enemy2Die.h"
#include "Enemy2Beckon.h"
#include "Enemy2WalkHotcoal.h"

class Enemy2 :public Entity
{
public:
	Enemy2();
	Enemy2( Player *player, vector<D3DXVECTOR2> list);
	~Enemy2();
	void Update();

	void Draw(D3DXVECTOR2 transform = D3DXVECTOR2());

	void SetState(Enemy2State *newState);


	vector<D3DXVECTOR2> mListPosition;
	vector<int> positionted;
	int CurrentPosIndex = -1;
	Rect GetBound();

	



	
	Enemy2State::StateName getState();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
	Enemy2Data *mData;
	bool CheckRunning = false;
	bool CheckFire = false;
	bool Reverse = false;
	bool CheckCoal = false;
	bool CheckBecKon = false;

	Animation* GetCurrentAnimation();
	void CheckAction();
	int Heal = 3;

	Enemy2State::StateName mCurrentState;
	Animation  *mCurrentAnimation;
	Enemy2State *randomState;
private:
	vector<Rect> LoadRECT(Enemy2State::StateName state);

	Player* mPlayer;
	Animation
		*mAnimationRunning,
		*mAnimationAttack,
		*mAnimationAttacked,
		*mAnimationDied,
		*mAnimationBenkon,
		*mAnimationWalkHotcoal;
	Sprite *mSprite;


	void changeAnimation(Enemy2State::StateName state);
};






