#include "Sprite.h"

Sprite::Sprite(const char* filePath, Rect sourceRect, int width, int height, D3DCOLOR colorKey, D3DXVECTOR2 center, LPDIRECT3DTEXTURE9 textureType)
{

	mCenterDraw = center;
	if (textureType != NULL)
		mTexture = textureType;
	this->InitWithSprite(filePath, sourceRect, width, height, colorKey);

}

Sprite::Sprite()
{

}

Sprite::~Sprite()
{
	if (mTexture != NULL)
		mTexture->Release();
}

void Sprite::InitWithSprite(const char* filePath, Rect sourceRect, int width, int height, D3DCOLOR colorKey)
{

	HRESULT result;
	mSpriteHandler = GameGlobal::GetCurrentSpriteHandler();
	mPosition = D3DXVECTOR3(0, 0, 0);
	mRotation = 0;
	mRotationCenter = D3DXVECTOR2(mPosition.x, mPosition.y);
	mTranslation = D3DXVECTOR2(0, 0);
	mScale = D3DXVECTOR2(0, 1);
	mSourceRect = sourceRect;
	mScale.x = mScale.y = 1;

	D3DXGetImageInfoFromFileA(filePath, &mImageInfo);

	if (width == NULL)
	{
		if (!isRect(sourceRect))
			mWidth = mImageInfo.Width;
		else
			mWidth = sourceRect.right - sourceRect.left;
	}
	else
		mWidth = width;

	if (height == NULL)
	{
		if (!isRect(sourceRect))
			mHeight = mImageInfo.Height;
		else
			mHeight = sourceRect.bottom - sourceRect.top;
	}
	else
		mHeight = height;

	if (!isRect(sourceRect))
	{
		mSourceRect.left = 0;
		mSourceRect.right = mWidth;
		mSourceRect.top = 0;
		mSourceRect.bottom = mHeight;
	}

	if (mTexture == NULL)
	{
		LPDIRECT3DDEVICE9 device;
		mSpriteHandler->GetDevice(&device);

		if (mColorTrans != D3DCOLOR_XRGB(0, 0, 0))
			colorKey = mColorTrans;

		D3DXCreateTextureFromFileExA(
			device,
			filePath,
			mImageInfo.Width,
			mImageInfo.Height,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			colorKey,
			&mImageInfo,
			NULL,
			&mTexture);

	}


}

bool Sprite::isRect(Rect rect)
{
	if (rect.left == rect.right)
		return false;

	if (rect.top == rect.bottom)
		return false;

	return true;
}

int Sprite::GetWidth()
{
	return mWidth;
}

int Sprite::GetHeight()
{
	return mHeight;
}

void Sprite::Draw(D3DXVECTOR3 position, Rect sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	D3DXVECTOR3 center_new, center;
	D3DXVECTOR3 inPosition = mPosition;
	Rect inSourceRect = mSourceRect;
	float inRotation = mRotation;
	D3DXVECTOR2 inCcale = mScale;
	D3DXVECTOR2 inTranslation = mTranslation;
	D3DXVECTOR2 inRotationCenter = D3DXVECTOR2(inPosition.x, inPosition.y);
	D3DXVECTOR2 scalingScenter = D3DXVECTOR2(inPosition.x, inPosition.y);

	if (position != D3DXVECTOR3())
		inPosition = position;

	if (isRect(sourceRect))
		inSourceRect = sourceRect;

	if (scale != D3DXVECTOR2())
		inCcale = scale;

	if (transform != D3DXVECTOR2())
		inTranslation = transform;

	if (rotationCenter != D3DXVECTOR2())
		inRotationCenter = rotationCenter;
	else
		mRotationCenter = D3DXVECTOR2(inPosition.x, inPosition.y);// cho phep quay giua hinh

	if (inSourceRect.mCenter.x < 150 && inSourceRect.mCenter.x > 0) {
		center_new = inSourceRect.mCenter;
	}
	else center_new = D3DXVECTOR3(0, 0, 0);

	D3DXVECTOR3 center1 = D3DXVECTOR3(mWidth*mCenterDraw.x, mHeight*mCenterDraw.y, 0);
	if (center_new == D3DXVECTOR3(0, 0, 0))
		center = center1;
	else
		center = center_new;
	D3DXMatrixTransformation2D(&mMatrix, &scalingScenter, 0, &inCcale, &D3DXVECTOR2(inPosition.x, inPosition.y - mHeight / 2),
		angle, &inTranslation);

	D3DXMATRIX oldMatrix;

	mSpriteHandler->GetTransform(&oldMatrix);
	mSpriteHandler->SetTransform(&mMatrix);



	mSpriteHandler->Draw(mTexture,
		&inSourceRect,
		&center,
		&inPosition,
		D3DCOLOR_ARGB(255, 255, 255, 255)); // nhung pixel nao co mau trang se duoc to mau nay len

	mSpriteHandler->SetTransform(&oldMatrix); // set lai matrix cu~ de Sprite chi ap dung transfrom voi class nay
}

void Sprite::SetSourceRect(Rect rect)
{
	mSourceRect = rect;
}

LPDIRECT3DTEXTURE9 Sprite::GetTexture()
{
	return mTexture;
}

void Sprite::SetPosition(D3DXVECTOR3 pos)
{
	mPosition = pos;
}

void Sprite::SetPosition(float x, float y)
{
	mPosition = D3DXVECTOR3(x, y, 0);
}

void Sprite::SetPosition(D3DXVECTOR2 pos)
{
	this->SetPosition(pos.x, pos.y);
}

D3DXVECTOR3 Sprite::GetPosition()
{
	return mPosition;
}

D3DXVECTOR2 Sprite::GetScale()
{
	return mScale;
}

void Sprite::SetScale(D3DXVECTOR2 scale)
{
	mScale = scale;
}

D3DXVECTOR2 Sprite::GetTranslation()
{
	return mTranslation;
}

void Sprite::SetTranslation(D3DXVECTOR2 translation)
{
	mTranslation = translation;
}

D3DXVECTOR2 Sprite::GetRotationCenter()
{
	return mRotationCenter;
}

void Sprite::SetRotationCenter(D3DXVECTOR2 rotationCenter)
{
	mRotationCenter = rotationCenter;
}

float Sprite::GetRotation()
{
	return mRotation;
}

void Sprite::SetRotation(float rotation)
{
	mRotation = rotation;
}

D3DXIMAGE_INFO Sprite::GetImageInfo()
{
	return mImageInfo;
}

void Sprite::FlipHorizontal(bool flag)
{
	if (mIsFlipHorizontal != flag)
	{
		mIsFlipHorizontal = flag;
		mScale = D3DXVECTOR2(mScale.x, -mScale.y);
	}

}

void Sprite::FlipVertical(bool flag)
{
	if (mIsFlipVertical != flag)
	{
		mIsFlipVertical = flag;
		mScale = D3DXVECTOR2(-mScale.x, mScale.y);
	}
}

bool Sprite::IsFlipHorizontal()
{
	return mIsFlipHorizontal;
}

bool Sprite::IsFlipVertical()
{
	return mIsFlipVertical;
}

void Sprite::SetWidth(int width)
{
	mWidth = width;
}

void Sprite::SetHeight(int height)
{
	mHeight = height;
}

void Sprite::SetTransColor(D3DCOLOR color)
{
	mColorTrans = color;
}


Rect Sprite::GetSourceRect()
{
	return mSourceRect;
}

D3DXVECTOR2 Sprite::GetCenterDraw()
{
	return mCenterDraw;
}
void Sprite::SetCenterDraw(D3DXVECTOR2 center)
{
	mCenterDraw = center;
}
LPD3DXSPRITE Sprite::GetSpriteHandle()
{
	return mSpriteHandler;
}