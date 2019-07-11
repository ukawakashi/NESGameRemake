#include "Scene.h"


Scene::Scene()
{
	mBackColor = 0x4866ff;

	LoadContent();
}

Scene::~Scene()
{

}

void Scene::Update(float dt)
{

}

void Scene::LoadContent()
{
	if (musicOn)
		playMusic();
}

void Scene::Draw()
{

}

void Scene::OnKeyDown(int keyCode)
{

}

void Scene::OnKeyUp(int keyCode)
{

}

void Scene::OnMouseDown(float x, float y)
{

}

D3DCOLOR Scene::GetBackcolor()
{
	return mBackColor;
}

void Scene::turnSound(bool state)
{
	soundOn = state;
}
bool Scene::isSoundOn()
{
	return soundOn;
}

void Scene::turnMusic(bool state)
{
	musicOn = state;
}
bool Scene::isMusicOn()
{
	return musicOn;
}

void Scene::playMusic()
{

}