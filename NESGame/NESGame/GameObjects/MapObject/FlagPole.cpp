#include "FlagPole.h"





FlagPole::~FlagPole()
{
}





vector<Rect> FlagPole::LoadRect()
{
	vector<Rect> listSourceRect;
	listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLItems(), "FlagPole");
	return listSourceRect;
}


Rect FlagPole::GetBound()
{
	Rect rect;
	rect.left = this->GetPosition().x;
	rect.right =rect.left+represent->GetWidth();
	rect.top = this->GetPosition().y - represent->GetHeight() / 2;
	rect.bottom = rect.top + represent->GetHeight();
	return rect;
}

FlagPole::FlagPole()
{
	this->filePath = ResourceManager::GetInstance()->GetTextureFlagPole();
	this->source = this->LoadRect();
	this->totalFrame = this->source.size();

	this->timePerFrame = (float)1 / 20;
	this->center = D3DXVECTOR2(0, 0.5);
	this->colorKey = D3DCOLOR_XRGB(255, 0, 255);
	represent = new Sprite(filePath, Rect(), 0, 0, colorKey, center,GameGlobal::mFlagPoletexture);

	Rect rect = source.at(0);

	represent->SetSourceRect(rect);
	represent->SetWidth(rect.right - rect.left);
	represent->SetHeight(rect.bottom - rect.top);
	Tag = Entity::flagPole;
	mCurrentAnimation = new Animation(filePath, totalFrame, source, timePerFrame, center, colorKey,Entity::flagPole);
}

void FlagPole::Update()
{
	if (Actived)
	{
		if (mCurrentAnimation->GetCurrentFrame() == totalFrame - 1)
		{
			Actived = false;
			mCurrentAnimation->Reset();
		}
		else SimpleObject::Update();
	}
}
void FlagPole::OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side)
{
	Actived = true;

}