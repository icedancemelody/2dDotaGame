#include"SettingScene.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

Scene* SettingScene::createScene()

{

	auto scene = Scene::create();



	auto layer = SettingScene::create();



	scene->addChild(layer);



	return scene;

}



bool SettingScene::init() {

	if (!Layer::init())

	{

		return false;

	}



	auto visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	auto top = Sprite::create("/Button/setting_top.png");

	top->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - top->getContentSize().height / 2 - 50));
	top->setScale(1.5f);
	addChild(top);



	auto background = Sprite::create("/BG/settingbg.png");

	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer

	this->addChild(background, -1);

	

	auto musicOnSprite = Sprite::create("/Button/setting_check_on.png");

	auto musicOffSprite = Sprite::create("/Button/setting_check_off.png");

	auto musicOnMenuItem = MenuItemSprite::create(musicOnSprite, NULL);

	auto musicOffMenuItem = MenuItemSprite::create(musicOffSprite, NULL);

	auto musicToggleMenuItem = MenuItemToggle::createWithCallback

	(

		CC_CALLBACK_1(SettingScene::menuMusicToggleCallback, this),

		musicOnMenuItem,

		musicOffMenuItem,

		NULL

	);

	musicToggleMenuItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));



	auto closeItem = MenuItemImage::create(

		"/Button/backButton.png",

		"/Button/backButton-selected.png",

		CC_CALLBACK_1(SettingScene::menuItem1Callback, this));

	float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;

	float y = origin.y + closeItem->getContentSize().height / 2;

	closeItem->setPosition(Vec2(x, y));



	auto menu = Menu::create(musicToggleMenuItem, closeItem, NULL);

	menu->setPosition(Vec2::ZERO);

	this->addChild(menu, 1);





	UserDefault* defaults = UserDefault::getInstance();

	if (defaults->getBoolForKey("music_key")) {

		musicToggleMenuItem->setSelectedIndex(0);

	}

	else {

		musicToggleMenuItem->setSelectedIndex(1);

	}



	return true;

}



void SettingScene::menuMusicToggleCallback(cocos2d::Ref* pSender) {

	UserDefault* defaults = UserDefault::getInstance();

	if (defaults->getBoolForKey("music_key")) {

		defaults->setBoolForKey("music_key", false);

		SimpleAudioEngine::getInstance()->stopBackgroundMusic();

	}

	else {

		defaults->setBoolForKey("music_key", true);

		SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3", true);

	}

}



void SettingScene::menuItem1Callback(cocos2d::Ref* pSender)

{

	Director::getInstance()->popScene();

}