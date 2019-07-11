#include "DropBrick.h"



DropBrick::DropBrick(D3DXVECTOR2 startPOS)
{
	SetPosition(startPOS);
	mStartPOS = startPOS;
	Rect rect = { 171,1050,1083,188};
	Brick = new Sprite("Resources/Aladdin.png", rect, 33, 17, D3DCOLOR_XRGB(255, 0, 255),D3DXVECTOR2(0.5,1.0),GameGlobal::mAladdintexture);
	Brick->SetPosition(startPOS+ D3DXVECTOR2(0,10));
	Tag = Entity::BrickDrop;
}


DropBrick::~DropBrick()
{
}
void DropBrick::Draw(D3DXVECTOR2 tran, D3DXVECTOR2 Scale)
{
	//Brick->Draw(D3DXVECTOR3(/*temp.x,temp.y,0*/),Rect(),Scale,tran);
	Brick->Draw(D3DXVECTOR3(Brick->GetPosition().x, Brick->GetPosition().y+12,0), Rect(), Scale, tran);
}

void DropBrick::Update()
{
	if (FlagActive)
	{
		mDelay++;
		if (mDelay < 20) return;
		Entity::AddPosition(0,5);
		Brick->SetPosition(GetPosition());
		if (GetPosition().y - mStartPOS.y >= 200)
		{
			FlagActive = false;
			//check = false;
			SetPosition(mStartPOS);
		}
		
	}
	else
	{
		SetPosition(mStartPOS);
		Brick->SetPosition(GetPosition());
		mDelay = 0;
	}
	
}
void DropBrick::OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side)
{
	/*if (!check)
	{
		if ((impactor->Tag == Entity::PlayerOne) && (side == Entity::NotKnow || side == Entity::BottomLeft || side == Entity::BottomRight)) {
			impactor->SetPosition(impactor->GetPosition().x, impactor->GetPosition().y - 10);
			check = true;
		}
	}*/
	if(impactor->GetPosition().y<440 && impactor->GetPosition().x <2000 || impactor->GetPosition().y<448 && impactor->GetPosition().x >4200 
		|| /*impactor->GetPosition().y <472 &&*/ impactor->GetPosition().x <4200 && impactor->GetPosition().x >4000)
		FlagActive = true;
}
