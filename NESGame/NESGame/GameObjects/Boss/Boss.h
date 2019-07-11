#pragma once
#include "../Entity.h"
#include "../Player/Player.h"
#include "../Boss/BossState.h"
#include "BossSnakeAttack.h"
#include "BossJafarAttack.h"
#include <cstdlib>
#include <ctime>
#include "BossStandJafar.h"
#include "BossStandSnake.h"
#include "FireBurn.h"
class Boss:public Entity
{
public:
	Boss(Player *player, D3DXVECTOR3 pos);
	~Boss();

	void Update();

	void Draw(D3DXVECTOR2 transform = D3DXVECTOR2());

	void SetState(BossState *newState);
	void OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
	BossState::StateName mCurrentState;
	Animation  *mCurrentAnimation;
	Player* mPlayer;
	BossData *mData;
	Animation* GetCurrentAnimation();
	vector<D3DXVECTOR3> starPos;
	Rect GetBound();
	int HPCount =30;
	int currentAmmo = 0;
	vector<FireBurn*> listFireBurn;
	bool Reverse = false;

	Animation *mAnimationStar;
private:
	vector<Rect> LoadRect(BossState::StateName state);
	vector<Rect> LoadRectFire();
	vector<Rect> LoadRectStar();
	Sprite *star1, *star2, *star3;
	Animation
		*mAnimationStandJafar,
		*mAnimationSnakeAttack,
		*mAnimationAttackedSnake,
		*mAnimationStandSnake,
		*mAnimationJafarAttack,
		*mAnimationFire1,
		*mAnimationFire2,
		*mAnimationFire3;
	Sprite *mSprite;
	void DrawStar(D3DXVECTOR2 transform);
	bool BossAttacked = false;
	float lastTimeBossAttacked = 0;
	float lastTimeCreateMeteor = 0;
	void changeAnimation(BossState::StateName state);


};



