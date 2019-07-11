#ifndef __ANIMATION__
#define __ANIMATION__



#include "Sprite.h"
#include "../GameObjects/Entity.h"
using namespace std;

class Animation
{
public:
	//ham ho tro lay animation voi anh co duy nhat 1 hang
	Animation(const char* filePath, int totalFrame, vector<Rect> source, float timePerFrame = 0.1f, D3DXVECTOR2 center = D3DXVECTOR2(0.5, 0.5), D3DCOLOR colorKey = D3DCOLOR_XRGB(255, 0, 255), Entity::EntityTypes type = Entity::None);

	Animation();

	virtual void Update(float dt);

	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), Rect sourceRect = Rect(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

	virtual void SetPosition(D3DXVECTOR3 pos);
	virtual void SetPosition(float x, float y);
	virtual void SetPosition(D3DXVECTOR2 pos);

	D3DXVECTOR2 GetScale();
	void SetScale(D3DXVECTOR2 scale);

	float GetRotation();
	void SetRotation(float rotation); // by radian

	D3DXVECTOR2 GetRotationCenter();
	void SetRotationCenter(D3DXVECTOR2 rotationCenter);

	void SetFlipVertical(bool flag);
	void SetFlipHorizontal(bool flag);

	D3DXVECTOR2 GetTranslation(); // phep tinh tien tu world position -> view position
	void SetTranslation(D3DXVECTOR2 translation); // phep tinh tien: tu the world position -> view position

	~Animation();
	Sprite* GetSprite();
	void Reset();

	int GetCurrentFrame();
	void SetCurrentFrame(int frame);
	void SetReverse(bool re);
	vector<Rect>	mSourRect;
	int GetTotalFrame();
protected:
	//su dung cho ke thua
	void InitWithAnimation(const char* filePath, int totalFrame, vector<Rect> source, float timePerFrame = 0.1f, D3DXVECTOR2 center = D3DXVECTOR2(0.5, 0.5), D3DCOLOR colorKey = NULL);

	int
		mCurrentIndex, //gia tri frame hien tai - bat dau tu 0 -> tong so frame - 1
		mTotalFrame;  //tong so frame

	bool mReverse = false; //Co ve nguoc hay khong,Vẽ tua ngược lại 

	float       mTimePerFrame, //thoi gian luan chuyen 1 frame
		mCurrentTotalTime; //tong thoi gian hien tai de thuc hien timeperframe


	Entity::EntityTypes mType;
	Sprite*			mSprite;
};

#endif
