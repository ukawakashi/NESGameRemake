#include "ResourceManager.h"

ResourceManager* ResourceManager::_instance = NULL;

ResourceManager::ResourceManager()
{
	//Duong dan den file xml chua cac rectangle
	_animationXMLAladdin = new tinyxml2::XMLDocument();
	_animationXMLAladdin->LoadFile("Resources/Aladdin/Aladdin-Animations.xml");

	_animationXMLGuard = new tinyxml2::XMLDocument();
	_animationXMLGuard->LoadFile("Resources/Enemies/Guards.xml");

	_animationXMLCivilian = new tinyxml2::XMLDocument();
	_animationXMLCivilian->LoadFile("Resources/Enemies/Civil-Enemies.xml");

	_animationXMLEnemy5 = new tinyxml2::XMLDocument();
	_animationXMLEnemy5->LoadFile("Resources/Enemies/Enemy-5-Animations.xml");

	_animationXMLExplosions = new tinyxml2::XMLDocument();
	_animationXMLExplosions->LoadFile("Resources/Enemies/Explosions.xml");

	_animationXMLAppleWeapon = new tinyxml2::XMLDocument();
	_animationXMLAppleWeapon->LoadFile("Resources/Weapons/PlayerWeapons/AppleWeapon-Animation.xml");

	_animationXMLEnemy3Weapon = new tinyxml2::XMLDocument();
	_animationXMLEnemy3Weapon->LoadFile("Resources/Weapons/EnemiesWeapons/Enemy-3-Weapon-Animations.xml");

	_animationXMLCamel = new tinyxml2::XMLDocument();
	_animationXMLCamel->LoadFile("Resources/Items/Camel.xml");

	_animationXMLHandPot = new tinyxml2::XMLDocument();
	_animationXMLHandPot->LoadFile("Resources/Items/HandPot-Animation.xml");

	_animationXMLPlayerHealthMeter = new tinyxml2::XMLDocument();
	_animationXMLPlayerHealthMeter->LoadFile("Resources/Items/HealthMeter-Animation.xml");

	_animationXMLPlayerUp = new tinyxml2::XMLDocument();
	_animationXMLPlayerUp->LoadFile("Resources/Items/Up-Animation.xml");

	_animationXMLItems = new tinyxml2::XMLDocument();
	_animationXMLItems->LoadFile("Resources/Items/Items.xml");

	_animationXMLPeddler = new tinyxml2::XMLDocument();
	_animationXMLPeddler->LoadFile("Resources/Items/Peddler.xml");

	//Cac file anh duoc su dung
	char aladdin[] = "Resources/Aladdin/Aladdin_Sprite.png";
	char Guard[] = "Resources/Enemies/Guards.png";
	char Civilian[] = "Resources/Enemies/Civilian.png";
	char Explosions[] = "Resources/Enemies/Explosions.png";
	char Items[] = "Resources/Items/Items.png";
	char Peddler[] = "Resources/Items/Peddler.png";
	char FlagPole[] = "Resources/Items/FlagPole.png";
	char Camel[] = "Resources/Items/Camel.png";
	char HandPot[] = "Resources/Enemies/Civilian.png";
	char AgrabahMaket[] = "Resources/Maps/AgrabahMarket/AgrabahMarket.png";

	_textureAladdin = aladdin;
	_textureGuard = Guard;
	_textureCivilian = Civilian;
	_textureExplosions = Explosions;
	_textureItems = Items;
	_texturePeddler = Peddler;
	_textureFlagPole = FlagPole;
	_textureCamel = Camel;
	_textureHandPot = HandPot;
	_textureAgrabahMarket = AgrabahMaket;

	//Intro animation
	_animationXMLIntro = new tinyxml2::XMLDocument();
	_animationXMLIntro->LoadFile("Resources/Scenes/IntroScene.xml");

	//man boss:
	char MapBoss[] = "Resources/Maps/JafarPlace/TestMap.png";
	_textureMapBoss = MapBoss;

	_animationXMLJafar = new tinyxml2::XMLDocument();
	_animationXMLJafar->LoadFile("Resources/Enemies/Jafar.xml");

	_animationXMLSnake = new tinyxml2::XMLDocument();
	_animationXMLSnake->LoadFile("Resources/Enemies/Snake-Animations.xml");

	_animationXMLJafarWeapon1 = new tinyxml2::XMLDocument();
	_animationXMLJafarWeapon1->LoadFile("Resources/Weapons/EnemiesWeapons/Jafar-Weapon-1-Animation.xml");

	_animationXMLJafarWeapon2 = new tinyxml2::XMLDocument();
	_animationXMLJafarWeapon2->LoadFile("Resources/Weapons/EnemiesWeapons/Jafar-Weapon-2-Animation.xml");

	char BossJafar[] = "Resources/Enemies/Boss_Sprite.png";
	char Explosions2[] = "Resources/Enemies/Enemy_Explosions_Sprite.png";

	_textureBossJafar = BossJafar;
	_textureExplosions = Explosions2;

	//intro
	char Intro[] = "Resources/New Piskel.png";
	char IntroScene[] = "Resources/IntroScene.png";
	char Intro2[] = "Resources/Intro2.png";
	char Menu[] = "Resources/Scenes/Menu.png";
	char Knife[] = "Resources/Select_Menu.png";
	char Bug[] = "Resources/Bug.jpg";
	char Explain[] = "Resources/Explain.png";
	char Story[] = "Resources/Story.png";

	_textureIntro = Intro;
	_textureIntroScene = IntroScene;
	_textureIntro2 = Intro2;
	_TextureMenu = Menu;
	_TextureKnife = Knife;
	_textureBug = Bug;
	_textureExplain = Explain;
	_textureStory = Story;

	//Music+Sound
	Sound::getInstance()->loadSound("", "null");
	//Nhac nen trong Scene
	Sound::getInstance()->loadSound("Resources/Sounds/Agrabah-Market.wav", "AgrabahMarket");//
	Sound::getInstance()->loadSound("Resources/Sounds/Boss-Battle.wav", "BossTheme");
	Sound::getInstance()->loadSound("Resources/Sounds/Main-Theme.wav", "MenuTheme");//
	Sound::getInstance()->loadSound("Resources/Sounds/Scarab Pickup.wav", "BugSceneTheme");
	//Sound::getInstance()->loadSound("Resources/Sounds/Stage-Clear.wav", "StageClear");
	//Sound::getInstance()->loadSound("Resources/Sounds/Storyline-StageStart.wav", "CutSceneTheme");
	//Intro Dau tien
	Sound::getInstance()->loadSound("Resources/Sounds/Start Gun.wav", "StartGun");
	Sound::getInstance()->loadSound("Resources/Sounds/Iago Squawk.wav", "IagoSquawk");
	Sound::getInstance()->loadSound("Resources/Sounds/Stones Crumble.wav", "StonesCrumble");
	//Am cua Aladdin
	Sound::getInstance()->loadSound("Resources/Sounds/High Sword.wav", "HighSword");//
	Sound::getInstance()->loadSound("Resources/Sounds/Low Sword.wav", "LowSword");//
	Sound::getInstance()->loadSound("Resources/Sounds/Aladdin Hurt.wav", "AladdinAttacked");//
	Sound::getInstance()->loadSound("Resources/Sounds/Aladdin Oof.wav", "AladdinLanding");//
	Sound::getInstance()->loadSound("Resources/Sounds/Aladdin Push.wav", "AladdinPush");//
	Sound::getInstance()->loadSound("Resources/Sounds/Apple Slice.wav", "AladdinThrowApple");
	Sound::getInstance()->loadSound("Resources/Sounds/Flagpole.wav", "AladdinPole");//
	Sound::getInstance()->loadSound("Resources/Sounds/Coming Out.wav", "AladdinRevive");//
	Sound::getInstance()->loadSound("Resources/Sounds/Apple Collect.wav", "AladdinEatApple");//
	Sound::getInstance()->loadSound("Resources/Sounds/Rock Bounce.wav", "AladdinEatRock");//
	Sound::getInstance()->loadSound("Resources/Sounds/Extra Health.wav", "AladdinEatHealth");//
	Sound::getInstance()->loadSound("Resources/Sounds/Continue Point.wav", "AladdinEatCheckpoint");//
	//Sound::getInstance()->loadSound("Resources/Sounds/Earthquake.wav", "AladdinEatLamp");//
	Sound::getInstance()->loadSound("Resources/Sounds/Wow!.wav", "AladdinEatBonus");//
	Sound::getInstance()->loadSound("Resources/Sounds/Yeah.wav", "AladdinEatLive");

	//Am Va cham
	Sound::getInstance()->loadSound("Resources/Sounds/Apple Splat.wav", "appleSplat");//loi keu nhieu lan
	Sound::getInstance()->loadSound("Resources/Sounds/Sword Ching.wav", "SwordChing");//loi keu nhieu lan
	//Sound::getInstance()->loadSound("Resources/Sounds/Clay Pot.wav", "BowlBreak");//loi keu nhieu lan
	Sound::getInstance()->loadSound("Resources/Sounds/Camel Spit.wav", "CamelSpit");//
	Sound::getInstance()->loadSound("Resources/Sounds/Fire From Coal.wav", "CoalFire");//
																					   //Enemy
	//Sound::getInstance()->loadSound("Resources/Sounds/Low Sword.wav", "Attack");//
	Sound::getInstance()->loadSound("Resources/Sounds/Guard Hit 1.wav", "Enemy1Attacked");//
	Sound::getInstance()->loadSound("Resources/Sounds/Guard Hit 2.wav", "Enemy2Attacked");//
	Sound::getInstance()->loadSound("Resources/Sounds/Guard Beckon.wav", "Enemy2Beckon");
	//Sound::getInstance()->loadSound("Resources/Sounds/Guard's Pants.wav", "Enemy3Attacked");//
	//Sound::getInstance()->loadSound("Resources/Sounds/Cloud Poof.wav", "Die");//
																			  //Items
	Sound::getInstance()->loadSound("Resources/Sounds/Tip Toe.wav", "OutofApple");//
																				  //Am tai DieSCene
	Sound::getInstance()->loadSound("Resources/Sounds/Abu Waving.wav", "abu");//
	Sound::getInstance()->loadSound("Resources/Sounds/Genie Fumes.wav", "genie");//
}


ResourceManager::~ResourceManager()
{
	delete _animationXMLAladdin;
	delete _animationXMLGuard;
	delete _animationXMLCivilian;
	delete _animationXMLEnemy5;
	delete _animationXMLAppleWeapon;
	delete _animationXMLEnemy3Weapon;
	delete _animationXMLPlayerHealthMeter;
	delete _animationXMLPlayerUp;
	delete _animationXMLCamel;
	delete _animationXMLHandPot;
	delete _animationXMLIntro;

	delete _textureAladdin;
	delete _textureGuard;
	delete _textureCivilian;
	delete _textureItems;
	delete _textureFlagPole;
	delete _textureCamel;
	delete _textureAgrabahMarket;
	delete _textureHandPot;
	delete _textureIntro;

	//man boss:
	delete _animationXMLJafar;
	delete _animationXMLSnake;
	delete _animationXMLJafarWeapon1;
	delete _animationXMLJafarWeapon2;
	delete _animationXMLExplosions;

	delete _textureBossJafar;
	delete _textureExplosions;
	delete _textureMapBoss;
}


ResourceManager* ResourceManager::GetInstance()
{
	if (!_instance)
		_instance = new ResourceManager();
	return _instance;
}

tinyxml2::XMLDocument* ResourceManager::GetAnimationXMLAladdin()
{
	return _animationXMLAladdin;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLGuard()
{
	return _animationXMLGuard;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLCivilian()
{
	return _animationXMLCivilian;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLEnemy5()
{
	return _animationXMLEnemy5;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLExplosions()
{
	return _animationXMLExplosions;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLAppleWeapon()
{
	return _animationXMLAppleWeapon;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLEnemy3Weapon()
{
	return _animationXMLEnemy3Weapon;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLPlayerHealthMeter()
{
	return _animationXMLPlayerHealthMeter;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLPlayerUp()
{
	return _animationXMLPlayerUp;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLCamel()
{
	return _animationXMLCamel;
}
tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLHandPot()
{
	return _animationXMLHandPot;
}
tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLItems()
{
	return _animationXMLItems;
}
tinyxml2::XMLDocument* ResourceManager::GetAnimationXMLPeddler()
{
	return _animationXMLPeddler;
}
tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLJafar()
{
	return _animationXMLJafar;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLSnake()
{
	return _animationXMLSnake;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLJafarWeapon1()
{
	return _animationXMLJafarWeapon1;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLJafarWeapon2()
{
	return _animationXMLJafarWeapon2;
}

tinyxml2::XMLDocument * ResourceManager::GetAnimationXMLIntro()
{
	return _animationXMLIntro;
}

//Texture
const char* ResourceManager::GetTextureAladdin()
{
	return _textureAladdin;
}

const char* ResourceManager::GetTextureGuard()
{
	return _textureGuard;
}

const char* ResourceManager::GetTextureCivilian()
{
	return _textureCivilian;
}

const char* ResourceManager::GetTextureExplosions()
{
	return _textureExplosions;
}

const char* ResourceManager::GetTextureItems()
{
	return _textureItems;
}

const char* ResourceManager::GetTexturePeddler()
{
	return _texturePeddler;
}

const char* ResourceManager::GetTextureFlagPole()
{
	return _textureFlagPole;
}

const char* ResourceManager::GetTextureCamel()
{
	return _textureCamel;
}
const char* ResourceManager::GetTextureHandPot()
{
	return _textureHandPot;
}
const char* ResourceManager::GetTextureAgrabahMarket()
{
	return _textureAgrabahMarket;
}

const char* ResourceManager::GetTextureBossJafar()
{
	return _textureBossJafar;
}

const char* ResourceManager::GetTextureMapBoss()
{
	return _textureMapBoss;
}

const char* ResourceManager::GetTextureIntro()
{
	return _textureIntro;
}

const char* ResourceManager::GetTextureIntroScene()
{
	return _textureIntroScene;
}

const char* ResourceManager::GetTextureIntro2()
{
	return _textureIntro2;
}

const char* ResourceManager::GetTextureMenu()
{
	return _TextureMenu;
}

const char* ResourceManager::GetTextureKnife()
{
	return _TextureKnife;
}

const char* ResourceManager::GetTextureBug()
{
	return _textureBug;
}

const char* ResourceManager::GetTextureExplain()
{
	return _textureExplain;
}

const char* ResourceManager::GetTextureStory()
{
	return _textureStory;
}


//Quan ly sound
void ResourceManager::playSound(std::string name, bool isloop, int times)
{
	Sound::getInstance()->play(name, isloop, times);
}

void ResourceManager::stopSound(std::string name)
{
	Sound::getInstance()->stop(name);
}

