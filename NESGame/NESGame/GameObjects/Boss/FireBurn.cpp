#include "FireBurn.h"


vector<Rect> FireBurn::LoadRECT()
{
	vector<Rect> listSourceRect;
	Rect rect;
	rect.left = 8; rect.top = 286; rect.right = rect.left + 74; rect.bottom = rect.top + 49; listSourceRect.push_back(rect);
	rect.left = 96; rect.top = 288; rect.right = rect.left + 79; rect.bottom = rect.top + 47; listSourceRect.push_back(rect);
	rect.left = 184; rect.top = 294; rect.right = rect.left + 98; rect.bottom = rect.top + 41; listSourceRect.push_back(rect);
	rect.left = 296; rect.top = 295; rect.right = rect.left + 89; rect.bottom = rect.top + 40; listSourceRect.push_back(rect);
	rect.left = 400; rect.top = 307; rect.right = rect.left + 77; rect.bottom = rect.top + 28; listSourceRect.push_back(rect);
	rect.left = 488; rect.top = 305; rect.right = rect.left + 73; rect.bottom = rect.top + 30; listSourceRect.push_back(rect);
	rect.left = 572; rect.top = 293; rect.right = rect.left + 60; rect.bottom = rect.top + 42; listSourceRect.push_back(rect);
	rect.left = 645; rect.top = 285; rect.right = rect.left + 64; rect.bottom = rect.top + 50; listSourceRect.push_back(rect);
	return listSourceRect;
}
FireBurn::FireBurn(D3DXVECTOR2 startPos)
{
	mAnimationFireBurn= new Animation("Resources/jafar.png", 8, LoadRECT(), (float)1 / 0.5, D3DXVECTOR2(0.5, 1), D3DCOLOR_XRGB(186, 254, 202));
	this->startPos = startPos;
	SetPosition(startPos.x,startPos.y+10);
	isActive = false;
}
void FireBurn :: Update()
{
	
	if (isActive)
	{

		mAnimationFireBurn->Update(1);
		if (isLeftorRight)
			AddPosition(2, 0);
		else 	AddPosition(-2, 0);
	}
}
void FireBurn::Draw(D3DXVECTOR2 trans)
{
	if (isActive)
	{
		mAnimationFireBurn->SetPosition(GetPosition());
		if(isLeftorRight)
			mAnimationFireBurn->SetFlipVertical(false);
		else
			mAnimationFireBurn->SetFlipVertical(true);
		mAnimationFireBurn->Draw(D3DXVECTOR3(), Rect(), D3DXVECTOR2(), trans);
	}
}
void FireBurn::OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side)
{
	if (impactor->Tag == Entity::Land)
	{
		SetPosition(startPos);
		mAnimationFireBurn->Reset();
		isActive = false;
		isLeftorRight = false;
	}
	return;
}
FireBurn::~FireBurn()
{
}
