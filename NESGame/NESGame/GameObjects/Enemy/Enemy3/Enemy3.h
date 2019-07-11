#pragma once
#include "../../Entity.h"
#include "../../Player/Player.h"
#include "Enemy3State.h"
#include "Enemy3Data.h"
#include "../../../GameComponents/Animation.h"
#include "Enemy3Running.h"
#include "Enemy3Attacked.h"
#include "Enemy3Fighting.h"
#include "Enemy3Die.h"

class Enemy3 :public Entity
{
public:
	Enemy3();
	Enemy3(Player *player, vector<D3DXVECTOR2> list);
	~Enemy3();
	void Update();

	void Draw(D3DXVECTOR2 transform = D3DXVECTOR2());

	void SetState(Enemy3State *newState);


	vector<D3DXVECTOR2> mListPosition;
	vector<int> positionted;
	int CurrentPosIndex = -1;
	Rect GetBound();

	Enemy3State::StateName getState();

	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
	Enemy3Data *mData;
	bool CheckRunning = false;
	bool CheckFire = false;
	bool Reverse = false;

	Animation* GetCurrentAnimation();
	void CheckAction();
	int Heal = 3;

	Enemy3State::StateName mCurrentState;
	Animation  *mCurrentAnimation;
	Weapon *mKnife;
private:
	vector<Rect> LoadRECT(Enemy3State::StateName state);

	Player* mPlayer;
	Animation
		*mAnimationRunning,
		*mAnimationAttack,
		*mAnimationAttacked,
		*mAnimationDied;
	Sprite *mSprite;


	void changeAnimation(Enemy3State::StateName state);
};






