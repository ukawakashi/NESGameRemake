#include "Weapon.h"


vector<Rect>Weapon::LoadRECT(WeaponState::StateName state)
{
	vector<Rect> listSourceRect;
	Rect rect;
	if (Tag == EntityTypes::Bowl)
		switch (state)
		{
		case WeaponState::Flying:

			listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLCivilian(), "Bowl");
			break;
		case WeaponState::Breaking:
			listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLCivilian(), "BowlLeftBreak");
			break;
		case WeaponState::NONE:
			break;
		default:
			break;
		}
		else
			if (Tag == EntityTypes::AppleThrow)
			{
				switch (state)
				{
				case WeaponState::Flying:
					listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "AppleFlying");


					break;
				case WeaponState::Breaking:
					listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "AppleSplat");

					break;
				case WeaponState::NONE:
					break;
				default:
					break;
				}
			}
			else
				if (Tag == EntityTypes::CamelSpit)
				{
					switch (state)
					{
					case WeaponState::Flying:
						listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLCamel(), "CamelSpit2");


						break;
					case WeaponState::Breaking:
						listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "AppleSplat");

						break;
					case WeaponState::NONE:
						break;
					default:
						break;
					}
				}
			else// if (Tag == EntityTypes::KnifeEnemy3)
			{
				switch (state)
				{
				case WeaponState::Flying:
					listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLGuard(), "FatmanKnife");
					break;
				case WeaponState::Breaking:
					listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLAladdin(), "KnifeBreaking");
					break;
				case WeaponState::NONE:
					break;
				default:
					break;
				}
			}

	return listSourceRect;
}
Weapon::Weapon(EntityTypes type)
{
	Tag = type;
	if (Tag == EntityTypes::Bowl)
	{
		FlyingAnim = new Animation(ResourceManager::GetInstance()->GetTextureCivilian(), 6, LoadRECT(WeaponState::Flying), (float)1 / 0.2, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(120, 193, 152), Entity::civilian);
		BreakingAnim = new Animation(ResourceManager::GetInstance()->GetTextureCivilian(), 8, LoadRECT(WeaponState::Breaking), (float)1 / 10, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(120, 193, 152), Entity::civilian);

	}
	else if (Tag == EntityTypes::AppleThrow)
	{
		FlyingAnim = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 8, LoadRECT(WeaponState::Flying), (float)1 / 20, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255), Entity::PlayerOne);
		BreakingAnim = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 5, LoadRECT(WeaponState::Breaking), (float)1 / 20, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255), Entity::PlayerOne);

	}
	else if (Tag == EntityTypes::CamelSpit)
	{
		FlyingAnim = new Animation(ResourceManager::GetInstance()->GetTextureCamel(), 1, LoadRECT(WeaponState::Flying), (float)1 / 20, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(248, 0, 248) , Entity::CamelSpit);
		FlyingAnim->SetScale(D3DXVECTOR2(1.0f, 1.0f));
		BreakingAnim = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 5, LoadRECT(WeaponState::Breaking), (float)1 / 20, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255), Entity::PlayerOne);

	}
	else
		{
			FlyingAnim = new Animation(ResourceManager::GetInstance()->GetTextureGuard(), 7, LoadRECT(WeaponState::Flying), (float)1 / 20, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(120, 193, 152), Entity::Enemy);

			BreakingAnim = new Animation(ResourceManager::GetInstance()->GetTextureAladdin(), 10, LoadRECT(WeaponState::Breaking), (float)1 / 0.4, D3DXVECTOR2(0.5, 0.5), D3DCOLOR_XRGB(255, 0, 255), Entity::PlayerOne);
			BreakingAnim->SetScale(D3DXVECTOR2(2, 2));
		}


	SetState(WeaponState::NONE/*, type*/);

	mReverse = false;


}

Weapon::~Weapon()
{
}


void Weapon::changeAnim(WeaponState::StateName state)
{
	switch (state)
	{
	case WeaponState::Flying:
		mCurrentAnim = FlyingAnim;
		BreakingAnim->Reset();
		break;

	case WeaponState::Breaking:

		mCurrentAnim = BreakingAnim;
		FlyingAnim->Reset();
		break;

	default:
		return;
		break;
	}
	this->width = mCurrentAnim->GetSprite()->GetWidth();
	this->height = mCurrentAnim->GetSprite()->GetHeight();
}

void Weapon::Update(float dt)
{


	if (mCurrentAnim != nullptr)
	{
		mCurrentAnim->Update(1);
		width = mCurrentAnim->GetSprite()->GetWidth();
		height = mCurrentAnim->GetSprite()->GetHeight();
		if (mCurrentAnim == BreakingAnim)
		{
			if (mCurrentAnim->GetCurrentFrame() == mCurrentAnim->GetTotalFrame() - 1)
			{
				this->SetState(WeaponState::NONE);

			}
		}
	}

	if (curState != nullptr)
	{
		curState->Update(1);
		posX = curState->getPos().x;
		posY = curState->getPos().y;
	}

}
void Weapon::Draw(D3DXVECTOR3 position, Rect sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{

	//mCurrentAnimation->GetSprite()->FlipVertical(mCurrentReverse);


	if (mCurrentAnim != nullptr)
	{
		mCurrentAnim->SetPosition(this->GetPosition());
		mCurrentAnim->Draw(position, sourceRect, D3DXVECTOR2(), transform, angle, rotationCenter, colorKey);

	}
}

Rect Weapon::GetBound()
{

	Rect rect;
	rect.left = this->posX - (width*0.3) / 2;
	rect.right = rect.left + width*0.3;
	rect.top = this->posY - height*0.3;
	rect.bottom = this->posY;

	return rect;
}

void Weapon::SetState(WeaponState::StateName newState)
{
	switch (newState)
	{
	case WeaponState::Flying:
		curState = new WeaponFlyState(D3DXVECTOR3(posX, posY, 0), mReverse, Tag);
		break;
	case WeaponState::Breaking:
		curState = new WeaponBreakState(D3DXVECTOR3(posX, posY, 0));
		break;
	case WeaponState::NONE:
		curState = nullptr;
		mCurrentAnim = nullptr;
		return;
		break;
	}

	this->changeAnim(newState);
}

void Weapon::OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side)
{
	if (impactor->Tag == Entity::AppleObject) return;
	SetState(WeaponState::Breaking);
	if (Tag == EntityTypes::AppleThrow)
		ResourceManager::GetInstance()->playSound("appleSplat", false, 1);
	else if (Tag == EntityTypes::Bowl)
	{
		Sound::getInstance()->play("BowlBreak", false, 1);
	}
	else if (Tag == EntityTypes::KnifeEnemy3)
		Sound::getInstance()->play("SwordChing", false, 1);
}
WeaponState::StateName Weapon::GetCurrentState()
{
	if (curState == nullptr) return WeaponState::NONE;
	else return curState->GetNameState();
}