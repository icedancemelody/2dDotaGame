#include"GameMap.h"

USING_NS_CC;

#define JCHM 133
#define TIMER 233
Scene* GameMap::createScene()
{
	auto scene = Scene::create();

	auto layer = GameMap::create();

	scene->addChild(layer);

	return scene;
}

bool GameMap::init() {
	if (!Layer::init()) {
		return false;
	}
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	_tileMap = TMXTiledMap::create("Map/bg_tiledMap.tmx");
	_tileMap->setPosition(Vec2(origin.x ,
		origin.y));
	_tileMap->setAnchorPoint(Vec2(0,0));
	this->addChild(_tileMap, -1, JCHM);

	TMXObjectGroup *objG = _tileMap->getObjectGroup("Object1");
	auto object = objG->getObject("PlayerBorn");
	float x = object["x"].asFloat();
	float y = object["y"].asFloat();

	Sprite* sprite = Sprite::create("/Hero/Male_2_stand.png");
	_tileMap->addChild(sprite, 2);
		
	//设置精灵的位置
	sprite->setPosition(Vec2(x, y));

	//设置精灵的描点为左下角
	sprite->setAnchorPoint(Vec2(0, 0));

	Animation* animation = Animation::create();
	for (int i = 1; i < 7; i++) {
		char file_name[50] = { 0 };
		sprintf(file_name, "Hero/Male_warrior_%d_run.png", i);
		animation->addSpriteFrameWithFile(file_name);
	}
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(2.0f / 10.0f);
	animation->setLoops(-1);
	Animate* animate = Animate::create(animation);
	sprite->runAction(animate);
	
	//设置人物血条
	m_pBloodView = new bloodView();
	m_pBloodView->setPosition(Vec2(130,550));//位置（可自己调整）
	m_pBloodView->setScale(2.2f);//缩放比例
	m_pBloodView->setBackgroundTexture("/sprite/xue_back.png");//灰条
	m_pBloodView->setForegroundTexture("/sprite/xue_fore.png");//红条
	m_pBloodView->setTotalBlood(100.0f);//从满血开始
	m_pBloodView->setCurrentBlood(100.0f);//从满血开始
	Sprite *xuekuang= Sprite::create("/sprite/kuang.png");//血量框
	xuekuang->setPosition(Vec2(m_pBloodView->getPositionX(), m_pBloodView->getPositionY()));
	this->addChild(xuekuang, 2);
	this->addChild(m_pBloodView, 2);
	
	
	auto shopItem= MenuItemImage::create(
		"/Button/shopbutton.png",
		"/Button/shopbutton.png",
		CC_CALLBACK_1(GameMap::createShopCallBack, this));
	float spmn_x = origin.x + shopItem->getContentSize().width / 2;
	float spmn_y = origin.y + visibleSize.height / 2 - shopItem->getContentSize().height / 2;
	shopItem->setPosition(Vec2(spmn_x, spmn_y));

	auto menu = Menu::create(shopItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 5,333);

	time = 0;
	auto timelabel = Label::createWithTTF("00:00", "fonts/Marker Felt.ttf", 30);
	timelabel->setPosition(Vec2(origin.x + visibleSize.width-timelabel->getContentSize().width,
		origin.y + visibleSize.height - timelabel->getContentSize().height));
	this->addChild(timelabel, 2,TIMER);
	this->scheduleUpdate();
	this->schedule(schedule_selector(GameMap::updatetime), 1.0f);
	
	return true;
}


/*void GameMap::initBG() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//添加背景地图
	auto bg = TMXTiledMap::create("/pd_tilemap.tmx/");
	this->addChild(bg, -2, JCHM);

	//添加发光背景

	//添加背景精灵1



}

void GameMap::onExit() {
	Layer::onExit();
	//停止调用射子弹函数
	//注销事件监听器

	auto nodes = this->getChildren();
	for (const auto&node : nodes) {
		if (node->getTag() != JCHM) {
			this->removeChild(node);
		}
	}
}

void GameMap::onEnter() {
	Layer::onEnter();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto pauseSprite = Sprite::createWithSpriteFrameName("");
	auto pauseMenuItem = MenuItemSprite::create(, , CC_CALLBACK_1(GameMap::menuPauseCallBack, this));
	auto pauseMenu = Menu::create(pauseMenuItem, NULL);
	pauseMenu->setPosition(Vec2(30, visibleSize.height - 28));
	this->addChild(pauseMenu, 20, 999);
}

void GameMap::menuPauseCallBack(cocos2d::Ref* pSender) {
	log("menuPauseCallBack");
	this->pause();
	for (const auto&node : this->getChildren()) {
		node->pause();
		}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	//返回主菜单
	auto backNormal = Sprite::createWithSpriteFrameName("");
	auto backSelected = Sprite::createWithSpriteFrameName("");
	auto backMenuItem = MenuItemSprite::create(backNormal, backSelected, CC_CALLBACK_1(GameMap::menuBackCallback, this));


}*/

//商店的创建
void GameMap::createShopCallBack(cocos2d::Ref* pSender) {
	//_player->stopAllActions();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//if (IS_SHOP_OPEN) { return; }
	//shopbackground
    _shopLayer = Layer::create();
	auto _shopBg = Sprite::create("BG/shopbg.png");
	_shopBg->setPosition(Vec2(
		visibleSize.width / 2,
		visibleSize.height/2
	));
	//closebutton
	auto closeShopButton = MenuItemImage::create(
		"/Button/shopButtonNormal.png",
		"/Button/shopButtonSelected.png",
		CC_CALLBACK_1(GameMap::closeShopCallBack, this)
	);
	closeShopButton->setPosition(_shopBg->getPosition() + Vec2(320, -140));
	
	//item
	auto itemCloth = MenuItemImage::create(
		"/equipment/cloth.png",
		"/equipment/cloth.png",
		CC_CALLBACK_1(GameMap::buyItemCallBack, this)
	);
	itemCloth->setPosition(_shopBg->getPosition() + Vec2(-100, -50));

	auto itemSword = MenuItemImage::create(
		"/equipment/sword.png",
		"/equipment/sword.png",
		CC_CALLBACK_1(GameMap::buyItemCallBack, this)
	);
	itemSword->setPosition(_shopBg->getPosition() + Vec2(100, -50));
	
	//shopshow
	Sprite* shopsprite = Sprite::create("shop.png");
	shopsprite->setPosition(_shopBg->getPosition() + Vec2(0, 100));
	_shopLayer->addChild(shopsprite, 2);
	//menucreate
	auto mn = Menu::create(closeShopButton,itemCloth ,itemSword,NULL);
	mn->setPosition(Vec2::ZERO);
	_shopLayer->addChild(mn, 6);
	_shopLayer->addChild(_shopBg);
	this->addChild(_shopLayer, 5,JCHM);
}

//商店的关闭
void GameMap::closeShopCallBack(cocos2d::Ref* pSender) {
	_shopLayer->removeFromParent();
}
void GameMap::buyItemCallBack(cocos2d::Ref* pSender){
	
}

void GameMap::updatetime(float dt) {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->getChildByTag(TIMER)->removeFromParent();
	time++;
	int minutes = time / 60;
	int seconds = time - minutes * 60;
	std::string left = std::to_string(minutes);
	std::string right=std::to_string(seconds);
	if (minutes < 10) {
		left = "0" + left;
	}
	if (seconds< 10) {
		right = "0" + right;
	}
	auto timelabel = Label::createWithTTF(left+":"+right, "fonts/Marker Felt.ttf", 30);
	timelabel->setPosition(Vec2(origin.x + visibleSize.width - timelabel->getContentSize().width,
		origin.y + visibleSize.height  - timelabel->getContentSize().height));
	this->addChild(timelabel, 2,TIMER);
	m_pBloodView->setCurrentBlood(m_pBloodView->getCurrentBlood() - 1);
}

