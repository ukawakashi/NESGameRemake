#include "SimpleObject.h"

SimpleObject::SimpleObject()
{

}
SimpleObject::~SimpleObject()
{

}
void SimpleObject::Update()
{

	if (Actived)
	{
		mCurrentAnimation->Update(60);
	}
	
}
void SimpleObject::Draw(D3DXVECTOR3 position, Rect sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform)
{
	
	if (Actived)
	{
		mCurrentAnimation->Draw(GetPosition(),sourceRect, scale,transform);	
	}
	else
	{
		if (represent != nullptr) {
			represent->Draw(GetPosition(), sourceRect, scale, transform);
		}
	}
}
void SimpleObject::SetPos(float x, float y)
{
	SetPosition(x, y);
	represent->SetPosition(x, y);

	if(mCurrentAnimation!=nullptr)
	mCurrentAnimation->SetPosition(this->GetPosition());
}
void SimpleObject::OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side)
{

	
}

vector<Rect> SimpleObject::LoadRect()
{
	return vector<Rect>();
}