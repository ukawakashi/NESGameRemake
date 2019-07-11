#include "Rect.h"



Rect::Rect()
{
	Rect(0, 0, 0, 0);
}

Rect::Rect(float top, float left, float right, float bottom, D3DXVECTOR3 center)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;

	if (center.x <= 0)
		center.x = (right - left) / 2;
	if (center.y <= 0)
		center.y = (bottom - top);

	this->mCenter = center;
}

Rect::~Rect()
{
}

void Rect::Set(float top, float left, float right, float bottom, D3DXVECTOR3 center)
{
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	if (center != D3DXVECTOR3(0, 0, 0))
		this->mCenter = center;
}

void Rect::SetCenter(float x, float y, float z)
{
	x = (x == 0) ? (this->right - this->left) / 2 : x;
	y = (y == 0) ? this->bottom - this->top : y;
	this->mCenter = D3DXVECTOR3(x, y, z);
}

bool Rect::IsCollision(Rect rect)
{
	bool flag = ((rect.left >= left)
		&& (rect.right <= right)
		&& (rect.top >= top)
		&& (rect.bottom <= bottom));

	float dh = (abs(top - rect.bottom) > abs((bottom - rect.top))) ? abs(top - rect.bottom) : abs((bottom - rect.top));
	float dw = (abs(left - rect.right) > abs(right - rect.left)) ? abs(left - rect.right) : abs(right - rect.left);

	return ((dw <= ((right - left) + (rect.right - rect.left)))
		&& (dh <= ((bottom - top) + (rect.bottom - rect.top)))
		|| flag);
}