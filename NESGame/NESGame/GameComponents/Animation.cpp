#include "Animation.h"

Animation::Animation()
{

}

Animation::Animation(const char* filePath, int totalFrame, vector<Rect> source, float timePerFrame, D3DXVECTOR2 center, D3DCOLOR colorKey, Entity::EntityTypes type)
{
	if (type != Entity::EntityTypes::None)
		mType = type;
	InitWithAnimation(filePath, totalFrame, source, timePerFrame, center, colorKey);

}

void Animation::InitWithAnimation(const char* filePath, int totalFrame, vector<Rect> source, float timePerFrame, D3DXVECTOR2 center, D3DCOLOR colorKey)
{


	if (mType == Entity::EntityTypes::PlayerOne)
		mSprite = new Sprite(filePath, Rect(), 0, 0, colorKey, center, GameGlobal::mAladdintexture);
	else if (mType == Entity::Enemy)
		mSprite = new Sprite(filePath, Rect(), 0, 0, colorKey, center, GameGlobal::mEnemytexture);
	else if (mType == Entity::flare)
		mSprite = new Sprite(filePath, Rect(), 0, 0, colorKey, center, GameGlobal::mFlaretexture);
	else if (mType == Entity::civilian)
		mSprite = new Sprite(filePath, Rect(), 0, 0, colorKey, center, GameGlobal::mCiviliantexture);
	else if (mType == Entity::Camel)
		mSprite = new Sprite(filePath, Rect(), 0, 0, colorKey, center, GameGlobal::mCameltexture);
	else if (mType == Entity::flagPole)
		mSprite = new Sprite(filePath, Rect(), 0, 0, colorKey, center, GameGlobal::mFlagPoletexture);
	else if (mType == Entity::CheckPoint)
		mSprite = new Sprite(filePath, Rect(), 0, 0, colorKey, center, GameGlobal::mItemtexture);
	else if (mType == Entity::jafar)
		mSprite = new Sprite(filePath, Rect(), 0, 0, colorKey, center, GameGlobal::mJafartexture);
	else if (mType == Entity::Peddler)
		mSprite = new Sprite(filePath, Rect(), 0, 0, colorKey, center, GameGlobal::mPeddlertexture);
	else
		mSprite = new Sprite(filePath, Rect(), 0, 0, colorKey, center);
	mTimePerFrame = timePerFrame;
	mTotalFrame = totalFrame;
	mSourRect = source;

	Rect rect = mSourRect.at(0);
	mSprite->SetSourceRect(rect);
	mSprite->SetWidth(rect.right - rect.left);
	mSprite->SetHeight(rect.bottom - rect.top);
}

Animation::~Animation()
{

}

void Animation::SetFlipVertical(bool flag)
{
	mSprite->FlipVertical(flag);
}

void Animation::SetFlipHorizontal(bool flag)
{
	mSprite->FlipHorizontal(flag);
}

D3DXVECTOR2 Animation::GetScale()
{
	return mSprite->GetScale();
}

void Animation::SetScale(D3DXVECTOR2 scale)
{
	mSprite->SetScale(scale);
}

float Animation::GetRotation()
{
	return mSprite->GetRotation();
}

void Animation::SetRotation(float rotation) // by radian
{
	mSprite->SetRotation(rotation);
}

D3DXVECTOR2 Animation::GetRotationCenter()
{
	return mSprite->GetRotationCenter();
}
void Animation::Reset()
{
	mCurrentIndex = 0;
}
void Animation::SetRotationCenter(D3DXVECTOR2 rotationCenter)
{
	mSprite->SetRotationCenter(rotationCenter);
}

D3DXVECTOR2 Animation::GetTranslation()
{
	return mSprite->GetTranslation();
}

void Animation::SetTranslation(D3DXVECTOR2 translation)
{
	mSprite->SetTranslation(translation);
}
Sprite* Animation::GetSprite()
{
	return mSprite;
}
void Animation::Update(float dt)
{
	if (mTotalFrame <= 1)
		return;
	if (mCurrentIndex <= mTotalFrame)
	{
		Rect rect = mSourRect.at(mCurrentIndex);

		mSprite->SetSourceRect(rect);
		mSprite->SetWidth(rect.right - rect.left);
		mSprite->SetHeight(rect.bottom - rect.top);
	}
	if (mCurrentTotalTime >= mTimePerFrame)
	{
		mCurrentTotalTime = 0;
		mCurrentIndex++;


		if (mCurrentIndex >= mTotalFrame)
			mCurrentIndex = 0;

	}
	else
	{
		mCurrentTotalTime += dt;
	}
}

void Animation::Draw(D3DXVECTOR3 position, Rect sourceRect, D3DXVECTOR2 scale,
	D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	if (mReverse)
	{
		Rect rect = mSourRect.at(mTotalFrame - mCurrentIndex - 1);
		mSprite->SetSourceRect(rect);
		mSprite->SetWidth(rect.right - rect.left);
		mSprite->SetHeight(rect.bottom - rect.top);
	}
	mSprite->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Animation::SetPosition(D3DXVECTOR3 pos)
{
	mSprite->SetPosition(pos);
}

void Animation::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR3(x, y, 0));
}

void Animation::SetPosition(D3DXVECTOR2 pos)
{
	SetPosition(D3DXVECTOR3(pos));
}
int Animation::GetCurrentFrame()
{
	return mCurrentIndex;
}
void Animation::SetCurrentFrame(int frame)
{
	mCurrentIndex = frame;
}
void Animation::SetReverse(bool re)
{
	mReverse = re;
}

int Animation::GetTotalFrame()
{
	return mTotalFrame;
}