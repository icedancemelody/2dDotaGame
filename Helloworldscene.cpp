#include "HelloWorldScene.h"

#include "SimpleAudioEngine.h"

#include<iostream>
#include<string.h>

#define TIMER 233
USING_NS_CC;

float sprite1_position_x;
float sprite1_position_y;
float x_touch;
float y_touch;
int countx, county;
float flytime = 0.2;//子弹飞行时间
int number_soider = 1;//第几波兵
int attack_distance;//攻击距离
int maxexp = 340;
int exp_increase = 100;
int jishashu = 0;
int budaoshu = 0;
int kill = 0;
int dead = 0;
int hero_type;
int time_again = 1;
int buytimes = 0;

hero _plane(1000, 100, 160, 10, 20, 100, 100, 3, 100, 100, 0, 1000, 400);

hero _sprite2(1000, 100, 100, 10, 20, 100, 100, 3, 100, 100, 0, 600, 400);



Scene* HelloWorld::createScene(std::string HeroName)

{

	Scene *sc = Scene::create();

	auto *ly = HelloWorld::create();

	ly->initWithName(HeroName);

	sc->addChild(ly);

	return sc;

}

void HelloWorld::initWithName(std::string HeroName) {
	heroname = HeroName;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	maplayer = Layer::create();
	_tileMap = TMXTiledMap::create("bg_tiledMap.tmx");
	_tileMap->setPosition(Vec2(origin.x, origin.y));
	_tileMap->setAnchorPoint(Vec2(0, 0));
	maplayer->addChild(_tileMap, 0);
	this->addChild(maplayer, -1, 100);

	//设置层
	_setLayer = Layer::create();
	_shopLayer = Layer::create();




	TMXObjectGroup *objG = _tileMap->getObjectGroup("Object1");
	auto object = objG->getObject("PlayerBorn");
	float a = object["x"].asFloat();
	float b = object["y"].asFloat();
	log("%f,%f", a, b);



	time = 0;
	auto timelabel = Label::createWithTTF("00:00", "fonts/Marker Felt.ttf", 30);
	timelabel->setPosition(Vec2(origin.x + visibleSize.width - timelabel->getContentSize().width,
		origin.y + visibleSize.height - timelabel->getContentSize().height));
	this->addChild(timelabel, 2, TIMER);
	this->schedule(schedule_selector(HelloWorld::updatetime), 1.0f);
	//动画
	//创建英雄
	hero1 = Hero::create();
	hero2 = Hero::create();
	if (heroname == "warrior") {
		_plane.attackrange = 200;
		run_num = 6;
		att_num = 5;
		string1 = "/warrior/Male_warrior_run_";
		run_name = string1.c_str();
		string2 = "/warrior/Male_warrior_attack_";
		att_name = string2.c_str();
		string3 = "/shooter/Male_shooter_attack_";
		hero1->InitHeroSprite("warrior/Male_warrior_stand_1.png");
		hero_type = 1;
		hero2->InitHeroSprite("shooter/Male_shooter_stand_1.png");
		_sprite2.attackrange = 500;
		otherheroname = "shooter";
		att_num1 = 7;
		att_name1 = string3.c_str();

		for (int i = 0; i < 3; i++) {
			if (i == 0) {
				skill1 = "warrior_skill1.png";
				skill_name[0] = skill1.c_str();
			}
			if (i == 1) {
				skill2 = "warrior_skill2.png";
				skill_name[1] = skill2.c_str();
			}
			if (i == 2) {
				skill3 = "warrior_skill3.png";
				skill_name[2] = skill3.c_str();
			}
		}
	}

	if (heroname == "shooter") {
		_plane.attackrange = 500;
		run_num = 4;
		att_num = 7;
		string1 = "/shooter/Male_shooter_run_";
		run_name = string1.c_str();
		string2 = "/shooter/Male_shooter_attack_";
		att_name = string2.c_str();
		string3 = "/mage/Female_mage_attack_";
		hero1->InitHeroSprite("shooter/Male_shooter_stand_1.png");
		hero_type = 2;
		hero2->InitHeroSprite("mage/Female_mage_stand_1.png");
		_sprite2.attackrange = 400;
		att_num1 = 2;
		otherheroname = "mage";
		att_name1 = string3.c_str();
		for (int i = 0; i < 3; i++) {
			if (i == 0) {
				skill1 = "shooter_skill1.png";
				skill_name[i] = skill1.c_str();
			}
			if (i == 1) {
				skill2 = "shooter_skill2.png";
				skill_name[i] = skill2.c_str();
			}
			if (i == 2) {
				skill3 = "shooter_skill3.png";
				skill_name[i] = skill3.c_str();
			}
		}
	}

	if (heroname == "mage") {
		_plane.attackrange = 400;
		run_num = 6;
		att_num = 2;
		string1 = "/mage/Female_mage_run_";
		run_name = string1.c_str();
		string2 = "/mage/Female_mage_attack_";
		att_name = string2.c_str();
		string3 = "/warrior/Male_warrior_attack_";
		hero1->InitHeroSprite("mage/Female_mage_stand_1.png");
		hero2->InitHeroSprite("warrior/Male_warrior_stand_1.png");
		hero_type = 3;
		otherheroname = "warrior";
		_sprite2.attackrange = 200;
		att_num1 = 5;
		att_name1 = string3.c_str();
		for (int i = 0; i < 3; i++) {
			if (i == 0) {
				skill1 = "mage_skill1.png";
				skill_name[i] = skill1.c_str();
			}
			if (i == 1) {
				skill2 = "mage_skill2.png";
				skill_name[i] = skill2.c_str();
			}
			if (i == 2) {
				skill3 = "mage_skill3.png";
				skill_name[i] = skill3.c_str();
			}
		}
	}

	Sprite* skill[3];
	for (int i = 0; i < 3; i++) {
		skill[i] = Sprite::create(skill_name[i]);
		skill[i]->setPosition(Vec2(350 + (130 * i), 50));
		_setLayer->addChild(skill[i], 1);
	}
	for (int i = 0; i < 3; i++) {
		Sprite* progressSprite = Sprite::create("zhe.png");
		mProgressTimer[i] = ProgressTimer::create(progressSprite);
		mProgressTimer[i]->setPosition(Vec2(350 + (130 * i), 50));
		_setLayer->addChild(mProgressTimer[i], 2);
	}

	//hero1->InitHeroSprite("male_shooter/Male_shooter_stand_1.png");
	hero1->setPosition(Vec2(a + 100, b + 200));
	hero1->setScale(1);
	maplayer->addChild(hero1, 2, 1);

	hero2->setPosition(Vec2(a + 6100, b + 200));
	hero2->setScale(1);
	maplayer->addChild(hero2, 2, 1001);



	auto tower1 = Tower::createWithTowerTypes(TowerType1);
	tower1->setPosition(Vec2(300, 200));
	tower1->setScale(1.2f);
	maplayer->addChild(tower1, 1, 3);


	auto tower2 = Tower::createWithTowerTypes(TowerType1);
	tower2->setPosition(Vec2(2500, 200));
	tower2->setScale(1.2f);
	maplayer->addChild(tower2, 1, 4);


	auto tower3 = Tower::createWithTowerTypes(TowerType3);
	tower3->setPosition(Vec2(3900, 200));
	tower3->setScale(1.2f);
	maplayer->addChild(tower3, 1, 1003);


	auto tower4 = Tower::createWithTowerTypes(TowerType3);
	tower4->setPosition(Vec2(6100, 200));
	tower4->setScale(1.2f);
	maplayer->addChild(tower4, 1, 1004);


	auto home1 = Tower::createWithTowerTypes(TowerType2);
	home1->setPosition(Vec2(100, 200));
	home1->setScale(1.2f);
	maplayer->addChild(home1, 1, 2);


	auto home2 = Tower::createWithTowerTypes(TowerType4);
	home2->setPosition(Vec2(6300, 200));
	home2->setScale(1.2f);
	maplayer->addChild(home2, 1, 1002);

	this->schedule(schedule_selector(HelloWorld::updatefriend), (1.5f));
	this->schedule(schedule_selector(HelloWorld::updatefriendtower), (3.0f));
	this->schedule(schedule_selector(HelloWorld::updateenemy), (1.5f));
	this->schedule(schedule_selector(HelloWorld::updateenemytower), (3.0f));
	this->schedule(schedule_selector(HelloWorld::updateattacked), (3.0f));
	this->schedule(schedule_selector(HelloWorld::updateattackedenemy), (3.0f));
	this->schedule(schedule_selector(HelloWorld::updateattacked1), (1.5f));
	this->schedule(schedule_selector(HelloWorld::updateattacked1enemy), (1.5f));
	this->schedule(schedule_selector(HelloWorld::updateenemyheromove));
	this->schedule(schedule_selector(HelloWorld::updateenemyheroattack), (1.0f));
	this->schedule(schedule_selector(HelloWorld::updateenemyheroattackhero), (1.0f));
	this->schedule(schedule_selector(HelloWorld::updatequanshui));
	auto listenerkeyPad = EventListenerKeyboard::create();


	listenerkeyPad->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys[keyCode] = true;
		auto W_key = cocos2d::EventKeyboard::KeyCode::KEY_W;
		auto A_key = cocos2d::EventKeyboard::KeyCode::KEY_A;
		auto S_key = cocos2d::EventKeyboard::KeyCode::KEY_S;
		auto D_key = cocos2d::EventKeyboard::KeyCode::KEY_D;
		if (isKeyPressed(W_key)) {
			hero1->SetAnimation(run_name, run_num, hero1->HeroDirecton);
		}

		if (isKeyPressed(A_key)) {
			hero1->HeroDirecton = true;
			hero1->SetAnimation(run_name, run_num, hero1->HeroDirecton);
		}

		if (isKeyPressed(S_key)) {
			hero1->SetAnimation(run_name, run_num, hero1->HeroDirecton);
		}

		if (isKeyPressed(D_key)) {
			hero1->HeroDirecton = false;
			hero1->SetAnimation(run_name, run_num, hero1->HeroDirecton);
		}
	};

	listenerkeyPad->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys[keyCode] = false;
		hero1->StopAnimation();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);





	this->scheduleUpdate();


	auto listenerkeyPad1 = EventListenerKeyboard::create();
	listenerkeyPad1->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad1, this);


	auto myListener = EventListenerTouchOneByOne::create();
	myListener->setSwallowTouches(true);
	myListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::touchBegan, this);

	myListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::touchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myListener, this);
	//scenemove(mapTild, plane, _tileMap);


	//设置人物血条
	m_pBloodView = new bloodView();
	m_pBloodView->setPosition(Vec2(130, 550));
	m_pBloodView->setScale(2.2f);
	m_pBloodView->setBackgroundTexture("xue_back.png");
	m_pBloodView->setForegroundTexture("xue_fore.png");
	m_pBloodView->setTotalBlood(100.0f);
	m_pBloodView->setCurrentBlood(100.0f);
	Sprite *xuekuang = Sprite::create("kuang.png");
	xuekuang->setPosition(Vec2(m_pBloodView->getPositionX(), m_pBloodView->getPositionY()));
	this->addChild(xuekuang, 2);
	this->addChild(m_pBloodView, 2);
	//设置人物血条1
	m_pBloodView1 = new bloodView();
	m_pBloodView1->setPosition(Vec2(830, 550));
	m_pBloodView1->setScale(2.2f);
	m_pBloodView1->setBackgroundTexture("xue_back.png");
	m_pBloodView1->setForegroundTexture("xue_fore.png");
	m_pBloodView1->setTotalBlood(100.0f);
	m_pBloodView1->setCurrentBlood(100.0f);
	Sprite *xuekuang1 = Sprite::create("kuang.png");
	xuekuang1->setPosition(Vec2(m_pBloodView1->getPositionX(), m_pBloodView1->getPositionY()));
	this->addChild(xuekuang1, 2);
	this->addChild(m_pBloodView1, 2);

	//记分板
	auto ScoreItem = MenuItemImage::create(
		"scoreboard.png",
		"scoreboard.png",
		CC_CALLBACK_1(HelloWorld::createScoreCallBack, this)
	);
	float board_x = origin.x + ScoreItem->getContentSize().width / 2 + 10;
	float board_y = origin.y + visibleSize.height / 2 - ScoreItem->getContentSize().height / 2 - 60;
	ScoreItem->setPosition(Vec2(board_x, board_y));

	//商店按钮
	auto shopItem = MenuItemImage::create(
		"/Button/shopButton666.png",
		"/Button/shopButton666.png",
		CC_CALLBACK_1(HelloWorld::createShopCallBack, this));
	float spmn_x = origin.x + shopItem->getContentSize().width / 2;
	float spmn_y = origin.y + visibleSize.height / 2 - shopItem->getContentSize().height / 2 + 30;
	shopItem->setPosition(Vec2(spmn_x, spmn_y));

	// 暂停按钮

	auto SettingItem = MenuItemImage::create(

		"/Button/setting.png",

		"/Button/setting.png",

		CC_CALLBACK_1(HelloWorld::createSettingCallBack, this));



	SettingItem->setPosition(Vec2(

		visibleSize.width - SettingItem->getContentSize().width / 2 + 30,

		SettingItem->getContentSize().height / 2 - 40

	));

	SettingItem->setScale(0.3f);

	auto menu = Menu::create(ScoreItem, shopItem, SettingItem, NULL);
	menu->setPosition(Vec2::ZERO);
	_setLayer->addChild(menu, 1);
	this->addChild(_setLayer, 5, 636);
}

//技能冷却图标
void HelloWorld::BeginSkill(int i, int cd) {
	mProgressTimer[i]->setType(cocos2d::ProgressTimerType(kCCProgressTimerTypeRadial));
	ProgressTo *t = ProgressTo::create(cd, 100);
	CallFunc* callFunc;
	if (i == 0) { callFunc = CallFunc::create(this, callfunc_selector(HelloWorld::EndSkill1)); }
	if (i == 1) { callFunc = CallFunc::create(this, callfunc_selector(HelloWorld::EndSkill2)); }
	if (i == 2) { callFunc = CallFunc::create(this, callfunc_selector(HelloWorld::EndSkill3)); }
	ActionInterval* act = Sequence::create(t, callFunc, NULL);
	mProgressTimer[i]->setVisible(true);
	mProgressTimer[i]->runAction(act);

}

void HelloWorld::EndSkill1() {
	mProgressTimer[0]->setVisible(false);
}
void HelloWorld::EndSkill2() {
	mProgressTimer[1]->setVisible(false);
}
void HelloWorld::EndSkill3() {
	mProgressTimer[2]->setVisible(false);
}

//地图随主角移动:获得主角在地图的相对位置，并设置地图位置。
Point scenemove(Hero *plane, TMXTiledMap *_tileMap, Vec2 vPos)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size mapTiledNum = _tileMap->getMapSize();

	Size mapTild = _tileMap->getTileSize();

	Size mapSize = Size(mapTiledNum.width * mapTild.width, mapTiledNum.height * mapTild.height);
	float x = MAX(vPos.x, visibleSize.width / 2);
	float y = MAX(vPos.y, visibleSize.height / 2);
	x = MIN(x, mapSize.width - visibleSize.width / 2);
	y = MIN(y, mapSize.height - visibleSize.height / 2);
	Vec2 destPos = Vec2(x, y);
	Vec2 centerPos = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	Vec2 viewPos = centerPos - destPos;

	if (viewPos.x < 0) {
		countx = -viewPos.x / 2;
	}

	return Vec2(viewPos);
}

static void problemLoading(const char* filename)

{

	printf("Error while loading: %s\n", filename);

	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");

}




bool HelloWorld::init()

{


	if (!Layer::init())

	{

		return false;

	}


	return true;

}


void HelloWorld::createShopCallBack(cocos2d::Ref* pSender) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (shop_is_open == true || score_is_open == true) { return; }
	//shoplayer
	_shopLayer = Layer::create();
	auto _shopBg = Sprite::create("shopbg.png");
	_shopBg->setPosition(Vec2(
		visibleSize.width / 2,
		visibleSize.height / 2
	));
	//closebutton
	auto closeShopButton = MenuItemImage::create(
		"/Button/shopButtonNormal.png",
		"/Button/shopButtonSelected.png",
		CC_CALLBACK_1(HelloWorld::closeShopCallBack, this)
	);
	closeShopButton->setPosition(_shopBg->getPosition() + Vec2(375, -180));

	//show my money
	std::string money = std::to_string((int)_plane.get_gp());
	auto my_money = Label::createWithSystemFont("MONEY:" + money, "fonts/arial-unicode-26.fnt", 30);
	my_money->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 180));
	my_money->setColor(Color3B::BLACK);
	_shopLayer->addChild(my_money, 2);
	//item
	MenuItemImage* ItemSword[4];
	MenuItemImage* ItemCloth[4];
	MenuItemImage* ItemLive[4];
	MenuItemImage* ItemShoe[4];
	for (int i = 1; i < 5; i++) {
		char fileName[50] = { 0 };
		char callbackname[50] = { 0 };
		std::string money;
		std::string dscb;
		if (i == 1) {
			money = "300g";
			dscb = "Attack+10";
		}
		if (i == 2) {
			money = "700g";
			dscb = "Attack+50";
		}
		if (i == 3) {
			money = "1300g";
			dscb = "Attack+100";
		}
		if (i == 4) {
			money = "2000g";
			dscb = "Attack+150";
		}
		sprintf(fileName, "/equipment/sword%d.png", i);
		if (i == 1) {
			ItemSword[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buySwordCallBack1, this)
			);
		}
		if (i == 2) {
			ItemSword[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buySwordCallBack2, this)
			);
		}
		if (i == 3) {
			ItemSword[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buySwordCallBack3, this)
			);
		}
		if (i == 4) {
			ItemSword[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buySwordCallBack4, this)
			);
		}
		ItemSword[i - 1]->setScale(0.8f);
		ItemSword[i - 1]->setPosition(_shopBg->getPosition() + Vec2(-300, 220 - (80 * i)));
		auto money_label = Label::createWithSystemFont(money, "fonts/arial-unicode-26.fnt", 22);
		money_label->setPosition(_shopBg->getPosition() + Vec2(-360, 220 - (80 * i)));
		money_label->setColor(Color3B::BLACK);
		_shopLayer->addChild(money_label, 2);
		auto dscb_label = Label::createWithSystemFont(dscb, "fonts/arial-unicode-26.fnt", 15);
		dscb_label->setPosition(_shopBg->getPosition() + Vec2(-260, 180 - (80 * i)));
		dscb_label->setColor(Color3B::RED);
		_shopLayer->addChild(dscb_label, 2);
	};
	for (int i = 1; i < 5; i++) {
		char fileName[50] = { 0 };
		char callbackname[50] = { 0 };
		sprintf(fileName, "/equipment/cloth%d.png", i);
		std::string money;
		std::string dscb;
		if (i == 1) {
			money = "450g";
			dscb = "Armor+10";
		}
		if (i == 2) {
			money = "1000g";
			dscb = "Armor+50";
		}
		if (i == 3) {
			money = "1500g";
			dscb = "Armor+100";
		}
		if (i == 4) {
			money = "2400g";
			dscb = "Armor+150";
		}
		if (i == 1) {
			ItemCloth[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buyClothCallBack1, this)
			);
		}
		if (i == 2) {
			ItemCloth[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buyClothCallBack2, this)
			);
		}
		if (i == 3) {
			ItemCloth[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buyClothCallBack3, this)
			);
		}
		if (i == 4) {
			ItemCloth[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buyClothCallBack4, this)
			);
		}
		ItemCloth[i - 1]->setScale(0.8f);
		ItemCloth[i - 1]->setPosition(_shopBg->getPosition() + Vec2(-120, 220 - (80 * i)));
		auto money_label = Label::createWithSystemFont(money, "fonts/arial-unicode-26.fnt", 22);
		money_label->setPosition(_shopBg->getPosition() + Vec2(-180, 220 - (80 * i)));
		money_label->setColor(Color3B::BLACK);
		_shopLayer->addChild(money_label, 2);
		auto dscb_label = Label::createWithSystemFont(dscb, "fonts/arial-unicode-26.fnt", 15);
		dscb_label->setPosition(_shopBg->getPosition() + Vec2(-50, 180 - (80 * i)));
		dscb_label->setColor(Color3B::RED);
		_shopLayer->addChild(dscb_label, 2);
	};
	for (int i = 1; i < 5; i++) {
		char fileName[50] = { 0 };
		char callbackname[50] = { 0 };
		sprintf(fileName, "/equipment/live%d.png", i);
		std::string money;
		std::string dscb;
		if (i == 1) {
			money = "400g";
			dscb = "Blood+200";
		}
		if (i == 2) {
			money = "800g";
			dscb = "Blood+500";
		}
		if (i == 3) {
			money = "1200g";
			dscb = "Blood+1200";
		}
		if (i == 4) {
			money = "1600g";
			dscb = "Now Blood Double!!";
		}
		if (i == 1) {
			ItemLive[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buyLiveCallBack1, this)
			);
		}
		if (i == 2) {
			ItemLive[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buyLiveCallBack2, this)
			);
		}
		if (i == 3) {
			ItemLive[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buyLiveCallBack3, this)
			);
		}
		if (i == 4) {
			ItemLive[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buyLiveCallBack4, this)
			);
		}
		ItemLive[i - 1]->setScale(0.8f);
		ItemLive[i - 1]->setPosition(_shopBg->getPosition() + Vec2(120, 220 - (80 * i)));
		auto money_label = Label::createWithSystemFont(money, "fonts/arial-unicode-26.fnt", 22);
		money_label->setPosition(_shopBg->getPosition() + Vec2(60, 220 - (80 * i)));
		money_label->setColor(Color3B::BLACK);
		_shopLayer->addChild(money_label, 2);
		auto dscb_label = Label::createWithSystemFont(dscb, "fonts/arial-unicode-26.fnt", 15);
		dscb_label->setPosition(_shopBg->getPosition() + Vec2(160, 180 - (80 * i)));
		dscb_label->setColor(Color3B::RED);
		_shopLayer->addChild(dscb_label, 2);
	};
	for (int i = 1; i < 5; i++) {
		char fileName[50] = { 0 };
		char callbackname[50] = { 0 };
		sprintf(fileName, "/equipment/shoe%d.png", i);
		std::string money;
		std::string dscb;
		if (i == 1) {
			money = "250g";
			dscb = "Speed+25";
		}
		if (i == 2) {
			money = "800g";
			dscb = "Speed+80";
		}
		if (i == 3) {
			money = "1100g";
			dscb = "Speed+50&Attack+80";
		}
		if (i == 4) {
			money = "1100g";
			dscb = "Speed+50&Armor+80";
		}
		if (i == 1) {
			ItemShoe[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buyShoeCallBack1, this)
			);
		}
		if (i == 2) {
			ItemShoe[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buyShoeCallBack2, this)
			);
		}
		if (i == 3) {
			ItemShoe[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buyShoeCallBack3, this)
			);
		}
		if (i == 4) {
			ItemShoe[i - 1] = MenuItemImage::create(
				fileName,
				fileName,
				CC_CALLBACK_1(HelloWorld::buyShoeCallBack4, this)
			);
		}
		ItemShoe[i - 1]->setScale(0.64f);
		ItemShoe[i - 1]->setPosition(_shopBg->getPosition() + Vec2(300, 220 - (80 * i)));
		auto money_label = Label::createWithSystemFont(money, "fonts/arial-unicode-26.fnt", 22);
		money_label->setPosition(_shopBg->getPosition() + Vec2(240, 220 - (80 * i)));
		money_label->setColor(Color3B::BLACK);
		_shopLayer->addChild(money_label, 2);
		auto dscb_label = Label::createWithSystemFont(dscb, "fonts/arial-unicode-26.fnt", 15);
		dscb_label->setPosition(_shopBg->getPosition() + Vec2(330, 180 - (80 * i)));
		dscb_label->setColor(Color3B::RED);
		_shopLayer->addChild(dscb_label, 2);
	}
	//shopshow
	Sprite* shopsprite = Sprite::create("shop.png");
	shopsprite->setPosition(_shopBg->getPosition() + Vec2(0, 190));
	_shopLayer->addChild(shopsprite, 2);
	//menucreate
	auto mn = Menu::create(closeShopButton,
		ItemSword[0], ItemSword[1], ItemSword[2], ItemSword[3],
		ItemCloth[0], ItemCloth[1], ItemCloth[2], ItemCloth[3],
		ItemLive[0], ItemLive[1], ItemLive[2], ItemLive[3],
		ItemShoe[0], ItemShoe[1], ItemShoe[2], ItemShoe[3],
		NULL);
	mn->setPosition(Vec2::ZERO);
	_shopLayer->addChild(mn, 6);
	_shopLayer->addChild(_shopBg);
	this->addChild(_shopLayer, 5);
	shop_is_open = true;
}

//商店的关闭
void HelloWorld::closeShopCallBack(cocos2d::Ref* pSender) {
	shop_is_open = false;
	_shopLayer->removeFromParent();
}
void HelloWorld::buySwordCallBack1(cocos2d::Ref* pSender) {
	if (_plane._gp < 300 || _plane.eqp_num == 6) { return; }
	_plane._ad += 10;
	_plane._gp -= 300;
	_plane.me_have[0][0] = true;
	_plane.me_this_eqp[0][0]++;
	_plane.eqp_num++;
}
void HelloWorld::buySwordCallBack2(cocos2d::Ref* pSender) {
	if (_plane._gp < 700 || _plane.me_have[0][0] == false) { return; }
	_plane._ad += 40;
	_plane._gp -= 700;
	_plane.me_have[0][0] = false;
	_plane.me_have[0][1] = true;
	_plane.me_this_eqp[0][0]--;
	_plane.me_this_eqp[0][1]++;
}
void HelloWorld::buySwordCallBack3(cocos2d::Ref* pSender) {
	if (_plane._gp < 1300 || _plane.me_have[0][1] == false) { return; }
	_plane._ad += 50;
	_plane._gp -= 1300;
	_plane.me_have[0][1] = false;
	_plane.me_have[0][2] = true;
	_plane.me_this_eqp[0][1]--;
	_plane.me_this_eqp[0][2]++;
}
void HelloWorld::buySwordCallBack4(cocos2d::Ref* pSender) {
	if (_plane._gp < 2000 || _plane.me_have[0][2] == false) { return; }
	_plane._ad += 50;
	_plane._gp -= 2000;
	_plane.me_have[0][2] = false;
	_plane.me_have[0][3] = true;
	_plane.me_this_eqp[0][2]--;
	_plane.me_this_eqp[0][3]++;
}
void HelloWorld::buyClothCallBack1(cocos2d::Ref* pSender) {
	if (_plane._gp < 450 || _plane.eqp_num == 6) { return; }
	_plane._hujia += 10;
	_plane._gp -= 450;
	_plane.me_have[1][0] = true;
	_plane.me_this_eqp[1][0]++;
	_plane.eqp_num++;
}
void HelloWorld::buyClothCallBack2(cocos2d::Ref* pSender) {
	if (_plane._gp < 1000 || _plane.me_have[1][0] == false) { return; }
	_plane._hujia += 40;
	_plane._gp -= 1000;
	_plane.me_have[1][0] = false;
	_plane.me_have[1][1] = true;
	_plane.me_this_eqp[1][0]--;
	_plane.me_this_eqp[1][1]++;
}
void HelloWorld::buyClothCallBack3(cocos2d::Ref* pSender) {
	if (_plane._gp < 1500 || _plane.me_have[1][1] == false) { return; }
	_plane._hujia += 50;
	_plane._gp -= 1500;
	_plane.me_have[1][1] = false;
	_plane.me_have[1][2] = true;
	_plane.me_this_eqp[1][1]--;
	_plane.me_this_eqp[1][2]++;
}
void HelloWorld::buyClothCallBack4(cocos2d::Ref* pSender) {
	if (_plane._gp < 2400 || _plane.me_have[1][2] == false) { return; }
	_plane._hujia += 50;
	_plane._gp -= 2400;
	_plane.me_have[1][2] = false;
	_plane.me_have[1][3] = true;
	_plane.me_this_eqp[1][2]--;
	_plane.me_this_eqp[1][3]++;
}
void HelloWorld::buyLiveCallBack1(cocos2d::Ref* pSender) {
	if (_plane._gp < 400 || _plane.eqp_num == 6) { return; }
	_plane._max_blood += 200;
	_plane._blood += 200;
	_plane._gp -= 400;
	_plane.me_have[2][0] = true;
	_plane.me_this_eqp[2][0]++;
	_plane.eqp_num++;
}
void HelloWorld::buyLiveCallBack2(cocos2d::Ref* pSender) {
	if (_plane._gp < 800 || _plane.me_have[2][0] == false) { return; }
	_plane._max_blood += 300;
	_plane._blood += 300;
	_plane._gp -= 800;
	_plane.me_have[2][0] = false;
	_plane.me_have[2][1] = true;
	_plane.me_this_eqp[2][0]--;
	_plane.me_this_eqp[2][1]++;
}
void HelloWorld::buyLiveCallBack3(cocos2d::Ref* pSender) {
	if (_plane._gp < 1200 || _plane.me_have[2][1] == false) { return; }
	_plane._max_blood += 700;
	_plane._blood += 700;
	_plane._gp -= 1200;
	_plane.me_have[2][1] = false;
	_plane.me_have[2][2] = true;
	_plane.me_this_eqp[2][1]--;
	_plane.me_this_eqp[2][2]++;
}
void HelloWorld::buyLiveCallBack4(cocos2d::Ref* pSender) {
	if (_plane._gp < 1600 || _plane.me_have[2][2] == false) { return; }
	_plane._blood += _plane._max_blood;
	_plane._max_blood += _plane._max_blood;
	_plane._gp -= 1600;
	_plane.me_have[2][2] = false;
	_plane.me_have[2][3] = true;
	_plane.me_this_eqp[2][2]--;
	_plane.me_this_eqp[2][3]++;
}
bool have_shoe = false;
void HelloWorld::buyShoeCallBack1(cocos2d::Ref* pSender) {
	if (_plane._gp < 250 || _plane.eqp_num == 6 || have_shoe == true) { return; }
	_plane._speed += 1.5;
	_plane._gp -= 250;
	_plane.me_have[3][0] = true;
	_plane.me_this_eqp[3][0]++;
	_plane.eqp_num++;
	have_shoe = true;
}
void HelloWorld::buyShoeCallBack2(cocos2d::Ref* pSender) {
	if (_plane._gp < 800 || _plane.me_have[3][0] == false) { return; }
	_plane._speed += 2.0;
	_plane._gp -= 800;
	_plane.me_have[3][0] = false;
	_plane.me_have[3][1] = true;
	_plane.me_this_eqp[3][0]--;
	_plane.me_this_eqp[3][1]++;
}
void HelloWorld::buyShoeCallBack3(cocos2d::Ref* pSender) {
	if (_plane._gp < 1100 || _plane.me_have[3][0] == false) { return; }
	_plane._speed += 1.5;
	_plane._gp -= 1100;
	_plane._ad += 80;
	_plane.me_have[3][0] = false;
	_plane.me_have[3][2] = true;
	_plane.me_this_eqp[3][0]--;
	_plane.me_this_eqp[3][2]++;
}
void HelloWorld::buyShoeCallBack4(cocos2d::Ref* pSender) {
	if (_plane._gp < 1100 || _plane.me_have[3][0] == false) { return; }
	_plane._speed += 1.5;
	_plane._gp -= 1100;
	_plane._hujia += 80;
	_plane.me_have[3][0] = false;
	_plane.me_have[3][3] = true;
	_plane.me_this_eqp[3][0]--;
	_plane.me_this_eqp[3][3]++;
}
//记分板的建立
void HelloWorld::createScoreCallBack(cocos2d::Ref* pSender) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (score_is_open == true || shop_is_open == true) { return; }
	//Scoreboardbg
	_ScoreboardLayer = Layer::create();
	auto _Bg = Sprite::create("scoreboardbg.jpg");
	_Bg->setPosition(Vec2(
		visibleSize.width / 2,
		visibleSize.height / 2
	));
	//计分记录数据：
	std::string b = std::to_string((int)_plane._level);
	std::string c = std::to_string(kill);
	std::string d = std::to_string(dead);
	std::string e = std::to_string(budaoshu);
	std::string f = std::to_string(jishashu);
	//closebutton
	auto closeScoreButton = MenuItemImage::create(
		"closescore.png",
		"closescore.png",
		CC_CALLBACK_1(HelloWorld::closeScoreCallBack, this)
	);
	closeScoreButton->setPosition(_Bg->getPosition() + Vec2(260, 195));

	//我方战绩（包括英雄类型、击杀数、死亡数、金钱）
	auto my = Label::createWithSystemFont("MY HERO:"+heroname+ "  Lv:" + b, "fonts/arial-unicode-26.fnt", 26);//间隔10字符位
	my->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 160));
	_ScoreboardLayer->addChild(my, 4);

	auto my_kill = Label::createWithSystemFont("KILL:" + c + "  KILL SOIDER : " + e, "fonts/arial-unicode-26.fnt", 26);
	my_kill->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 130));
	_ScoreboardLayer->addChild(my_kill, 4);


	auto my_die = Label::createWithSystemFont("DIE:" + d, "fonts/arial-unicode-26.fnt", 26);
	my_die->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	_ScoreboardLayer->addChild(my_die, 4);

	//敌方战绩（包括英雄类型、击杀数、死亡数、金钱）
	auto other = Label::createWithSystemFont("OTHER HERO:"+otherheroname+"  Lv:"+b, "fonts/arial-unicode-26.fnt", 26);//间隔10字符位
	other->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 70));
	_ScoreboardLayer->addChild(other, 4);

	auto other_kill = Label::createWithSystemFont("KILL:" + d, "fonts/arial-unicode-26.fnt", 26);
	other_kill->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
	_ScoreboardLayer->addChild(other_kill, 4);

	auto other_die = Label::createWithSystemFont("DIE:" + c, "fonts/arial-unicode-26.fnt", 26);
	other_die->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 130));
	_ScoreboardLayer->addChild(other_die, 4);

	//我方装备显示
	int my_show_num = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == 0) {
				if (my_show_num >= 6) { break; }//装备数大于6不再显示
				else {
					if (_plane.me_have[i][j] == true) {
						for (int k = 0; k < _plane.me_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/sword%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (my_show_num * 80), visibleSize.height / 2 + 40));
							eqp_show->setScale(0.75f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							my_show_num++;
						}
					}
				}
			}
			if (i == 1) {
				if (my_show_num >= 6) { break; }//装备数大于6不再显示
				else {
					if (_plane.me_have[i][j] == true) {
						for (int k = 0; k < _plane.me_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/cloth%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (my_show_num * 80), visibleSize.height / 2 + 40));
							eqp_show->setScale(0.75f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							my_show_num++;
						}
					}
				}
			}
			if (i == 2) {
				if (my_show_num >= 6) { break; }//装备数大于6不再显示
				else {
					if (_plane.me_have[i][j] == true) {
						for (int k = 0; k < _plane.me_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/live%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (my_show_num * 80), visibleSize.height / 2 + 40));
							eqp_show->setScale(0.75f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							my_show_num++;
						}
					}
				}
			}
			if (i == 3) {
				if (my_show_num >= 6) { break; }//装备数大于6不再显示
				else {
					if (_plane.me_have[i][j] == true) {
						for (int k = 0; k < _plane.me_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/shoe%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (my_show_num * 80), visibleSize.height / 2 + 40));
							eqp_show->setScale(0.6f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							my_show_num++;
						}
					}
				}
			}
		}
	}
	//敌方装备显示
	int enemy_show_num = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == 0) {
				if (enemy_show_num >= 6) { break; }//装备数大于6不再显示
				else {

					if (_sprite2.me_have[i][j] == true) {
						for (int k = 0; k < _sprite2.me_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/sword%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (enemy_show_num * 80), visibleSize.height / 2 - 170));
							eqp_show->setScale(0.75f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							enemy_show_num++;
						}
					}
				}
			}
			if (i == 1) {
				if (enemy_show_num >= 6) { break; }//装备数大于6不再显示
				else {
					if (_sprite2.me_have[i][j] == true) {
						for (int k = 0; k < _sprite2.me_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/cloth%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (enemy_show_num * 80), visibleSize.height / 2 - 170));
							eqp_show->setScale(0.75f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							enemy_show_num++;
						}
					}
				}
			}
			if (i == 2) {
				if (enemy_show_num >= 6) { break; }//装备数大于6不再显示
				else {
					if (_sprite2.me_have[i][j] == true) {
						for (int k = 0; k < _sprite2.me_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/live%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (enemy_show_num * 80), visibleSize.height / 2 - 170));
							eqp_show->setScale(0.75f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							enemy_show_num++;
						}
					}
				}
			}
			if (i == 3) {
				if (enemy_show_num >= 6) { break; }//装备数大于6不再显示
				else {
					if (_sprite2.me_have[i][j] == true) {
						for (int k = 0; k < _sprite2.me_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/shoe%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (enemy_show_num * 80), visibleSize.height / 2 - 170));
							eqp_show->setScale(0.6f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							enemy_show_num++;
						}
					}
				}
			}
		}
	}
	auto mn = Menu::create(closeScoreButton, NULL);
	mn->setPosition(Vec2::ZERO);
	_ScoreboardLayer->addChild(mn, 6);
	_ScoreboardLayer->addChild(_Bg);
	_setLayer->addChild(_ScoreboardLayer, 1);
	score_is_open = true;
}
//记分板的关闭
void HelloWorld::closeScoreCallBack(cocos2d::Ref* pSender) {
	score_is_open = false;
	_ScoreboardLayer->removeFromParent();
}

//设置返回游戏或回主菜单
void HelloWorld::createSettingCallBack(cocos2d::Ref* pSender) {

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto visibleSize = Director::getInstance()->getVisibleSize();

	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);

	renderTexture->begin();

	this->getParent()->visit();

	renderTexture->end();



	Director::getInstance()->pushScene(Gamepause::scene(renderTexture));

}


//level up
void level_up()
{
	_plane._ad += 9;
	_plane._hujia += 1;
	_plane._exp = 0;
	maxexp += exp_increase;
	exp_increase += 40;
	_plane._level++;
}

void HelloWorld::be_attacked2(hero a, Soider* b) {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int x155 = b->get_blood();
	int x156 = a.get_ad();
	int x157 = b->getHujia();
	if (x156 < x157)
	{
		x156 = x157 + 10;
	}
	b->setBlood(x155 - (x156 - x157));
	int diaoxue = (x155 - (x156 - x157)) * 100 / b->getMaxblood();
	b->getHps()->setPercentage(diaoxue);
	CCDelayTime* delayTime = CCDelayTime::create(0.7f);

	if (diaoxue <= 0)
	{
		if (a._max_mp > 10)
		{
			_plane._exp = _plane._exp + b->getExp();
			log("%d", _plane._exp);
			//升级
			if (_plane._exp >= maxexp) {
				level_up();
			}
			//补刀多10金
			_plane._gp = _plane._gp + b->getVal() + 10;
			budaoshu++;
		}
		if (b->getTag() == 2 || b->getTag() == 1002) {
			if (b->getTag() == 2) { I_lose=true; }
			if (b->getTag() == 1002) { I_win=true; }
		}
		b->removeFromParent();

	}
}

Point calculate(float x1, float y1, float x2, float y2, float nXOutOfWorld, float nYOutOfWorld)
{
	float fK = 1.0;

	float fb = 0.0;

	if (x1 != x2)

	{

		fK = (float)(y2 - y1) / (x2 - x1);//求出K

	}

	fb = y2 - x2 * fK;//求出b

	//求该直线在屏幕外的点

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	float fY = y1 > y2 ? -nYOutOfWorld : size.height + nYOutOfWorld;

	float fX = 1.0;

	if (fK != 0)

	{

		fX = (fY - fb) / fK;//这个fX可能非常大，或者非常小

	}

	if (x1 == x2)//应该沿Y轴运动

	{

		fX = x1;

		fY = y1 > y2 ? -nXOutOfWorld : size.height + nYOutOfWorld;

	}

	else if (y2 == y1)//应该沿X轴运动

	{

		fX = x1 > x2 ? -nXOutOfWorld : size.width + nXOutOfWorld;

		fY = y1;

	}

	else if (fX > size.width + nXOutOfWorld)//重新计算fX和fY

	{

		fX = size.width + nXOutOfWorld;

		fY = fK * fX + fb;

	}

	else if (fX < -nXOutOfWorld)//重新计算fX和fY

	{

		fX = -nXOutOfWorld;

		fY = fK * fX + fb;

	}

	return ccp(fX, fY);
}


//创建小兵
void HelloWorld::updatetime(float dt)
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->getChildByTag(TIMER)->removeFromParent();
	time++;


	int minutes = time / 60;
	int seconds = time - minutes * 60;
	_plane._gp += 1;
	_sprite2._gp += 10;
	if (time % 30 == 0)
	{
		auto enemy1 = Soider::createWithSoiderTypes(SoiderType1);
		enemy1->setVelocity(Vec2(50, 0));
		enemy1->setPosition(Vec2(400, 200));
		enemy1->setFlipX(true);
		maplayer->addChild(enemy1, 2, number_soider * 4 + 1);

		auto enemy2 = Soider::createWithSoiderTypes(SoiderType1);
		enemy2->setVelocity(Vec2(50, 0));
		enemy2->setPosition(Vec2(300, 200));
		enemy2->setFlipX(true);
		maplayer->addChild(enemy2, 2, number_soider * 4 + 2);

		auto enemy3 = Soider::createWithSoiderTypes(SoiderType2);
		enemy3->setVelocity(Vec2(50, 0));
		enemy3->setPosition(Vec2(200, 200));
		enemy3->setFlipX(true);
		maplayer->addChild(enemy3, 2, number_soider * 4 + 3);

		auto enemy4 = Soider::createWithSoiderTypes(SoiderType3);
		enemy4->setVelocity(Vec2(50, 0));
		enemy4->setPosition(Vec2(100, 200));
		enemy4->setFlipX(true);
		maplayer->addChild(enemy4, 2, number_soider * 4 + 4);

		auto enemy5 = Soider::createWithSoiderTypes(SoiderType1);
		enemy5->setVelocity(Vec2(-50, 0));
		enemy5->setPosition(Vec2(6200, 200));
		maplayer->addChild(enemy5, 2, number_soider * 4 + 1001);

		auto enemy6 = Soider::createWithSoiderTypes(SoiderType1);
		enemy6->setVelocity(Vec2(-50, 0));
		enemy6->setPosition(Vec2(6300, 200));
		maplayer->addChild(enemy6, 2, number_soider * 4 + 1002);

		auto enemy7 = Soider::createWithSoiderTypes(SoiderType2);
		enemy7->setVelocity(Vec2(-50, 0));
		enemy7->setPosition(Vec2(6400, 200));
		maplayer->addChild(enemy7, 2, number_soider * 4 + 1003);

		auto enemy8 = Soider::createWithSoiderTypes(SoiderType3);
		enemy8->setVelocity(Vec2(-50, 0));
		enemy8->setPosition(Vec2(6500, 200));
		maplayer->addChild(enemy8, 2, number_soider * 4 + 1004);

		number_soider++;

	}

	std::string left = std::to_string(minutes);
	std::string right = std::to_string(seconds);
	if (minutes < 10) {
		left = "0" + left;
	}
	if (seconds < 10) {
		right = "0" + right;
	}
	auto timelabel = Label::createWithTTF(left + ":" + right, "fonts/Marker Felt.ttf", 30);
	timelabel->setPosition(Vec2(origin.x + visibleSize.width - timelabel->getContentSize().width,
		origin.y + visibleSize.height - timelabel->getContentSize().height));
	this->addChild(timelabel, 2, TIMER);

	if(I_lose==true){
		auto label = Label::createWithTTF("YOU LOSE...", "fonts/Marker Felt.ttf", 50);
		label->setPosition(Vec2(origin.x + visibleSize.width/2 ,
			origin.y + visibleSize.height/2 ));
		this->addChild(label, 3);
		MenuItemImage *pLoginItem = MenuItemImage::create(

			"/Button/pause_login.png",

			"/Button/pause_login.png",

			CC_CALLBACK_1(HelloWorld::menuLoginCallback, this)

		);
		pLoginItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 60));

		pLoginItem->setScale(1.3f);

		Menu* pMenu = Menu::create( pLoginItem, NULL);

		pMenu->setPosition(Vec2::ZERO);

		this->addChild(pMenu, 2);
	}
	if (I_win == true) {
		auto label = Label::createWithTTF("YOU WIN!!!", "fonts/Marker Felt.ttf", 50);
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 2));
		this->addChild(label, 3);
		MenuItemImage *pLoginItem = MenuItemImage::create(

			"/Button/pause_login.png",

			"/Button/pause_login.png",

			CC_CALLBACK_1(HelloWorld::menuLoginCallback, this)

		);
		pLoginItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 60));

		pLoginItem->setScale(1.3f);

		Menu* pMenu = Menu::create(pLoginItem, NULL);

		pMenu->setPosition(Vec2::ZERO);

		this->addChild(pMenu, 2);
	}


}
void HelloWorld::menuLoginCallback(cocos2d::Ref* pSender)

{

	auto sc = WelcomeScene::createScene();

	Director::getInstance()->pushScene(sc);

}


//小兵互怼
void Soider::be_attacked(Soider* a, Soider* b) {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	int x151 = b->get_blood();
	int x152 = a->get_ad();
	int x99 = b->getHujia();
	b->setBlood(x151 - (x152 - x99));
	int diaoxue = (x151 - (x152 - x99)) * 100 / b->getMaxblood();
	b->getHps()->setPercentage(diaoxue);
	CCDelayTime* delayTime = CCDelayTime::create(0.7f);

	if (b->blood <= 0)
	{
		_plane._exp += b->getExp();
		//升级
		if (_plane._exp >= maxexp) {
			level_up();
		}
		_plane._gp = _plane._gp + b->getVal();
		b->removeFromParent();
	}



}

//敌方英雄移动购物和攻击AI
void HelloWorld::updateenemyheromove(float dt)//敌方英雄移动和购物
{
	if (_sprite2._gp >= 400 && buytimes == 0)
	{
		_sprite2._max_blood += 200;
		_sprite2._blood += 200;
		_sprite2._gp -= 400;
		_sprite2.me_have[2][0] = true;
		_sprite2.me_this_eqp[2][0]++;
		_sprite2.eqp_num++;
		buytimes++;
	}
	if (_sprite2._gp >= 800 && buytimes == 1)
	{
		_sprite2._max_blood += 300;
		_sprite2._blood += 300;
		_sprite2._gp -= 800;
		_sprite2.me_have[2][0] = false;
		_sprite2.me_have[2][1] = true;
		_sprite2.me_this_eqp[2][0]--;
		_sprite2.me_this_eqp[2][1]++;
		buytimes++;
	}
	if (_sprite2._gp >= 1200 && buytimes == 2)
	{
		_sprite2._max_blood += 700;
		_sprite2._blood += 700;
		_sprite2._gp -= 1200;
		_sprite2.me_have[2][1] = false;
		_sprite2.me_have[2][2] = true;
		_sprite2.me_this_eqp[2][1]--;
		_sprite2.me_this_eqp[2][2]++;
		buytimes++;
	}
	if (_sprite2._gp >= 1600 && buytimes == 3)
	{
		_sprite2._max_blood = _sprite2._max_blood * 2;
		_sprite2._blood = _sprite2._blood * 2;
		_sprite2._gp -= 1600;
		_sprite2.me_have[2][2] = false;
		_sprite2.me_have[2][3] = true;
		_sprite2.me_this_eqp[2][2]--;
		_sprite2.me_this_eqp[2][3]++;
		buytimes++;
	}
	if (_sprite2._gp >= 250 && buytimes == 4)
	{
		_sprite2._speed += 1.5;
		_sprite2._gp -= 250;
		_sprite2.me_have[3][0] = true;
		_sprite2.me_this_eqp[3][0]++;
		_sprite2.eqp_num++;
		have_shoe = true;
		buytimes++;
	}
	if (_sprite2._gp >= 800 && buytimes == 5)
	{
		_sprite2._speed += 2.0;
		_sprite2._gp -= 800;
		_sprite2.me_have[3][0] = false;
		_sprite2.me_have[3][1] = true;
		_sprite2.me_this_eqp[3][0]--;
		_sprite2.me_this_eqp[3][1]++;
		buytimes++;
	}
	if (_sprite2._gp >= 300 && buytimes == 6)
	{
		_sprite2._ad += 10;
		_sprite2._gp -= 300;
		_sprite2.me_have[0][0] = true;
		_sprite2.me_this_eqp[0][0]++;
		_sprite2.eqp_num++;
		buytimes++;
	}
	if (_sprite2._gp >= 700 && buytimes == 7)
	{
		_sprite2._ad += 40;
		_sprite2._gp -= 700;
		_sprite2.me_have[0][0] = false;
		_sprite2.me_have[0][1] = true;
		_sprite2.me_this_eqp[0][0]--;
		_sprite2.me_this_eqp[0][1]++;
		buytimes++;
	}
	if (_sprite2._gp >= 1300 && buytimes == 8)
	{
		_sprite2._ad += 50;
		_sprite2._gp -= 1300;
		_sprite2.me_have[0][1] = false;
		_sprite2.me_have[0][2] = true;
		_sprite2.me_this_eqp[0][1]--;
		_sprite2.me_this_eqp[0][2]++;
		buytimes++;
	}
	if (_sprite2._gp >= 2000 && buytimes == 9)
	{
		_sprite2._ad += 50;
		_sprite2._gp -= 2000;
		_sprite2.me_have[0][2] = false;
		_sprite2.me_have[0][3] = true;
		_sprite2.me_this_eqp[0][2]--;
		_sprite2.me_this_eqp[0][3]++;
		buytimes++;
	}
	if (_sprite2._gp >= 450 && buytimes == 10)
	{
		_sprite2._hujia += 10;
		_sprite2._gp -= 450;
		_sprite2.me_have[1][0] = true;
		_sprite2.me_this_eqp[1][0]++;
		_sprite2.eqp_num++;
		buytimes++;
	}
	if (_sprite2._gp >= 1000 && buytimes == 11)
	{
		_sprite2._hujia += 40;
		_sprite2._gp -= 1000;
		_sprite2.me_have[1][0] = false;
		_sprite2.me_have[1][1] = true;
		_sprite2.me_this_eqp[1][0]--;
		_sprite2.me_this_eqp[1][1]++;
		buytimes++;
	}
	if (_sprite2._gp >= 1500 && buytimes == 12)
	{
		_sprite2._hujia += 50;
		_sprite2._gp -= 1500;
		_sprite2.me_have[1][1] = false;
		_sprite2.me_have[1][2] = true;
		_sprite2.me_this_eqp[1][1]--;
		_sprite2.me_this_eqp[1][2]++;
		buytimes++;
	}
	if (_sprite2._gp >= 2400 && buytimes == 13)
	{
		_sprite2._hujia += 50;
		_sprite2._gp -= 2400;
		_sprite2.me_have[1][2] = false;
		_sprite2.me_have[1][3] = true;
		_sprite2.me_this_eqp[1][2]--;
		_sprite2.me_this_eqp[1][3]++;
		buytimes++;
	}
	if (_sprite2._gp >= 400 && buytimes == 14)
	{
		_sprite2._max_blood += 200;
		_sprite2._blood += 200;
		_sprite2._gp -= 400;
		_sprite2.me_have[2][0] = true;
		_sprite2.me_this_eqp[2][0]++;
		_sprite2.eqp_num++;
		buytimes++;
	}
	if (_sprite2._gp >= 800 && buytimes == 15)
	{
		_sprite2._max_blood += 300;
		_sprite2._blood += 300;
		_sprite2._gp -= 800;
		_sprite2.me_have[2][0] = false;
		_sprite2.me_have[2][1] = true;
		_sprite2.me_this_eqp[2][0]--;
		_sprite2.me_this_eqp[2][1]++;
		buytimes++;
	}
	if (_sprite2._gp >= 1200 && buytimes == 16)
	{
		_sprite2._max_blood += 700;
		_sprite2._blood += 700;
		_sprite2._gp -= 1200;
		_sprite2.me_have[2][1] = false;
		_sprite2.me_have[2][2] = true;
		_sprite2.me_this_eqp[2][1]--;
		_sprite2.me_this_eqp[2][2]++;
		buytimes++;
	}
	if (_sprite2._gp >= 1600 && buytimes == 17)
	{
		_sprite2._max_blood = _sprite2._max_blood * 2;
		_sprite2._blood = _sprite2._blood * 2;
		_sprite2._gp -= 1600;
		_sprite2.me_have[2][2] = false;
		_sprite2.me_have[2][3] = true;
		_sprite2.me_this_eqp[2][2]--;
		_sprite2.me_this_eqp[2][3]++;
		buytimes++;
	}
	if (_sprite2._gp >= 400 && buytimes == 18)
	{
		_sprite2._max_blood += 200;
		_sprite2._blood += 200;
		_sprite2._gp -= 400;
		_sprite2.me_have[2][0] = true;
		_sprite2.me_this_eqp[2][0]++;
		_sprite2.eqp_num++;
		buytimes++;
	}
	if (_sprite2._gp >= 800 && buytimes == 19)
	{
		_sprite2._max_blood += 300;
		_sprite2._blood += 300;
		_sprite2._gp -= 800;
		_sprite2.me_have[2][0] = false;
		_sprite2.me_have[2][1] = true;
		_sprite2.me_this_eqp[2][0]--;
		_sprite2.me_this_eqp[2][1]++;
		buytimes++;
	}
	if (_sprite2._gp >= 1200 && buytimes == 20)
	{
		_sprite2._max_blood += 700;
		_sprite2._blood += 700;
		_sprite2._gp -= 1200;
		_sprite2.me_have[2][1] = false;
		_sprite2.me_have[2][2] = true;
		_sprite2.me_this_eqp[2][1]--;
		_sprite2.me_this_eqp[2][2]++;
		buytimes++;
	}
	if (_sprite2._gp >= 1600 && buytimes == 21)
	{
		_sprite2._max_blood = _sprite2._max_blood * 2;
		_sprite2._blood = _sprite2._blood * 2;
		_sprite2._gp -= 1600;
		_sprite2.me_have[2][2] = false;
		_sprite2.me_have[2][3] = true;
		_sprite2.me_this_eqp[2][2]--;
		_sprite2.me_this_eqp[2][3]++;
		buytimes++;
	}

	if (_sprite2._blood * 100 / _sprite2._max_blood < 30)
	{
		
		MoveBy *moveby = MoveBy::create(0.1f, ccp(_sprite2._speed, 0));
		hero2->runAction(moveby);
	}
	else
	{
		MoveBy *moveby = MoveBy::create(0.1f, ccp(-_sprite2._speed, 0));
		hero2->runAction(moveby);
	}

}
void HelloWorld::updateenemyheroattack(float dt)
{
	for (int j6 = 2; j6 <= number_soider * 4; j6++)
	{
		Soider* friend123 = (Soider*)maplayer->getChildByTag(j6);
		if (friend123 == NULL)
			continue;
		if (ccpDistance(friend123->getPosition(), hero2->getPosition()) <= _sprite2.attackrange&&_sprite2._blood * 100 / _sprite2._max_blood >= 30)
		{
			//不同英雄普攻
			_sprite2._speed = 0;
			auto bullet2 = Sprite::create("CloseSelected.png");
			if (hero_type == 1) {

				bullet2 = Sprite::create("gongjian.png");

			}
			if (hero_type == 2) {
				bullet2 = Sprite::create("fashu.png");

			}
			if (hero_type == 3) {
				bullet2->setVisible(false);

			}

			maplayer->addChild(bullet2, 1);
			bullet2->setPosition(hero2->getPosition());

			CCPoint attck_point = Vec2(friend123->getPosition().x, friend123->getPosition().y);
			auto actionMove1 = CCMoveTo::create(flytime, attck_point);
			auto actionMovehide1 = CCHide::create();

			Sequence* sequence1 = Sequence::create(actionMove1, actionMovehide1, NULL);
			bullet2->runAction(sequence1);
			be_attacked2(_sprite2, friend123);
			hero2->AttackAnimation(att_name1, att_num1, hero2->HeroDirecton);
			break;
		}
		else
			_sprite2._speed = 3;
	}
}
void HelloWorld::updateenemyheroattackhero(float dt)
{
	if (ccpDistance(hero1->getPosition(), hero2->getPosition()) <= _sprite2.attackrange&&_sprite2._blood * 100 / _sprite2._max_blood >= 30)
	{
		//不同英雄普攻
		_sprite2._speed = 0;
		auto bullet2 = Sprite::create("CloseSelected.png");
		if (hero_type == 1) {

			bullet2 = Sprite::create("gongjian.png");
		}
		if (hero_type == 2) {
			bullet2 = Sprite::create("fashu.png");

		}
		if (hero_type == 3) {
			bullet2->setVisible(false);

		}

		maplayer->addChild(bullet2, 1);
		bullet2->setPosition(hero2->getPosition());

		CCPoint attck_point = Vec2(hero1->getPosition().x, hero1->getPosition().y);
		auto actionMove1 = CCMoveTo::create(flytime, attck_point);
		auto actionMovehide1 = CCHide::create();

		Sequence* sequence1 = Sequence::create(actionMove1, actionMovehide1, NULL);
		bullet2->runAction(sequence1);
	/*	be_attacked2(_sprite2, _plane);*/
		hero2->AttackAnimation(att_name1, att_num1, hero2->HeroDirecton);
		int blood14 = _plane.be_attacked_by_me(_sprite2, _plane);
		m_pBloodView->setCurrentBlood(blood14);
		if (blood14 <= 0)
		{
			hero1->setVisible(false);
			//重生
			time_again = 6;
			if (time_again == 6) {

				hero1->setPosition(Vec2(228, 230));
				hero1->setScale(1);
				hero1->setVisible(true);
				time_again == 1;
				blood14 = _sprite2.get_maxblood();
				_plane._blood = blood14;
				m_pBloodView->setCurrentBlood(100.0f);
				dead++;
			}
		}

		
		
	}
	else
		_sprite2._speed = 3;
}
void HelloWorld::updatefriend(float dt)//实现友方AI
{
	for (int i1 = 5; i1 <= number_soider * 4; i1++)
	{
		Soider* friendsoider = (Soider*)maplayer->getChildByTag(i1);
		if (friendsoider == NULL)
			continue;
		for (int j1 = 1002; j1 <= number_soider * 4 + 1000; j1++)
		{
			Soider* enemysoider = (Soider*)maplayer->getChildByTag(j1);
			if (enemysoider == NULL)
				continue;
			if (i1 % 3)
				attack_distance = 100;
			else
				attack_distance = 300;
			if (ccpDistance(friendsoider->getPosition(), enemysoider->getPosition()) <= attack_distance)
			{


				friendsoider->setVelocity(Vec2(0, 0));
				auto bullet2 = Sprite::create("CloseSelected.png");
				maplayer->addChild(bullet2, 1);
				bullet2->setPosition(friendsoider->getPosition());
				CCPoint attck_point = Vec2(enemysoider->getPosition().x, enemysoider->getPosition().y);
				auto actionMove1 = CCMoveTo::create(flytime, attck_point);
				auto actionMovehide1 = CCHide::create();

				Sequence* sequence1 = Sequence::create(actionMove1, actionMovehide1, NULL);
				bullet2->runAction(sequence1);
				//小兵掉血
				friendsoider->be_attacked(friendsoider, enemysoider);
				break;
			}
			else
			{
				friendsoider->setVelocity(Vec2(50, 0));
			}
		}
	}
}

//实现敌军AI
void HelloWorld::updateenemy(float dt)
{
	for (int i2 = 1005; i2 <= number_soider * 4 + 1000; i2++)
	{
		Soider* enemysoider1 = (Soider*)maplayer->getChildByTag(i2);
		if (enemysoider1 == NULL)
			continue;
		for (int j2 = 2; j2 <= number_soider * 4; j2++)
		{
			Soider* friendsoider1 = (Soider*)maplayer->getChildByTag(j2);
			if (friendsoider1 == NULL)
				continue;
			if ((i2 - 1000) % 3)
				attack_distance = 100;
			else
				attack_distance = 300;
			if (ccpDistance(enemysoider1->getPosition(), friendsoider1->getPosition()) <= attack_distance)
			{
				enemysoider1->setVelocity(Vec2(0, 0));
				auto bullet3 = Sprite::create("CloseSelected.png");
				maplayer->addChild(bullet3, 1);
				bullet3->setPosition(enemysoider1->getPosition());
				CCPoint attck_point = Vec2(friendsoider1->getPosition().x, friendsoider1->getPosition().y);
				auto actionMove2 = CCMoveTo::create(flytime, attck_point);
				auto actionMovehide2 = CCHide::create();

				Sequence* sequence2 = Sequence::create(actionMove2, actionMovehide2, NULL);
				bullet3->runAction(sequence2);

				enemysoider1->be_attacked(enemysoider1, friendsoider1);

				break;
			}
			else
			{
				enemysoider1->setVelocity(Vec2(-50, 0));
			}
		}
	}
}

void HelloWorld::updatequanshui(float dt)
{
	Hero* friendhero = (Hero*)maplayer->getChildByTag(1);
	Hero* enemyhero = (Hero*)maplayer->getChildByTag(1001);
	if (friendhero->getPositionX() < 200)
	{
		_plane._blood = _plane._max_blood;
		m_pBloodView->setCurrentBlood(100.0f);
	}
	if (enemyhero->getPositionX() > 6100)
	{
		_sprite2._blood = _sprite2._max_blood;
		m_pBloodView1->setCurrentBlood(100.0f);
	}
}

void Tower::be_attacked1(Tower* a, Soider* b) {


	int x153 = b->get_blood();
	int x154 = a->get_ad1();
	int x100 = b->getHujia();
	b->setBlood(x153 - (x154 - x100));

	int diaoxue = (x153 - (x154 - x100)) * 100 / b->getMaxblood();
	b->getHps()->setPercentage(diaoxue);
	if (diaoxue <= 0)
	{
		_plane._exp += b->getExp();
		//升级
		if (_plane._exp >= maxexp) {
			level_up();
		}
		_plane._gp = _plane._gp + b->getVal();

		b->removeFromParent();
	}


}




//友军防御塔AI
void HelloWorld::updatefriendtower(float dt)
{
	for (int i3 = 2; i3 <= 4; i3++)
	{
		Tower* friendtower1 = (Tower*)maplayer->getChildByTag(i3);
		if (friendtower1 == NULL)
			continue;
		for (int j3 = 1002; j3 <= number_soider * 4 + 1000; j3++)
		{
			Soider* enemytower1 = (Soider*)maplayer->getChildByTag(j3);
			if (enemytower1 == NULL)
				continue;
			if (ccpDistance(friendtower1->getPosition(), enemytower1->getPosition()) <= 600)
			{
				auto bullet2 = Sprite::create("CloseSelected.png");
				maplayer->addChild(bullet2, 1);
				bullet2->setPosition(friendtower1->getPosition());
				CCPoint attck_point = Vec2(enemytower1->getPosition().x, enemytower1->getPosition().y);
				auto actionMove1 = CCMoveTo::create(flytime, attck_point);
				auto actionMovehide1 = CCHide::create();

				Sequence* sequence1 = Sequence::create(actionMove1, actionMovehide1, NULL);
				bullet2->runAction(sequence1);
				friendtower1->be_attacked1(friendtower1, enemytower1);
				break;
			}
		}
	}
}


//敌方防御塔攻击我方英雄
void HelloWorld::updateattacked(float dt)
{
	Hero* myhero = (Hero*)maplayer->getChildByTag(1);
	for (int j0 = 1003; j0 <= 1004; j0++)
	{
		Tower* enemysoider1 = (Tower*)maplayer->getChildByTag(j0);
		if (enemysoider1 == NULL)
			continue;
		if (ccpDistance(enemysoider1->getPosition(), myhero->getPosition()) <= enemysoider1->getAttack_distance())
		{
			enemysoider1->setVelocity(Vec2(0, 0));
			auto bullet3 = Sprite::create("CloseSelected.png");
			maplayer->addChild(bullet3, 1);
			bullet3->setPosition(enemysoider1->getPosition());
			CCPoint attck_point = Vec2(myhero->getPosition().x, myhero->getPosition().y);
			auto actionMove2 = CCMoveTo::create(flytime, attck_point);
			auto actionMovehide2 = CCHide::create();

			Sequence* sequence2 = Sequence::create(actionMove2, actionMovehide2, NULL);
			bullet3->runAction(sequence2);
			int blood12 = _plane.be_attacked_by_tower(_plane, enemysoider1);
			m_pBloodView->setCurrentBlood(blood12);

			if (blood12 <= 0) {
				hero1->setVisible(false);

				//重生
				time_again = 6;
				if (time_again == 6) {

					hero1->setPosition(Vec2(228, 230));
					hero1->setScale(1);
					hero1->setVisible(true);
					time_again == 1;
					blood12 = _plane.get_maxblood();
					_plane._blood = blood12;
					m_pBloodView->setCurrentBlood(100.0f);
					dead++;
				}
			}
			continue;
		}
		else
		{
			enemysoider1->setVelocity(Vec2(-50, 0));
		}
	}
}
//我方防御塔攻击敌方英雄
void HelloWorld::updateattackedenemy(float dt)
{
	Hero* enemyhero = (Hero*)maplayer->getChildByTag(1001);
	for (int j7 = 3; j7 <= 4; j7++)
	{
		Tower* friendsoider1 = (Tower*)maplayer->getChildByTag(j7);
		if (friendsoider1 == NULL)
			continue;
		if (ccpDistance(friendsoider1->getPosition(), enemyhero->getPosition()) <= friendsoider1->getAttack_distance())
		{
			friendsoider1->setVelocity(Vec2(0, 0));
			auto bullet3 = Sprite::create("CloseSelected.png");
			maplayer->addChild(bullet3, 1);
			bullet3->setPosition(friendsoider1->getPosition());
			CCPoint attck_point = Vec2(enemyhero->getPosition().x, enemyhero->getPosition().y);
			auto actionMove2 = CCMoveTo::create(flytime, attck_point);
			auto actionMovehide2 = CCHide::create();

			Sequence* sequence2 = Sequence::create(actionMove2, actionMovehide2, NULL);
			bullet3->runAction(sequence2);
			int blood12 = _sprite2.be_attacked_by_tower(_sprite2, friendsoider1);
			m_pBloodView1->setCurrentBlood(blood12);

			if (blood12 <= 0) {
				hero2->setVisible(false);

				//重生
				time_again = 6;
				if (time_again == 6) {

					hero2->setPosition(Vec2(6100, 230));
					hero2->setScale(1);
					hero2->setVisible(true);
					time_again == 1;
					_sprite2._blood = _sprite2.get_maxblood();
					m_pBloodView1->setCurrentBlood(100.0f);
					kill++;
				}
			}
			continue;
		}
	}
}
//敌方小兵攻击我方英雄
void HelloWorld::updateattacked1(float dt)//实现AI
{
	Hero* myhero = (Hero*)maplayer->getChildByTag(1);
	for (int j0 = 1005; j0 <= number_soider * 4 + 1000; j0++)
	{
		Soider* enemysoider1 = (Soider*)maplayer->getChildByTag(j0);
		if (enemysoider1 == NULL)
			continue;
		if (ccpDistance(enemysoider1->getPosition(), myhero->getPosition()) <= enemysoider1->getAttack_distance())
		{
			enemysoider1->setVelocity(Vec2(0, 0));
			auto bullet3 = Sprite::create("CloseSelected.png");
			maplayer->addChild(bullet3, 1);
			bullet3->setPosition(enemysoider1->getPosition());
			CCPoint attck_point = Vec2(myhero->getPosition().x, myhero->getPosition().y);
			auto actionMove2 = CCMoveTo::create(flytime, attck_point);
			auto actionMovehide2 = CCHide::create();

			Sequence* sequence2 = Sequence::create(actionMove2, actionMovehide2, NULL);
			bullet3->runAction(sequence2);
			int blood11 = _plane.be_attacked_by_soider(_plane, enemysoider1);
			m_pBloodView->setCurrentBlood(blood11);
			if (blood11 <= 0)
			{
				hero1->setVisible(false);
				//重生
				time_again = 6;
				if (time_again == 6) {

					hero1->setPosition(Vec2(228, 230));
					hero1->setScale(1);
					hero1->setVisible(true);
					time_again == 1;
					blood11 = _plane.get_maxblood();
					_plane._blood = blood11;
					m_pBloodView->setCurrentBlood(100.0f);
					dead++;
				}
			}
			continue;
		}
		else
		{
			enemysoider1->setVelocity(Vec2(-50, 0));
		}
	}
}
//我方小兵攻击敌方英雄
void HelloWorld::updateattacked1enemy(float dt)//实现小兵攻击敌方英雄
{
	Hero* myhero = (Hero*)maplayer->getChildByTag(1001);
	for (int j8 = 5; j8 <= number_soider * 4; j8++)
	{
		Soider* friendsoider1 = (Soider*)maplayer->getChildByTag(j8);
		if (friendsoider1 == NULL)
			continue;
		if (ccpDistance(friendsoider1->getPosition(), myhero->getPosition()) <= friendsoider1->getAttack_distance())
		{
			friendsoider1->setVelocity(Vec2(0, 0));
			auto bullet3 = Sprite::create("CloseSelected.png");
			maplayer->addChild(bullet3, 1);
			bullet3->setPosition(friendsoider1->getPosition());
			CCPoint attck_point = Vec2(myhero->getPosition().x, myhero->getPosition().y);
			auto actionMove2 = CCMoveTo::create(flytime, attck_point);
			auto actionMovehide2 = CCHide::create();

			Sequence* sequence2 = Sequence::create(actionMove2, actionMovehide2, NULL);
			bullet3->runAction(sequence2);
			int blood11 = _sprite2.be_attacked_by_soider(_sprite2, friendsoider1);
			m_pBloodView1->setCurrentBlood(blood11);
			if (blood11 <= 0)
			{
				hero2->setVisible(false);
				//重生
				time_again = 6;
				if (time_again == 6) {

					hero2->setPosition(Vec2(6100, 230));
					hero2->setScale(1);
					hero2->setVisible(true);
					time_again == 1;
					_sprite2._blood = _sprite2.get_maxblood();
					m_pBloodView1->setCurrentBlood(100.0f);
					kill++;

				}
			}
			continue;
		}
		else
		{
			friendsoider1->setVelocity(Vec2(50, 0));
		}
	}
}

//敌军防御塔AI
void HelloWorld::updateenemytower(float dt)
{
	for (int i4 = 1003; i4 <= 1004; i4++)
	{
		Tower* enemytower2 = (Tower*)maplayer->getChildByTag(i4);
		if (enemytower2 == NULL)
			continue;
		for (int j4 = 2; j4 <= number_soider * 4; j4++)
		{
			Soider* friendtower2 = (Soider*)maplayer->getChildByTag(j4);
			if (friendtower2 == NULL)
				continue;
			if (ccpDistance(enemytower2->getPosition(), friendtower2->getPosition()) <= 600)
			{
				auto bullet2 = Sprite::create("CloseSelected.png");
				maplayer->addChild(bullet2, 1);
				bullet2->setPosition(enemytower2->getPosition());
				CCPoint attck_point = Vec2(friendtower2->getPosition().x, friendtower2->getPosition().y);
				auto actionMove1 = CCMoveTo::create(flytime, attck_point);
				auto actionMovehide1 = CCHide::create();

				Sequence* sequence1 = Sequence::create(actionMove1, actionMovehide1, NULL);
				bullet2->runAction(sequence1);

				enemytower2->be_attacked1(enemytower2, friendtower2);
				break;
			}
		}
	}
}

void hero::be_attacked_by(hero other) {

	_blood = _blood - (other.get_ad() - _hujia);
}


void hero::exp_up(hero me, Soider *other)

{
	me._exp = me._exp + other->getExp();
}


int hero::be_attacked_by_soider(hero a, Soider* b) {



	int x1066 = b->getAd();
	int x1067 = a.get_hujia();
	if ((x1066 - x1067) <= 0)
	{
		int bloodnow = (_blood / a.get_maxblood()) * 100;
		return bloodnow;
	}
	_blood = _blood - (x1066 - x1067);

	int bloodnow = (_blood / a.get_maxblood()) * 100;

	return bloodnow;

}

int hero::be_attacked_by_tower(hero a, Tower* b) {



	int x1166 = b->getAd();
	int x1167 = a.get_hujia();
	if ((x1166 - x1167) <= 0) {
		int bloodnow1 = (a.get_blood() / a.get_maxblood()) * 100;
		return bloodnow1;
	}
	_blood = _blood - (x1166 - x1167);
	int bloodnow1 = (a.get_blood() / a.get_maxblood()) * 100;
	//自己掉血

	return  bloodnow1;
}



int hero::be_attacked_by_me(hero a, hero b) {


	int x155 = b.get_blood();
	int x156 = a.get_ad();
	int x157 = b.get_hujia();
	if ((x156 - 157) <= 0)
	{
		int bloodnow2 = (_blood / b.get_maxblood()) * 100;
		return bloodnow2;
	}
	_blood = _blood - (x156 - x157);
	int bloodnow2 = (b.get_blood() / b.get_maxblood()) * 100;

	if (bloodnow2<= 0)
	{
		_plane._exp = _plane._exp + b.get_exp();
		log("%d", _plane._exp);
		//升级
		if (_plane._exp >= maxexp) {
			level_up();
		}
		//杀人300金
		_plane._gp = _plane._gp + 300;
		kill++;
	}
	return bloodnow2;

}


void be_attacked3(hero a, Soider* b) {


	int x165 = b->get_blood();
	b->setBlood(x165 *0.85);
	int diaoxue = (x165*0.85) * 100 / b->getMaxblood();
	b->getHps()->setPercentage(diaoxue);
	CCDelayTime* delayTime = CCDelayTime::create(0.7f);

	if (diaoxue <= 0)
	{
		_plane._exp = _plane._exp + b->getExp();
		//升级
		if (_plane._exp >= maxexp) {
			level_up();
		}
		//补刀多10金
		_plane._gp = _plane._gp + b->getVal() + 10;
		budaoshu++;
		b->removeFromParent();

	}
}
int be_attacked3hero(hero a, hero b) {


	int x165 = b.get_blood();
	_sprite2._blood=(x165*0.85);

	int bloodnow3 = (b.get_blood() / b.get_maxblood()) * 100;
	if (bloodnow3 <= 0)
	{
		_plane._exp = _plane._exp + b.get_exp();
		//升级
		if (_plane._exp >= maxexp) {
			level_up();
		}
		//补刀多10金
		_plane._gp = _plane._gp + 300;
		kill++;
	}
	return bloodnow3;
}



void be_attacked_4(hero a, Soider* b) {


	int x165 = b->get_blood();
	b->setBlood(x165 *0.25);
	int diaoxue = (x165*0.25) * 100 / b->getMaxblood();
	b->getHps()->setPercentage(diaoxue);
	CCDelayTime* delayTime = CCDelayTime::create(0.7f);

	if (diaoxue <= 0)
	{
		_plane._exp = _plane._exp + b->getExp();
		//升级
		if (_plane._exp >= maxexp) {
			level_up();
		}
		//补刀多10金
		_plane._gp = _plane._gp + b->getVal() + 10;
		budaoshu++;
		b->removeFromParent();

	}
}

void be_attacked4(hero a, Soider* b) {


	int x165 = b->get_blood();
	if ((x165 / b->getMaxblood()) * 100 <= 40) {
		int diaoxue = 0;
		b->getHps()->setPercentage(diaoxue);
		if (diaoxue <= 0)
		{
			_plane._exp = _plane._exp + b->getExp();

			//升级
			if (_plane._exp >= maxexp) {
				level_up();
			}
			//补刀多10金
			_plane._gp = _plane._gp + b->getVal() + 10;
			budaoshu++;
			b->removeFromParent();
		}


	}
	else return;
}
void be_attacked_skill7(hero a, Soider *b)
{
	int x165 = b->get_blood();
	int x166 = a.get_ad();
	int x167 = b->getMaxblood();
	b->setBlood(x165 - x166);
	int diaoxue = (x165 - x166) * 100 / b->getMaxblood();
	log("%d", diaoxue);
	b->getHps()->setPercentage(diaoxue);
	if (diaoxue <= 0)
	{
		_plane._exp = _plane._exp + b->getExp();
		//升级
		if (_plane._exp >= maxexp) {
			level_up();
		}
		//补刀多10金
		_plane._gp = _plane._gp + b->getVal() + 10;
		budaoshu++;
		b->removeFromParent();
	}
}

void be_attacked_skill9(hero a, Soider* b) {



	int x165 = b->get_blood();
	int x166 = a.get_ad();
	int x167 = b->getMaxblood();
	b->setBlood(x165 - x166);
	int diaoxue = (x165 - x166*3) * 100 / b->getMaxblood();
	log("%d", diaoxue);
	b->getHps()->setPercentage(diaoxue);
	if (diaoxue <= 0)
	{
		_plane._exp = _plane._exp + b->getExp();
		//升级
		if (_plane._exp >= maxexp) {
			level_up();
		}
		//补刀多10金
		_plane._gp = _plane._gp + b->getVal() + 10;
		budaoshu++;
		b->removeFromParent();
	}





}





//攻速的实现
void HelloWorld::gongsu1(float dt)
{
	gongsu = 1;
}





bool HelloWorld::touchBegan(Touch *touch, Event* event)
{

	x_touch = touch->getLocation().x + countx * 2;
	y_touch = touch->getLocation().y;
	Vec2 touchposition = Vec2(x_touch, y_touch);
	int timebefore = 0;
	int timenow = 0;
	timenow = time;
	for (int j5 = 1002; j5 <= number_soider * 4 + 1000; j5++)
	{
		Soider* enemy123 = (Soider*)maplayer->getChildByTag(j5);
		if (enemy123 == NULL)
			continue;
		if (ccpDistance(enemy123->getPosition(), hero1->getPosition()) <= _plane.attackrange && (timenow - timebefore) >= 1)
		{
			timebefore = timenow;

			//不同英雄普攻

			auto bullet2 = Sprite::create("CloseSelected.png");
			if (hero_type == 1) {

				bullet2->setVisible(false);
			}
			if (hero_type == 2) {

				bullet2 = Sprite::create("gongjian.png");
			}
			if (hero_type == 3) {

				bullet2 = Sprite::create("fashu.png");
				bullet2->setScale(0.5f);
			}

			maplayer->addChild(bullet2, 1);
			bullet2->setPosition(hero1->getPosition());

			CCPoint attck_point = Vec2(enemy123->getPosition().x, enemy123->getPosition().y);
			auto actionMove1 = CCMoveTo::create(flytime, attck_point);
			auto actionMovehide1 = CCHide::create();

			Sequence* sequence1 = Sequence::create(actionMove1, actionMovehide1, NULL);
			bullet2->runAction(sequence1);
			be_attacked2(_plane, enemy123);
			hero1->AttackAnimation(att_name, att_num, hero1->HeroDirecton);
			break;
		}
	}
	if (ccpDistance(hero1->getPosition(), hero2->getPosition()) <= _plane.attackrange) {
		Hero* enemyhero = (Hero*)maplayer->getChildByTag(1001);
		auto bullet2 = Sprite::create("CloseSelected.png");
		if (hero_type == 1) {

			bullet2->setVisible(false);
		}
		if (hero_type == 2) {

			bullet2 = Sprite::create("gongjian.png");
		}
		if (hero_type == 3) {

			bullet2 = Sprite::create("fashu.png");
			bullet2->setScale(0.5f);
		}

		maplayer->addChild(bullet2, 1);
		bullet2->setPosition(hero1->getPosition());

		CCPoint attck_point = Vec2(enemyhero->getPosition().x, enemyhero->getPosition().y);
		auto actionMove1 = CCMoveTo::create(flytime, attck_point);
		auto actionMovehide1 = CCHide::create();

		Sequence* sequence2 = Sequence::create(actionMove1, actionMovehide1, NULL);
		bullet2->runAction(sequence2);

		hero1->AttackAnimation(att_name, att_num, hero1->HeroDirecton);
		int blood13 = _sprite2.be_attacked_by_me(_plane, _sprite2);
		m_pBloodView1->setCurrentBlood(blood13);
		if (blood13 <= 0)
		{
			hero2->setVisible(false);
			//重生
			time_again = 6;
			if (time_again == 6) {

				hero2->setPosition(Vec2(6300, 230));
				hero2->setScale(1);
				hero2->setVisible(true);
				time_again == 1;
				blood13 = _sprite2.get_maxblood();
				_sprite2._blood = blood13;
				m_pBloodView1->setCurrentBlood(100.0f);
				kill++;
			}
		}
		
	}

	return true;

};




/*void HelloWorld::touchMoved(Touch *touch, Event* event)
{
	x_touch = touch->getLocation().x + countx * 2;
	y_touch = touch->getLocation().y;


	auto allbullet = CCArray::create();

	//enemy
	auto enemy = Sprite::create("CloseSelected.png");
	Size winSize = Director::getInstance()->getVisibleSize();
	int enemymovetick = 0;

	if (enemy == nullptr)

	{

		problemLoading("'CloseSelected.png'");

	}

	else

	{

		enemy->setPosition(Point(80, 32));
		enemy->setAnchorPoint(Point(0.5f, 0));
		this->addChild(enemy, 0);
	}

	auto bullet = Sprite::create("CloseNormal.png");

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	maplayer->addChild(bullet);

	bullet->setPosition(ccp(sprite1_position_x, sprite1_position_y));//设置子弹的发射位置

	const int OUT_OF_WORLD = 6000;


	CCPoint ptOutOfWorld = calculate(sprite1_position_x, sprite1_position_y, x_touch, y_touch, OUT_OF_WORLD, OUT_OF_WORLD);//获取屏幕外的一个点


	CCAction*pAction = CCMoveTo::create(2.0f, ptOutOfWorld);

	bullet->runAction(pAction);//发射子弹


	if (isCircleCollision(bullet->getPosition(), bullet->getContentSize().width / 2, enemy->getPosition(), enemy->getContentSize().width / 2))
	{


	}

	else



};*/


void HelloWorld::touchEnded(Touch *touch, Event* event)
{

	hero1->AttackEnd();
};


bool HelloWorld::isKeyPressed(EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}



void HelloWorld::update(float delta) {
	// Register an update function that checks to see if the CTRL key is pressed
	// and if it is displays how long, otherwise tell the user to press it
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Node::update(delta);
	auto W_key = cocos2d::EventKeyboard::KeyCode::KEY_W;
	auto A_key = cocos2d::EventKeyboard::KeyCode::KEY_A;
	auto S_key = cocos2d::EventKeyboard::KeyCode::KEY_S;
	auto D_key = cocos2d::EventKeyboard::KeyCode::KEY_D;
	if (isKeyPressed(W_key)) {
		MoveBy *moveby = MoveBy::create(0.1f, ccp(0, _plane._speed));

		ActionInterval *SineOUt = EaseSineInOut::create(moveby);

		hero1->runAction(moveby);

		sprite1_position_x = hero1->getPositionX();
		sprite1_position_y = hero1->getPositionY() + _plane._speed;
		Vec2 sprite1_position = hero1->getPosition();
		Vec2 move = scenemove(hero1, _tileMap, sprite1_position);
		maplayer->setPosition(move);

	}

	if (isKeyPressed(A_key)) {
		MoveBy *moveby = MoveBy::create(0.1f, ccp(-_plane._speed, 0));

		ActionInterval *SineOUt = EaseSineInOut::create(moveby);

		hero1->runAction(moveby);

		sprite1_position_x = hero1->getPositionX() - _plane._speed;
		sprite1_position_y = hero1->getPositionY();
		Vec2 sprite1_position = hero1->getPosition();
		Vec2 move = scenemove(hero1, _tileMap, sprite1_position);
		maplayer->setPosition(move);

	}

	if (isKeyPressed(S_key)) {
		MoveBy *moveby = MoveBy::create(0.1f, ccp(0, -_plane._speed));

		ActionInterval *SineOUt = EaseSineInOut::create(moveby);

		hero1->runAction(moveby);

		sprite1_position_x = hero1->getPositionX();
		sprite1_position_y = hero1->getPositionY() - _plane._speed;
		Vec2 sprite1_position = hero1->getPosition();
		Vec2 move = scenemove(hero1, _tileMap, sprite1_position);
		maplayer->setPosition(move);


	}

	if (isKeyPressed(D_key)) {
		MoveBy *moveby = MoveBy::create(0.1f, ccp(_plane._speed, 0));

		ActionInterval *SineOUt = EaseSineInOut::create(moveby);

		hero1->runAction(moveby);
		sprite1_position_x = hero1->getPositionX() + _plane._speed;
		sprite1_position_y = hero1->getPositionY();
		Vec2 sprite1_position = hero1->getPosition();
		Vec2 move = scenemove(hero1, _tileMap, sprite1_position);
		maplayer->setPosition(move);


	}
}
/*void HelloWorld::myupdate(float dt)
{
	auto J_key = cocos2d::EventKeyboard::KeyCode::KEY_J;
	if (isKeyPressed(J_key))
	{
		for (int j5 = 1001;j5 <= number_soider * 3 + 1000;j5++)
		{
			Soider* enemy123 = (Soider*)this->getChildByTag(j5);
			if (enemy123 == NULL)
				continue;
			if (ccpDistance(enemy123->getPosition(), plane->getPosition()) <= 400)
			{
				auto bullet2 = Sprite::create("CloseSelected.png");
				this->addChild(bullet2, 1);
				bullet2->setPosition(plane->getPosition());
				CCPoint attck_point = Vec2(enemy123->getPosition().x, enemy123->getPosition().y);
				auto actionMove1 = CCMoveTo::create(flytime, attck_point);
				auto actionMovehide1 = CCHide::create();

				Sequence* sequence1 = Sequence::create(actionMove1, actionMovehide1, NULL);
				bullet2->runAction(sequence1);
				break;
			}
		}
		//log("update");
	}
}*/

bool ifyes(Vec2 a, Vec2 b)
{
	if (a.y - b.y <= 20 && a.y - b.y >= -20) return true;
	return false;
}



//技能
void HelloWorld::skill_1_cd(float dt)
{
	hero1_cd1 = 1;
}
void HelloWorld::skill_2_cd(float dt)
{
	hero1_cd2 = 1;
}
void HelloWorld::skill_2_over(float dt) {
	hero1->removeChildByTag(2000);
	_plane._hujia -= 50;
}
void HelloWorld::skill_3_cd(float dt)
{
	hero1_cd3 = 1;
	hero1->removeChildByTag(1999);
}
void HelloWorld::skill_4_cd(float dt)
{
	hero2_cd1 = 1;
}
void HelloWorld::skill_5_cd(float dt)
{
	hero2_cd2 = 1;
	

}
void HelloWorld::skill_5_over(float dt) {
	hero1->removeChildByTag(2001);
	_plane._ad -= 50;
}
void HelloWorld::skill_6_cd(float dt)
{
	hero2_cd3 = 1;
}
void HelloWorld::skill_7_cd(float dt)
{
	hero3_cd1 = 1;
}
void HelloWorld::skill_7_over(float dt)
{
	hero1->removeChildByTag(2003);
	hero1->removeChildByTag(2004);
}
void HelloWorld::skill_8_cd(float dt)
{
	hero3_cd2 = 1;

}
void HelloWorld::skill_8_over(float dt) {
	hero1->removeChildByTag(2005);
	_plane._speed -= 5;
}
void HelloWorld::skill_9_cd(float dt)
{
	hero3_cd3 = 1;
}



bool ifyes7(Vec2 a, Vec2 b)
{
	if (a.x - b.x <= 200 && a.x - b.x >= -200 && a.y - b.y <= 20 && a.y - b.y >= -20) return true;
	return false;
}



//技能实现
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (heroname == "warrior") {
		switch (keyCode)
		{

		case cocos2d::EventKeyboard::KeyCode::KEY_1:
		{
			if (hero1_cd1 == 0) return;
			for (int j5 = 1005; j5 <= number_soider * 4 + 1005; j5++)
			{
				Soider* enemy123 = (Soider*)maplayer->getChildByTag(j5);
				if (enemy123 == NULL)
					continue;
				hero1->skill_1(hero1, maplayer);
				hero1_cd1 = 0;
				scheduleOnce(schedule_selector(HelloWorld::skill_1_cd), 2.0f);
				if (ifyes(hero1->getPosition(), enemy123->getPosition())) {
					be_attacked3(_plane, enemy123);
				}
			}


			if (ifyes(hero1->getPosition(), hero2->getPosition())) {
			int blood17=be_attacked3hero(_plane, _sprite2);
			m_pBloodView1->setCurrentBlood(blood17);
			if (blood17 <= 0)
			{
				hero2->setVisible(false);
				//重生
				time_again = 6;
				if (time_again == 6) {

				hero2->setPosition(Vec2(6300, 230));
				hero2->setScale(1);
				hero2->setVisible(true);
			    time_again == 1;
				blood17 = _sprite2.get_maxblood();
				_sprite2._blood = blood17;
				m_pBloodView1->setCurrentBlood(100.0f);
				kill++;
				}
		    }
			}


			BeginSkill(0, 2);
			break;
		}
		case cocos2d::EventKeyboard::KeyCode::KEY_2:
		{
			if (hero1_cd2 == 0) return;
			BeginSkill(1, 3);
			hero1->skill_2(hero1, maplayer);
			hero1_cd2 = 0;
			_plane._hujia += 50;
			scheduleOnce(schedule_selector(HelloWorld::skill_2_cd), 3.0f);
			scheduleOnce(schedule_selector(HelloWorld::skill_2_over), 2.0f);
			break;
		}
		case cocos2d::EventKeyboard::KeyCode::KEY_3:
		{
			if (hero1_cd3 == 0) return;
			BeginSkill(2, 5);
			hero1->skill_3(hero1, maplayer);
			hero1_cd3 = 0;
			scheduleOnce(schedule_selector(HelloWorld::skill_3_cd), 2.0f);
			for (int j5 = 1005; j5 <= number_soider * 4 + 1005; j5++)
			{
				Soider* enemy123 = (Soider*)maplayer->getChildByTag(j5);
				if (enemy123 == NULL)
					continue;
				if (ccpDistance(enemy123->getPosition(), hero1->getPosition()) <= _plane.attackrange) {
					be_attacked4(_plane, enemy123);
					break;
				}
			}
			break;
		}
		//回城
		case cocos2d::EventKeyboard::KeyCode::KEY_B:
		{
			hero1->setPosition(Vec2(228, 230));
			hero1->setScale(1);
			hero1->setVisible(true);
			int blood11 = _plane.get_maxblood();
			_plane._blood = blood11;
			m_pBloodView->setCurrentBlood(100.0f);
			break;
		}


		default:
			break;
		}
	}
	if (heroname == "shooter") {
		switch (keyCode)
		{

		case cocos2d::EventKeyboard::KeyCode::KEY_1:
		{
			if (hero2_cd1 == 0) return;
			for (int j5 = 1005; j5 <= number_soider * 4 + 1005; j5++)
			{
				Soider* enemy123 = (Soider*)maplayer->getChildByTag(j5);
				if (enemy123 == NULL)
					continue;
				hero1->skill_4(hero1, maplayer);
				hero2_cd1 = 0;
				scheduleOnce(schedule_selector(HelloWorld::skill_4_cd), 2.0f);
				if (ifyes(hero1->getPosition(), enemy123->getPosition())) {
					be_attacked3(_plane, enemy123);
				}
			}


			if (ifyes(hero1->getPosition(), hero2->getPosition())) {
				int blood17 = be_attacked3hero(_plane, _sprite2);
				m_pBloodView1->setCurrentBlood(blood17);
				if (blood17 <= 0)
				{
					hero2->setVisible(false);
					//重生
					time_again = 6;
					if (time_again == 6) {

						hero2->setPosition(Vec2(6300, 230));
						hero2->setScale(1);
						hero2->setVisible(true);
						time_again == 1;
						blood17 = _sprite2.get_maxblood();
						_sprite2._blood = blood17;
						m_pBloodView1->setCurrentBlood(100.0f);
						kill++;
					}
				}
			}


			BeginSkill(0, 2);
			break;
		}
		case cocos2d::EventKeyboard::KeyCode::KEY_2:
		{
			if (hero2_cd2 == 0) return;
			BeginSkill(1, 3);
			hero1->skill_5(hero1, maplayer);
			hero2_cd2 = 0;
			_plane._ad += 50;
			scheduleOnce(schedule_selector(HelloWorld::skill_5_cd), 3.0f);
			scheduleOnce(schedule_selector(HelloWorld::skill_5_over), 2.0f);
			break;

		}
		case cocos2d::EventKeyboard::KeyCode::KEY_3:
		{

			if (hero2_cd1 == 0) return;
			hero1->skill_6(hero1, maplayer);
			hero2_cd3 = 0;
			scheduleOnce(schedule_selector(HelloWorld::skill_6_cd), 10.0f);
			for (int j5 = 1005; j5 <= number_soider * 4 + 1005; j5++)
			{
				Soider* enemy123 = (Soider*)maplayer->getChildByTag(j5);
				if (enemy123 == NULL)
					continue;
				if (ifyes(hero1->getPosition(), enemy123->getPosition())) {
					be_attacked_4(_plane, enemy123);
				}
			}


			if (ifyes(hero1->getPosition(), hero2->getPosition())) {
				int blood17 = be_attacked3hero(_plane, _sprite2);
				m_pBloodView1->setCurrentBlood(blood17);
				if (blood17 <= 0)
				{
					hero2->setVisible(false);
					//重生
					time_again = 6;
					if (time_again == 6) {

						hero2->setPosition(Vec2(6300, 230));
						hero2->setScale(1);
						hero2->setVisible(true);
						time_again == 1;
						blood17 = _sprite2.get_maxblood();
						_sprite2._blood = blood17;
						m_pBloodView1->setCurrentBlood(100.0f);
						kill++;
					}
				}
			}


			BeginSkill(2, 10);
			break;
		}
		case cocos2d::EventKeyboard::KeyCode::KEY_B:
		{
			hero1->setPosition(Vec2(228, 230));
			hero1->setScale(1);
			hero1->setVisible(true);
			int blood11 = _plane.get_maxblood();
			_plane._blood = blood11;
			m_pBloodView->setCurrentBlood(100.0f);
			break;
		}

		default:
			break;
		}
	}
	if (heroname == "mage") {
		switch (keyCode)
		{

		case cocos2d::EventKeyboard::KeyCode::KEY_1:
		{
			if (hero3_cd1 == 0) return;
			hero1->skill_7(hero1, maplayer);
			hero3_cd1 = 0;
			scheduleOnce(schedule_selector(HelloWorld::skill_7_cd), 5.0f);
			scheduleOnce(schedule_selector(HelloWorld::skill_7_over), 1.0f);
			for (int j5 = 1002; j5 <= number_soider * 4 + 1000; j5++)
			{
				Soider* enemy123 = (Soider*)maplayer->getChildByTag(j5);
				if (enemy123 == NULL)
					continue;

				if (ifyes7(hero1->getPosition(), enemy123->getPosition())) {
					be_attacked_skill7(_plane, enemy123);
				}
			}
			if (ifyes7(hero1->getPosition(), hero2->getPosition())) {
				float blood17 = 100*_sprite2._blood * 0.8 / _sprite2._max_blood;
				m_pBloodView1->setCurrentBlood(blood17);
				if (blood17 <= 0)
				{
					hero2->setVisible(false);
					//重生
					time_again = 6;
					if (time_again == 6) {

						hero2->setPosition(Vec2(6300, 230));
						hero2->setScale(1);
						hero2->setVisible(true);
						time_again == 1;
						blood17 = _sprite2.get_maxblood();
						_sprite2._blood = blood17;
						m_pBloodView1->setCurrentBlood(100.0f);
						kill++;
					}
				}
			}


			BeginSkill(0, 5);
			break;
		}

		case cocos2d::EventKeyboard::KeyCode::KEY_2:
		{

			if (hero3_cd2 == 0) return;
			BeginSkill(1, 3);
			hero1->skill_8(hero1, maplayer);
			hero3_cd2 = 0;
			_plane._speed += 5;
			scheduleOnce(schedule_selector(HelloWorld::skill_8_cd), 3.0f);
			scheduleOnce(schedule_selector(HelloWorld::skill_8_over), 2.0f);
			BeginSkill(1, 3);
			break;

		}
		case cocos2d::EventKeyboard::KeyCode::KEY_3:
		{

			if (hero3_cd3 == 0)return;
			hero1->skill_9(hero1, maplayer);
			hero3_cd3 = 0;
			scheduleOnce(schedule_selector(HelloWorld::skill_9_cd), 15.0f);
			for (int j5 = 1005; j5 <= number_soider * 4 + 1005; j5++)
			{
				Soider* enemy123 = (Soider*)maplayer->getChildByTag(j5);
				if (enemy123 == NULL)
					continue;
			
				if (ccpDistance(enemy123->getPosition(), hero1->getPosition()) <= 6400) {
					be_attacked_skill9(_plane, enemy123);
				}
			}
			if (ccpDistance(hero2->getPosition(), hero1->getPosition()) <= 6400) {
				float blood17 = 100 * _sprite2._blood * 0.5 / _sprite2._max_blood;
				m_pBloodView1->setCurrentBlood(blood17);
				if (blood17 <= 0)
				{
					hero2->setVisible(false);
					//重生
					time_again = 6;
					if (time_again == 6) {

						hero2->setPosition(Vec2(6300, 230));
						hero2->setScale(1);
						hero2->setVisible(true);
						time_again == 1;
						blood17 = _sprite2.get_maxblood();
						_sprite2._blood = blood17;
						m_pBloodView1->setCurrentBlood(100.0f);
						kill++;
					}
				}
			}


			BeginSkill(2, 15);
		


			break;
		}
		case cocos2d::EventKeyboard::KeyCode::KEY_B:
		{
			hero1->setPosition(Vec2(228, 230));
			hero1->setScale(1);
			hero1->setVisible(true);
			int blood11 = _plane.get_maxblood();
			_plane._blood = blood11;
			m_pBloodView->setCurrentBlood(100.0f);
			break;
		}


		default:
			break;
		}
	}

}





void HelloWorld::menuCloseCallback(Ref* pSender)

{

	Director::getInstance()->end();



#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	exit(0);

#endif

}


