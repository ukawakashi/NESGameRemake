#ifndef __SCENE__
#define __SCENE__
#include <d3dx9.h>
#include <d3d9.h>

#include "GameGlobal.h"
#include "../GameControllers/ResourceManager.h"
//#include "../GameObjects/Entity.h"
class Scene
{
public:
	virtual void Update(float dt);
	virtual void LoadContent();
	virtual void Draw();

	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
	virtual void OnMouseDown(float x, float y);
	virtual void playMusic();

	D3DCOLOR GetBackcolor();

	~Scene();

	void turnSound(bool state);
	bool isSoundOn();

	void turnMusic(bool state);
	bool isMusicOn();


protected:
	Scene();
	bool musicOn, soundOn;

	char* musicName;

	D3DCOLOR                mBackColor;



private:
};

#endif

