#include "../Entity.h"
#include "../../GameComponents/Animation.h"
class SimpleObject :public Entity
{
public:

	SimpleObject();
	virtual ~SimpleObject();
	Animation *mCurrentAnimation;

	Sprite *represent;
	void Update();
	void Draw(D3DXVECTOR3 position, Rect sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform);
	void OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side);
	void SetPos(float x, float y);
	bool Actived = false;
protected:
	virtual vector<Rect> LoadRect();
	const char* filePath;
	int totalFrame;
	vector<Rect> source;
	float timePerFrame = 0.1f;
	D3DXVECTOR2 center= D3DXVECTOR2(0.5, 0.5);
	D3DCOLOR colorKey = NULL;



};