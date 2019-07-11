#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerRunJumpState.h"

vector<Rect> LoadRect(PlayerState::StateName state)
{
	vector<Rect> listSourceRect;
	Rect rect;
	//bmoi sua
	switch (state)
	{
	case PlayerState::Standing:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Stand");//50
		break;
	case PlayerState::Throwing:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Throwing");
		break;
	case PlayerState::Attack:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Attack");
		break;
	case PlayerState::UpAttack:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "UpAttack");
		break;
	case PlayerState::LookUp:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "LookUp");
		break;
	case PlayerState::Sit:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Sit");
		break;
	case PlayerState::SitThrow:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "SitThrow");
		break;
	case PlayerState::SitFight:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "SitFight");
		break;
	case PlayerState::RunJump:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "RunJump");
		break;
	case PlayerState::Jumping:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Jumping");
		break;
	case PlayerState::Falling:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Falling");
		break;
	case PlayerState::Landing:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Landing");
		break;
	case PlayerState::JumpThrow:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "JumpThrow");
		break;
	case PlayerState::JumpFight:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "JumpFight");
		break;
	case PlayerState::JumpPole:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Flip");
		break;
	case PlayerState::Running:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Running");
		break;
	case PlayerState::Stopping:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Stopping");
		break;
	case PlayerState::Climbing:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Climbing");
		break;
	case PlayerState::FallClimb:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "FallClimb");
		break;
	case PlayerState::FallAction:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "FallAction");
		break;
	case PlayerState::ClimbingHori:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "HoriClimbing");
		break;
	case PlayerState::StandHori:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "HoriStanding");
		break;
	case PlayerState::ThrowClimb:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "HoriThrow");
		break;
	case PlayerState::AttackClimb:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "HoriAttack");
		break;
	case PlayerState::JumpClimb:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "JumpClimb");
		break;
	case PlayerState::Pushing:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Pushing");
		break;
	case PlayerState::Fired:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Fired");
		break;
	case PlayerState::Sit2:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Sit2");
	case PlayerState::Attacked:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Attacked");
	case PlayerState::Die:
		break;
	case PlayerState::Revive:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Revive");
		break;
	case PlayerState::Win:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "Win");
		break;
	case PlayerState::FlyingBlack:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "FlyingBlack");
		break;
	case PlayerState::KissPrincess:
		listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "KissPrincess");
		break;
	default:
		break;
	}

	return listSourceRect;
}


int curApple = 0;
Player::Player()
{
	//bmoi sua
	mAnimationStanding = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 50, LoadRect(PlayerState::Standing), (float)1 / 15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::Entity::EntityTypes::PlayerOne);
	mAnimationThrowing = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 6, LoadRect(PlayerState::Throwing), (float)1 / 25, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationAttack = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 5, LoadRect(PlayerState::Attack), (float)1 / 20, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationUpAttack = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 28, LoadRect(PlayerState::UpAttack), (float)1 / 15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationLookUp = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 3, LoadRect(PlayerState::LookUp), (float)1 / 20, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationSiting = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 4, LoadRect(PlayerState::Sit), (float)1 / 20, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationSitThrow = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 5, LoadRect(PlayerState::SitThrow), (float)1 / 20, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationSitFight = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 7, LoadRect(PlayerState::SitFight), (float)1 / 20, D3DXVECTOR2(0.2, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationRunJump = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 7, LoadRect(PlayerState::RunJump), (float)1 / 10, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::Entity::EntityTypes::PlayerOne);
	mAnimationJumping = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 6, LoadRect(PlayerState::Jumping), (float)1 / 10, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::Entity::EntityTypes::PlayerOne);
	mAnimationFalling = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 4, LoadRect(PlayerState::Falling), (float)1 / 10, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationFallAction = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 1, LoadRect(PlayerState::FallAction), (float)1 / 10, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationFallClimb = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 9, LoadRect(PlayerState::FallClimb), (float)1 / 15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationLanding = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 12, LoadRect(PlayerState::Landing), (float)1 / 2, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationJumpThrow = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 6, LoadRect(PlayerState::JumpThrow), (float)1 / 30, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationJumpFight = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 7, LoadRect(PlayerState::JumpFight), (float)1 / 20, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationJumpPole = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 8, LoadRect(PlayerState::JumpPole), (float)1 / 15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationRunning = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 13, LoadRect(PlayerState::Running), (float)1 / 35, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationClimbing = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 10, LoadRect(PlayerState::Climbing), (float)1 / 30, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationClimbHori = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 9, LoadRect(PlayerState::ClimbingHori), (float)1 / 15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationThrowClimb = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 6, LoadRect(PlayerState::ThrowClimb), (float)1 / 15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationAttackClimb = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 7, LoadRect(PlayerState::AttackClimb), (float)1 / 25, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationJumpClimb = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 3, LoadRect(PlayerState::JumpClimb), (float)1 / 10, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationPushing = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 9/*8*/, LoadRect(PlayerState::Pushing), (float)1 / 15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationFired = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 8, LoadRect(PlayerState::Fired), (float)1 / 15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationSit2 = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 6, LoadRect(PlayerState::Sit2), (float)1 / 15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationAttacked = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 6, LoadRect(PlayerState::Attacked), (float)1 / 15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationRevive = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 14, LoadRect(PlayerState::Revive), (float)1 / 15, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	mAnimationStandHori = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 8, LoadRect(PlayerState::StandHori), (float)1 / 10, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes::PlayerOne);
	
	Tag = Entity::EntityTypes::PlayerOne;
	this->mPlayerData = new PlayerData();
	this->mPlayerData->player = this;
	this->vx = 0;
	this->vy = 0;
	this->SetState(new PlayerFallingState(this->mPlayerData));

	listWeapon.push_back(new Weapon(Entity::AppleThrow));
	listWeapon.push_back(new Weapon(Entity::AppleThrow));
	listWeapon.push_back(new Weapon(Entity::AppleThrow));


	mSplit = new Weapon(Entity::CamelSpit);
	
	allowJump = true;
	allowThrow = true;


	CheckPoint = D3DXVECTOR2(50, 300);
}

Player::~Player()
{
	mCurrentAnimation = mAnimationStanding = mAnimationRunning = mAnimationJumping = mAnimationRunJump = mAnimationFalling = mAnimationFallClimb = mAnimationThrowing
		= mAnimationClimbing = mAnimationSiting = mAnimationAttack = mAnimationSitFight = mAnimationJumpThrow = mAnimationSitThrow = mAnimationFired
		= mAnimationJumpPole = mAnimationClimbHori = mAnimationRevive = mAnimationStandHori = mAnimationLookUp = mAnimationUpAttack = mAnimationPushing = mAnimationFallAction = NULL;

	delete mAnimationStanding, mAnimationJumping, mAnimationRunJump, mAnimationRunning, mAnimationThrowing, mAnimationClimbing, mAnimationAttack, mAnimationSiting,
		mAnimationSitFight, mAnimationJumpThrow, mAnimationSitThrow, mAnimationFired, mAnimationThrowClimb, mAnimationJumpPole, mAnimationClimbHori,
		mAnimationRevive, mAnimationFalling, mAnimationFallClimb, mAnimationStandHori, mAnimationLookUp, mAnimationUpAttack, mAnimationPushing, mAnimationFallAction;
}

void Player::Update(float dt)
{

	LastPosition = D3DXVECTOR2(GetPosition().x, GetPosition().y);
	
	if (this->mPlayerData->state)
	{
		this->mPlayerData->state->Update(dt);
	}
	mCurrentAnimation->Update(dt);
	mSplit->Update(dt);
	Entity::Update(dt);
	for (int i = 0; i < listWeapon.size(); i++)
	{
		Weapon *temp = listWeapon.at(i);
	
		temp->Update(dt);
		if (temp->GetCurrentState() == WeaponState::NONE)
		{
			temp->SetPosition(D3DXVECTOR3(0, posY - 30, 0));
		}
	}
	if (HPCount > 100) HPCount = 100;
	if (HPCount == 0)
	{
		HPCount = 100;
		SetPosition(CheckPoint);
		SetState(new PLayerRevive(mPlayerData));
	}
	
}

void Player::HandleKeyboard(std::map<int, bool> keys)
{
	if (this->mPlayerData->state)
	{
		this->mPlayerData->state->HandleKeyboard(keys);
	}
}

void Player::OnKeyPressed(int key)
{

	//Nhay
	if (key == VK_SPACE)
	{	
		if (allowJump)
		{
			if (mCurrentState == PlayerState::Standing)
			{
				//vx = 150;
				this->mPlayerData->player->GetCurrentAnimation()->Reset();
				this->SetState(new PlayerJumpingState(this->mPlayerData));
			}
			if (mCurrentState == PlayerState::LookUp)
			{
				//vx = 150;
				this->mPlayerData->player->GetCurrentAnimation()->Reset();
				this->SetState(new PlayerJumpingState(this->mPlayerData));
			}
			if (mCurrentState == PlayerState::Running)
			{
				//vx = 150;
				this->mPlayerData->player->GetCurrentAnimation()->Reset();
				this->SetState(new PlayerRunJumpState(this->mPlayerData));
			}
			allowJump = false;
		}

	}
	//Nem tao
	if (key == VkKeyScan('z'))
	{
		ResourceManager::GetInstance()->playSound("AladdinThrowApple", false, 1);
		if (GetTickCount() - lastTimeThrow >= 500)
		{
			if (allowThrow)
			{

				if (AppleCount < 1) return;
				if (curApple > 2)
					curApple = 0;

				if (mCurrentState == PlayerState::ClimbingHori )
				{
					/*listWeapon.at(curApple)->SetPosition(D3DXVECTOR2(posX, posY));
					listWeapon.at(curApple)->mReverse = !mCurrentReverse;
					listWeapon.at(curApple)->SetState(WeaponState::Flying);
					curApple++;
					AppleCount--;*/
					return;
				}
				else
					listWeapon.at(curApple)->SetPosition(D3DXVECTOR2(posX, posY - 50));
				if (mCurrentState == PlayerState::Sit || mCurrentState == PlayerState::SitThrow)
					listWeapon.at(curApple)->SetPosition(D3DXVECTOR2(posX, posY - 30));
				listWeapon.at(curApple)->mReverse = mCurrentReverse;
				listWeapon.at(curApple)->SetState(WeaponState::Flying);
				curApple++;
				AppleCount--;
			}
			allowThrow = false;
			lastTimeThrow = GetTickCount();
		}
		else return;
	}
	//if (key == VK_NUMPAD5) HPCount = 0;
}

void Player::OnKeyUp(int key)
{
	if (key == VK_SPACE)
	{
	
		allowJump = true;
	}
	

	if (key == VkKeyScan('z'))
	{
		allowThrow = true;
	}
}



void Player::Draw(D3DXVECTOR3 position, Rect sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
		GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);


	if(mCurrentState!=PlayerState::ThrowClimb)
	mCurrentAnimation->GetSprite()->FlipVertical(mCurrentReverse);
	else mCurrentAnimation->GetSprite()->FlipVertical(!mCurrentReverse);


	mCurrentAnimation->SetPosition(this->GetPosition());
	if (isAttacked)
	{

		if (Count_temp % 2 == 0)
		{
			if (mCamera)
				mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
		}
		Count_temp++;
		if (Count_temp >16)
		{
			Count_temp = 0;
			isAttacked = false;
		}
	}
	else
		mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);

	for (int i = 0; i < listWeapon.size(); i++)
		listWeapon.at(i)->Draw(listWeapon.at(i)->GetPosition(), sourceRect, scale, trans, angle, rotationCenter, colorKey);
	
	mSplit->Draw(mSplit->GetPosition(), sourceRect, scale, trans, angle, rotationCenter, colorKey);
	

}

void Player::SetState(PlayerState *newState)
{
	delete this->mPlayerData->state;

	this->mPlayerData->state = newState;

	this->changeAnimation(newState->GetState());

	mCurrentState = newState->GetState();
}

Rect Player::GetBound()
{
	Rect rect;
	if (mCurrentState == PlayerState::ClimbingHori)
	{
		rect.left = this->posX - mCurrentAnimation->GetSprite()->GetWidth() / 2;
		rect.right = rect.left + mCurrentAnimation->GetSprite()->GetWidth();
		rect.bottom = this->posY+ mCurrentAnimation->GetSprite()->GetHeight();  //Chú ý đoạn này
		rect.top = this->posY;// + mCurrentAnimation->GetSprite()->GetHeight() / 2;

		float cWidth = this->posX;
		float cHeight = this->posY + mCurrentAnimation->GetSprite()->GetHeight() / 2;
		SetCenter(D3DXVECTOR2(cWidth, cHeight));
		return rect;
	}
	rect.left = this->posX - mCurrentAnimation->GetSprite()->GetWidth() / 2;
	rect.right = rect.left + mCurrentAnimation->GetSprite()->GetWidth();
	rect.top = this->posY - mCurrentAnimation->GetSprite()->GetHeight(); //Chú ý đoạn này
	rect.bottom = this->posY;// + mCurrentAnimation->GetSprite()->GetHeight() / 2;

	float cWidth = this->posX;
	float cHeight= this->posY- mCurrentAnimation->GetSprite()->GetHeight()/2;
	SetCenter(D3DXVECTOR2(cWidth, cHeight));
	return rect;
}

void Player::changeAnimation(PlayerState::StateName state)
{
	if (AppleCount == 0 && PlayerState::isThrowing(state))
	{
		return;
	}
	switch (state)
	{
	case PlayerState::Standing:
		mCurrentAnimation = mAnimationStanding;
		//ResourceManager::GetInstance()->playSound("AladdinRevive", false, 1);
		break;
	case PlayerState::Throwing:
		mCurrentAnimation = mAnimationThrowing;
		Sound::getInstance()->play("AladdinThrowApple", false, 1);
		break;
	case PlayerState::Attack:
		mCurrentAnimation = mAnimationAttack;
		ResourceManager::GetInstance()->playSound("LowSword", false, 1);
		break;
	case PlayerState::UpAttack:
		mCurrentAnimation = mAnimationUpAttack;
		ResourceManager::GetInstance()->playSound("HighSword", false, 1);
		break;
	case PlayerState::LookUp:
		mCurrentAnimation = mAnimationLookUp;
		break;
	case PlayerState::Sit:
		mCurrentAnimation = mAnimationSiting;
		break;
	case PlayerState::SitThrow:
		mCurrentAnimation = mAnimationSitThrow;
		Sound::getInstance()->play("AladdinThrowApple", false, 1);
		break;
	case PlayerState::SitFight:
		mCurrentAnimation = mAnimationSitFight;
		ResourceManager::GetInstance()->playSound("LowSword", false, 1);
		break;
	case PlayerState::RunJump:
		mCurrentAnimation = mAnimationRunJump;
		break;
	case PlayerState::Jumping:
		mCurrentAnimation = mAnimationJumping;
		break;
	case PlayerState::Falling:
		mCurrentAnimation = mAnimationFalling;
		break;
	case PlayerState::FallAction:
		mCurrentAnimation = mAnimationFallAction;
		break;
	case PlayerState::FallClimb:
		mCurrentAnimation = mAnimationFallClimb;
		break;
	case PlayerState::Landing:
		mCurrentAnimation = mAnimationLanding;
		Sound::getInstance()->play("AladdinLanding", false, 1);
		break;
	case PlayerState::JumpThrow:
		mCurrentAnimation = mAnimationJumpThrow;
		Sound::getInstance()->play("AladdinThrowApple", false, 1);
		break;
	case PlayerState::JumpFight:
		mCurrentAnimation = mAnimationJumpFight;
		ResourceManager::GetInstance()->playSound("LowSword", false, 1);
		break;
	case PlayerState::JumpPole:
		mCurrentAnimation = mAnimationJumpPole;
		ResourceManager::GetInstance()->playSound("AladdinPole", false, 1);
		break;
	case PlayerState::Running:
		mCurrentAnimation = mAnimationRunning;
		break;
	case PlayerState::Climbing:
		mCurrentAnimation = mAnimationClimbing;
		break;
	case PlayerState::ClimbingHori:
		mCurrentAnimation = mAnimationClimbHori;
		break;
	case PlayerState::StandHori:
		mCurrentAnimation = mAnimationStandHori;
		break;
	case PlayerState::ThrowClimb:
		mCurrentAnimation = mAnimationThrowClimb;
		Sound::getInstance()->play("AladdinThrowApple", false, 1);
		break;
	case PlayerState::AttackClimb:
		mCurrentAnimation = mAnimationAttackClimb;
		ResourceManager::GetInstance()->playSound("LowSword", false, 1);
		break;
	case PlayerState::JumpClimb:
		mCurrentAnimation = mAnimationJumpClimb;
		break;
	case PlayerState::Pushing:
		mCurrentAnimation = mAnimationPushing;
		Sound::getInstance()->play("AladdinPush", false, 1);
		break;
	case PlayerState::Fired:
		mCurrentAnimation = mAnimationFired;
		Sound::getInstance()->play("CoalFire", false, 1);
		break;
	case PlayerState::Sit2:
		mCurrentAnimation = mAnimationSit2;
		break;
	case PlayerState::Attacked:
		mCurrentAnimation = mAnimationAttacked;
		Sound::getInstance()->play("AladdinAttacked", false, 1);
		break;
	case PlayerState::Revive:
		mCurrentAnimation = mAnimationRevive;
		ResourceManager::GetInstance()->playSound("AladdinRevive", false, 1);
		break;
	}

	this->width = mCurrentAnimation->GetSprite()->GetWidth();
	this->height = mCurrentAnimation->GetSprite()->GetHeight();
}

Player::MoveDirection Player::getMoveDirection()
{
	if (this->vx > 0)
	{
		return MoveDirection::MoveToRight;
	}
	else if (this->vx < 0)
	{
		return MoveDirection::MoveToLeft;
	}

	return MoveDirection::None;
}

PlayerState::StateName Player::getState()
{
	return mCurrentState;
}

PlayerData* Player::GetCurrentPlayerData()
{
	return mPlayerData;
}
void Player::SetCamera(Camera *camera)
{
	this->mCamera = camera;
}

Animation* Player::GetCurrentAnimation()
{
	return mCurrentAnimation;
}
bool Player::GetallowThrow()
{
	return allowThrow;
}
void Player::SetallowThrow(bool flag)
{
	allowThrow = flag;
}

void Player::OnNoCollisionWithBottom()
{
	if (mCurrentState != PlayerState::Jumping && mCurrentState != PlayerState::RunJump
		&& mCurrentState != PlayerState::Falling && mCurrentState != PlayerState::JumpThrow && mCurrentState != PlayerState::JumpFight && mCurrentState != PlayerState::JumpClimb
		&& mCurrentState != PlayerState::FallClimb&& mCurrentState != PlayerState::AttackClimb && mCurrentState != PlayerState::StandHori)
	{
		this->SetState(new PlayerFallingState(this->mPlayerData));
	}
}



void Player::OnCollision(Entity *impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	
	if ((impactor->Tag == Bowl || /*impactor->Tag == Entity::Fired 
	||*/ impactor->Tag == KnifeEnemy3) && this->getState() != PlayerState::Fired  && this->getState() != PlayerState::Climbing && this->getState() != PlayerState::ClimbingHori)
		this->SetState(new PlayerAttackedState(this->mPlayerData));

	if ((impactor->Tag == Bowl || impactor->Tag == KnifeEnemy3) && (this->getState() == PlayerState::Climbing || this->getState() == PlayerState::ClimbingHori))
	{
		isAttacked = true;
		HPCount--;
	}

	if ((int)GetPosition().x > 2229 && (int)GetPosition().x < 2278 && ((int)LastPosition.x < 2229 || (int)LastPosition.x > 2278) && GetPosition().y>400)
	{
		if (CheckStair1)
			CheckStair1 = false;
		else CheckStair1 = true;
	}


	if ((int)GetPosition().x >= 2607 && (int)GetPosition().x <= 2658 && ((int)LastPosition.x < 2607 || (int)LastPosition.x > 2658) )
	{
		if (CheckStair2)
			CheckStair2 = false;
		else CheckStair2 = true;
	}
	
	if (CheckStair1 && (int) GetPosition().y >=600) CheckStair1 = false;
	if ((impactor->Tag == stair2 && CheckStair2 == false) ||(impactor->Tag == stair1 && CheckStair1 == false)) return;
	this->mPlayerData->state->OnCollision(impactor, side, data);
}

bool Player::isPlayerAttacking()
{
	if ((this->mCurrentState == PlayerState::Attack && mCurrentAnimation->GetCurrentFrame() >= 3) ||
		(this->mCurrentState == PlayerState::UpAttack&&mCurrentAnimation->GetCurrentFrame() >= 2) ||
		(this->mCurrentState == PlayerState::SitFight&&mCurrentAnimation->GetCurrentFrame() >= 3) ||
		(this->mCurrentState == PlayerState::JumpFight&&mCurrentAnimation->GetCurrentFrame() >= 4) ||
		(this->mCurrentState == PlayerState::AttackClimb&&mCurrentAnimation->GetCurrentFrame() >= 2))
			return true;
		return false;
}



void Player::SetReverse(bool flag)
{
	mCurrentReverse = flag;
}
bool Player::GetReverse()
{
	return mCurrentReverse;
}