#pragma once

#include "../GameComponents/GameGlobal.h"
#include "../MapReader/tinyxml2.h"
#include "../GameComponents/Sound.h"

class ResourceManager
{
private:
	static ResourceManager *_instance;
	//////XML resource
	tinyxml2::XMLDocument *_animationXMLAladdin,
		*_animationXMLGuard,
		*_animationXMLCivilian,
		*_animationXMLEnemy5,
		*_animationXMLExplosion,
		*_animationXMLAppleWeapon,
		*_animationXMLEnemy3Weapon,
		*_animationXMLPlayerHealthMeter,
		*_animationXMLPlayerUp,
		*_animationXMLCamel,
		*_animationXMLHandPot,
		*_animationXMLItems,
		*_animationXMLPeddler,
		//boss
		*_animationXMLJafar,
		*_animationXMLSnake,
		*_animationXMLExplosions,
		*_animationXMLJafarWeapon1,
		*_animationXMLJafarWeapon2,
		//IntroScene
		*_animationXMLIntro;

	//////Texture 
	char* _textureAladdin,
		*_textureGuard,
		*_textureCivilian,
		*_textureItems,
		*_texturePeddler,
		*_textureFlagPole,
		*_textureCamel,
		*_textureHandPot;

	//intro
	char*_textureIntro,
		*_textureIntroScene,
		*_textureIntro2,
		*_TextureMenu,
		*_TextureKnife,
		*_textureBug,
		*_textureExplain,
		*_textureStory;


	//map 1
	char* _textureAgrabahMarket;

	//man boss:
	char* _textureBossJafar;
	char* _textureExplosions;

	//map 2 TEST
	char* _textureMapBoss;
public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager* GetInstance();

	tinyxml2::XMLDocument* GetAnimationXMLAladdin();
	tinyxml2::XMLDocument* GetAnimationXMLGuard();
	tinyxml2::XMLDocument* GetAnimationXMLCivilian();
	tinyxml2::XMLDocument* GetAnimationXMLEnemy5();
	tinyxml2::XMLDocument* GetAnimationXMLExplosions();
	tinyxml2::XMLDocument* GetAnimationXMLAppleWeapon();
	tinyxml2::XMLDocument* GetAnimationXMLEnemy3Weapon();
	tinyxml2::XMLDocument* GetAnimationXMLPlayerHealthMeter();
	tinyxml2::XMLDocument* GetAnimationXMLPlayerUp();
	tinyxml2::XMLDocument* GetAnimationXMLCamel();
	tinyxml2::XMLDocument* GetAnimationXMLHandPot();
	tinyxml2::XMLDocument* GetAnimationXMLItems();
	tinyxml2::XMLDocument* GetAnimationXMLPeddler();

	tinyxml2::XMLDocument* GetAnimationXMLJafar();
	tinyxml2::XMLDocument* GetAnimationXMLSnake();
	tinyxml2::XMLDocument* GetAnimationXMLJafarWeapon1();
	tinyxml2::XMLDocument* GetAnimationXMLJafarWeapon2();
	//intro
	tinyxml2::XMLDocument* GetAnimationXMLIntro();

	const char* GetTextureAladdin();
	const char* GetTextureGuard();
	const char* GetTextureCivilian();
	const char* GetTextureExplosions();
	const char* GetTextureItems();
	const char* GetTexturePeddler();
	const char* GetTextureFlagPole();
	const char* GetTextureCamel();
	const char* GetTextureHandPot();
	const char* GetTextureAgrabahMarket();
	const char* GetTextureBossJafar();
	const char* GetTextureMapBoss();
	//intro
	const char* GetTextureIntro();
	const char* GetTextureIntroScene();
	const char* GetTextureIntro2();
	const char* GetTextureMenu();
	const char* GetTextureKnife();
	const char* GetTextureBug();
	const char* GetTextureExplain();
	const char* GetTextureStory();

	void playSound(std::string name, bool isloop, int times);
	void stopSound(std::string name);

	//void LoadRectMap(map<state> object);
};

