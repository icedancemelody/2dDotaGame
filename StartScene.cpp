#include "StartScene.h"
#include"GameMap.h"
USING_NS_CC;

Scene* StartScene::createScene()
{
	auto scene = Scene::create();

	auto layer = StartScene::create();

	scene->addChild(layer);

	return scene;
}

bool StartScene::init() {
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//选择英雄文字提示
	auto label = Label::createWithTTF("CHOOSE YOUR HERO!!", "fonts/Marker Felt.ttf", 50);
	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + (visibleSize.height/4)*3 - label->getContentSize().height));
		// add the label as a child to this layer
	this->addChild(label, -1);

	//背景图建立
	auto bg = Sprite::create("Chooseherobackground.png");
	bg->setPosition(Vec2(
		origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2
	));
	this->addChild(bg, -2);
	
	//回到开始画面按钮
	auto closeItem = MenuItemImage::create(
		"backButton.png",
		"backButton-selected.png",
		CC_CALLBACK_1(StartScene::menuItem1Callback, this));
	float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
	float y = origin.y + closeItem->getContentSize().height / 2;
	closeItem->setPosition(Vec2(x, y));
		
	
	//选择英雄头像建立
	auto heroButton_1= MenuItemImage::create(
		"/Hero/Hero1touxiang.png",
		"/Hero/Hero1touxiang,png",
		CC_CALLBACK_1(StartScene::menuEnterWarrior, this)
	);
	heroButton_1->setPosition(Vec2((visibleSize.width / 5)*2  -100+origin.x, (visibleSize.height / 5)*2 + origin.y));

	auto heroButton_2= MenuItemImage::create(
		"/Hero/Hero2touxiang.png",
		"/Hero/Hero2touxiang,png",
		CC_CALLBACK_1(StartScene::menuEnterMega, this)
	);
	heroButton_2->setPosition(Vec2((visibleSize.width / 5) * 2 +100+ origin.x, (visibleSize.height / 5) * 2 + origin.y));

	auto heroButton_3 = MenuItemImage::create(
		"/Hero/Hero3touxiang.png",
		"/Hero/Hero3touxiang,png",
		CC_CALLBACK_1(StartScene::menuEnterShooter, this)
	);
	heroButton_3->setPosition(Vec2((visibleSize.width / 5) * 2 +300+ origin.x, (visibleSize.height / 5) * 2 + origin.y));
	
	auto menu = Menu::create(closeItem, heroButton_1, heroButton_2, heroButton_3, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 0);
		
	return true;
}

void StartScene::menuItem1Callback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

void StartScene::menuEnterWarrior(cocos2d::Ref* pSender){//选择英雄为战士
	auto scene = GameMap::createScene("warrior");
	Director::getInstance()->pushScene(scene);
}
void StartScene::menuEnterShooter(cocos2d::Ref* pSender) {
	auto scene = GameMap::createScene("mage");
	Director::getInstance()->pushScene(scene);
}
void StartScene::menuEnterMega(cocos2d::Ref* pSender) {
	auto scene = GameMap::createScene("shooter");
	Director::getInstance()->pushScene(scene);
}