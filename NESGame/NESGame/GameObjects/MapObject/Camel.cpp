#include "Camel.h"

vector<Rect> Camel::LoadRect()
{
	vector<Rect> listSourceRect;
	listSourceRect = ReadResource::Instance()->LoadXML(ResourceManager::GetInstance()->GetAnimationXMLCamel(), "Camel");
	return listSourceRect;
}

Camel::Camel(const char* FilePath,
	float TimePerFrame ,
	D3DXVECTOR2 Center)
{


	this->filePath = FilePath;
	this->source = this->LoadRect();
	this->totalFrame = this->source.size();
	
	this->timePerFrame = TimePerFrame;
	this->center = Center;
	this->colorKey = D3DCOLOR_XRGB(248, 0, 248);
	represent = new Sprite(filePath, Rect(), 0, 0, D3DCOLOR_XRGB(248, 0, 248), center,GameGlobal::mCameltexture);

	Rect rect = source.at(0);

	represent->SetSourceRect(rect);
	represent->SetWidth(rect.right - rect.left);
	represent->SetHeight(rect.bottom - rect.top);

	mCurrentAnimation = new Animation(filePath, totalFrame, source, timePerFrame, center, D3DCOLOR_XRGB(248, 0, 248),Entity::Camel);

}

Rect Camel::GetBound()
{
	Rect re;
	re.left = posX - represent->GetWidth() / 2;
	re.right = re.left + represent->GetWidth();
	re.top=posY- represent->GetHeight() / 2;
	re.bottom=re.top+ represent->GetHeight();
	return re;
}
Camel::~Camel()
{
}
void Camel::Update()
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
void Camel::OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side)
{
	if (impactor->GetPosition().y < 640 )
	{
		if (impactor->Tag == Entity::PlayerOne)
			Actived = true;
	}
	else
		Actived = false;

}