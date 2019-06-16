#include "WelcomeScene.h"

#include "SimpleAudioEngine.h"

#include"StartScene.h"

#include"Helloworldscene.h"

#include"SettingScene.h"

USING_NS_CC;



Scene* WelcomeScene::createScene()

{

	return WelcomeScene::create();

}



// Print useful error message instead of segfaulting when files are not there.

static void problemLoading(const char* filename)

{

	printf("Error while loading: %s\n", filename);

	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");

}



// on "init" you need to initialize your instance

bool WelcomeScene::init()

{

	//////////////////////////////

	// 1. super init first

	if (!Scene::init())

	{

		return false;

	}



	auto visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	/////////////////////////////

	// 2. add a menu item with "X" image, which is clicked to quit the program

	//    you may modify it.



	// add a "close" icon to exit the progress. it's an autorelease object

	auto closeItem = MenuItemImage::create(

		"CloseNormaldawd.png",

		"CloseSelected.png",

		CC_CALLBACK_1(WelcomeScene::menuCloseCallback, this));



	if (closeItem == nullptr ||

		closeItem->getContentSize().width <= 0 ||

		closeItem->getContentSize().height <= 0)

	{

		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");

	}

	else

	{

		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;

		float y = origin.y + closeItem->getContentSize().height / 2;

		closeItem->setPosition(Vec2(x, y));

	}





	/////////////////////////////

	// 3. add your codes below...



	// add a label shows "Hello World"

	// create and initialize a label



	auto label = Label::createWithTTF("FINAL CAMPAGIN", "fonts/Marker Felt.ttf", 64);

	if (label == nullptr)

	{

		problemLoading("'fonts/Marker Felt.ttf'");

	}

	else

	{

		// position the label on the center of the screen

		label->setPosition(Vec2(origin.x + visibleSize.width / 2,

			origin.y + visibleSize.height - label->getContentSize().height));



		// add the label as a child to this layer

		this->addChild(label, 1);

	}



	// add "HelloWorld" splash screen"

	auto background = Sprite::create("/BG/welcomescene.jpg");



	if (background == nullptr)

	{

		problemLoading("'/BG/welcomescene.jpg'");

	}

	else

	{

		// position the sprite on the center of the screen

		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));



		// add the sprite as a child to this layer

		this->addChild(background, -1);

	}



	auto startButton = MenuItemImage::create(

		"/Button/entergame.png",

		"/Button/entergame.png",

		CC_CALLBACK_1(WelcomeScene::menuEnter, this)

	);

	startButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, (visibleSize.height / 3) * 2 + origin.y));



	auto settingButton = MenuItemImage::create(

		"/Button/setting.png",

		"/Button/setting.png",

		CC_CALLBACK_1(WelcomeScene::menuSetting, this)

	);

	settingButton->setPosition(Vec2(50 + origin.x, 50 + origin.y));

	settingButton->setScale(0.5f);

	auto menu = Menu::create(closeItem, startButton, settingButton, NULL);

	menu->setPosition(Vec2::ZERO);

	this->addChild(menu, 1);





	return true;

}





void WelcomeScene::menuCloseCallback(Ref* pSender)

{

	//Close the cocos2d-x game scene and quit the application

	Director::getInstance()->end();



	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/



	//EventCustom customEndEvent("game_scene_close_event");

	//_eventDispatcher->dispatchEvent(&customEndEvent);





}



void WelcomeScene::menuEnter(Ref* pSender)

{

	auto sc = StartScene::createScene();

	auto reScene = TransitionTurnOffTiles::create(0.5f, sc);

	Director::getInstance()->pushScene(reScene);

}



void WelcomeScene::menuSetting(cocos2d::Ref* pSender)

{

	auto sc = SettingScene::createScene();

	Director::getInstance()->pushScene(sc);

}