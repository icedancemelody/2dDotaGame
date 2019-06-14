#include "HelloWorldScene.h"

#include "SimpleAudioEngine.h"
#include "people.h"

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
int maxexp=340;
int exp_increase = 100;
int jishashu=0;
int budaoshu = 0;

hero _plane(100, 100, 100, 100, 100, 100, 100, 3, 100, 100, 0, 100000);

hero _sprite2(100, 10, 10, 10, 80, 10, 10, 10, 10, 10, 300, 30);

Scene* HelloWorld::createScene()

{

	Scene *sc = Scene::create();

	Layer *ly = HelloWorld::create();

	sc->addChild(ly);

	return sc;

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

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	maplayer = Layer::create();
	_tileMap = TMXTiledMap::create("bg_tiledMap.tmx");
	_tileMap->setPosition(Vec2(origin.x, origin.y));
	_tileMap->setAnchorPoint(Vec2(0, 0));
	maplayer->addChild(_tileMap, 0);
	this->addChild(maplayer, -1, 100);

	


	TMXObjectGroup *objG = _tileMap->getObjectGroup("Object1");
	auto object = objG->getObject("PlayerBorn");
	float a = object["x"].asFloat();
	float b = object["y"].asFloat();


	sprite2 = Sprite::create("plane1.png");
	_tileMap->addChild(sprite2, 1, 133);
	sprite2->setPosition(Vec2(a + 500, b + 40));
	time = 0;
	auto timelabel = Label::createWithTTF("00:00", "fonts/Marker Felt.ttf", 30);
	timelabel->setPosition(Vec2(origin.x + visibleSize.width - timelabel->getContentSize().width,
		origin.y + visibleSize.height - timelabel->getContentSize().height));
	this->addChild(timelabel, 2, TIMER);
	this->schedule(schedule_selector(HelloWorld::updatetime), 1.0f);
	//动画
	hero1 = Hero::create();
	hero1->InitHeroSprite("male_shooter/Male_shooter_stand_1.png");
	hero1->setPosition(Vec2(a + 100, b + 200));
	hero1->setScale(1);
	maplayer->addChild(hero1, 2);



	auto tower1 = Tower::createWithTowerTypes(TowerType1);
	tower1->setPosition(Vec2(300, 200));
	tower1->setScale(1.2f);
	maplayer->addChild(tower1, 1, 2);


	auto tower2 = Tower::createWithTowerTypes(TowerType1);
	tower2->setPosition(Vec2(2500, 200));
	tower2->setScale(1.2f);
	maplayer->addChild(tower2, 1, 3);


	auto tower3 = Tower::createWithTowerTypes(TowerType3);
	tower3->setPosition(Vec2(3900, 200));
	tower3->setScale(1.2f);
	maplayer->addChild(tower3, 1, 1002);


	auto tower4 = Tower::createWithTowerTypes(TowerType3);
	tower4->setPosition(Vec2(6100, 200));
	tower4->setScale(1.2f);
	maplayer->addChild(tower4, 1, 1003);


	auto home1 = Tower::createWithTowerTypes(TowerType2);
	home1->setPosition(Vec2(100, 200));
	home1->setScale(1.2f);
	maplayer->addChild(home1, 1, 1);


	auto home2 = Tower::createWithTowerTypes(TowerType4);
	home2->setPosition(Vec2(6300, 200));
	home2->setScale(1.2f);
	maplayer->addChild(home2, 1, 1001);

	this->schedule(schedule_selector(HelloWorld::updatefriend), (1.5f));
	this->schedule(schedule_selector(HelloWorld::updatefriendtower), (3.0f));
	this->schedule(schedule_selector(HelloWorld::updateenemy), (1.5f));
	this->schedule(schedule_selector(HelloWorld::updateenemytower), (3.0f));

	auto listenerkeyPad = EventListenerKeyboard::create();


	    listenerkeyPad->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys[keyCode] = true;
		auto W_key = cocos2d::EventKeyboard::KeyCode::KEY_W;
		auto A_key = cocos2d::EventKeyboard::KeyCode::KEY_A;
		auto S_key = cocos2d::EventKeyboard::KeyCode::KEY_S;
		auto D_key = cocos2d::EventKeyboard::KeyCode::KEY_D;
		if (isKeyPressed(W_key)) {
			hero1->SetAnimation("male_shooter/Male_shooter_run_", 4, hero1->HeroDirecton);
		}

		if (isKeyPressed(A_key)) {
			hero1->HeroDirecton = true;
			hero1->SetAnimation("male_shooter/Male_shooter_run_", 4, hero1->HeroDirecton);
		}

		if (isKeyPressed(S_key)) {
			hero1->SetAnimation("male_shooter/Male_shooter_run_", 4, hero1->HeroDirecton);
		}

		if (isKeyPressed(D_key)) {
			hero1->HeroDirecton = false;
			hero1->SetAnimation("male_shooter/Male_shooter_run_", 4, hero1->HeroDirecton);
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
	m_pBloodView1->setPosition(Vec2(630, 250));
	m_pBloodView1->setScale(2.2f);
	m_pBloodView1->setBackgroundTexture("xue_back.png");
	m_pBloodView1->setForegroundTexture("xue_fore.png");
	m_pBloodView1->setTotalBlood(100.0f);
	m_pBloodView1->setCurrentBlood(100.0f);
	Sprite *xuekuang1 = Sprite::create("kuang.png");
	xuekuang1->setPosition(Vec2(m_pBloodView1->getPositionX(), m_pBloodView1->getPositionY()));
	maplayer->addChild(xuekuang1, 2);
	maplayer->addChild(m_pBloodView1, 2);

	//设置层
	_setLayer = Layer::create();
	_shopLayer = Layer::create();
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
		"shopButton666.png",
		"shopButton666.png",
		CC_CALLBACK_1(HelloWorld::createShopCallBack, this));
	float spmn_x = origin.x + shopItem->getContentSize().width / 2;
	float spmn_y = origin.y + visibleSize.height / 2 - shopItem->getContentSize().height / 2 + 30;
	shopItem->setPosition(Vec2(spmn_x, spmn_y));

	auto menu = Menu::create(ScoreItem,shopItem, NULL);
	menu->setPosition(Vec2::ZERO);
	_setLayer->addChild(menu, 1);
	this->addChild(_setLayer, 5, 636);


	return true;

}


void HelloWorld::createShopCallBack(cocos2d::Ref* pSender) {
	//_player->stopAllActions();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (shop_is_open == true||score_is_open==true) { return; }
	//shoplayer
	_shopLayer = Layer::create();
	auto _shopBg = Sprite::create("shopbg.png");
	_shopBg->setPosition(Vec2(
		visibleSize.width / 2,
		visibleSize.height / 2
	));
	//closebutton
	auto closeShopButton = MenuItemImage::create(
		"shopButtonNormal.png",
		"shopButtonSelected.png",
		CC_CALLBACK_1(HelloWorld::closeShopCallBack, this)
	);
	closeShopButton->setPosition(_shopBg->getPosition() + Vec2(375, -180));

	//show my money
	std::string money = std::to_string((int)_plane.get_gp());
	auto my_money = Label::createWithSystemFont("MONEY:" + money, "fonts/arial-unicode-26.fnt", 30);
	my_money->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 -180));
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
void HelloWorld::buySwordCallBack1(cocos2d::Ref* pSender){
	if (_plane._gp < 300 || _plane.eqp_num == 6) {return;}
	_plane._ad += 10;
	_plane._gp -= 300;
	_plane.me_have[0][0] = true;
	_plane.me_this_eqp[0][0]++;
	_plane.eqp_num++;
}
void HelloWorld::buySwordCallBack2(cocos2d::Ref* pSender){
	if (_plane._gp < 700 || _plane.me_have[0][0] == false) { return; }
	_plane._ad += 40;
	_plane._gp -= 700;
	_plane.me_have[0][0] = false;
	_plane.me_have[0][1] = true;
	_plane.me_this_eqp[0][0]--;
	_plane.me_this_eqp[0][1]++;
}
void HelloWorld::buySwordCallBack3(cocos2d::Ref* pSender){
	if (_plane._gp < 1300 || _plane.me_have[0][1] == false) { return; }
	_plane._ad += 50;
	_plane._gp -= 1300;
	_plane.me_have[0][1] = false;
	_plane.me_have[0][2] = true;
	_plane.me_this_eqp[0][1]--;
	_plane.me_this_eqp[0][2]++;
}
void HelloWorld::buySwordCallBack4(cocos2d::Ref* pSender){
	if (_plane._gp < 2000 || _plane.me_have[0][2] == false) { return; }
	_plane._ad += 50;
	_plane._gp -= 2000;
	_plane.me_have[0][2] = false;
	_plane.me_have[0][3] = true;
	_plane.me_this_eqp[0][2]--;
	_plane.me_this_eqp[0][3]++;
}
void HelloWorld::buyClothCallBack1(cocos2d::Ref* pSender){
	if (_plane._gp < 450 || _plane.eqp_num == 6) { return; }
	_plane._hujia += 10;
	_plane._gp -= 450;
	_plane.me_have[1][0] = true;
	_plane.me_this_eqp[1][0]++;
	_plane.eqp_num++;
}
void HelloWorld::buyClothCallBack2(cocos2d::Ref* pSender){
	if (_plane._gp < 1000 || _plane.me_have[1][0] == false) { return; }
	_plane._hujia += 40;
	_plane._gp -= 1000;
	_plane.me_have[1][0] = false;
	_plane.me_have[1][1] = true;
	_plane.me_this_eqp[1][0]--;
	_plane.me_this_eqp[1][1]++;
}
void HelloWorld::buyClothCallBack3(cocos2d::Ref* pSender){
	if (_plane._gp < 1500 || _plane.me_have[1][1] == false) { return; }
	_plane._hujia += 50;
	_plane._gp -= 1500;
	_plane.me_have[1][1] = false;
	_plane.me_have[1][2] = true;
	_plane.me_this_eqp[1][1]--;
	_plane.me_this_eqp[1][2]++;
}
void HelloWorld::buyClothCallBack4(cocos2d::Ref* pSender){
	if (_plane._gp < 2400 || _plane.me_have[1][2] == false) { return; }
	_plane._hujia += 50;
	_plane._gp -= 2400;
	_plane.me_have[1][2] = false;
	_plane.me_have[1][3] = true;
	_plane.me_this_eqp[1][2]--;
	_plane.me_this_eqp[1][3]++;
}
void HelloWorld::buyLiveCallBack1(cocos2d::Ref* pSender){
	if (_plane._gp < 400 || _plane.eqp_num == 6) { return; }
	_plane._max_blood+=200;
	_plane._gp -= 400;
	_plane.me_have[2][0] = true;
	_plane.me_this_eqp[2][0]++;
	_plane.eqp_num++;
}
void HelloWorld::buyLiveCallBack2(cocos2d::Ref* pSender){
	if (_plane._gp < 800 || _plane.me_have[2][0] == false) { return; }
	_plane._max_blood += 300;
	_plane._gp -= 800;
	_plane.me_have[2][0] = false;
	_plane.me_have[2][1] = true;
	_plane.me_this_eqp[2][0]--;
	_plane.me_this_eqp[2][1]++;
}
void HelloWorld::buyLiveCallBack3(cocos2d::Ref* pSender){
	if (_plane._gp < 1200 || _plane.me_have[2][1] == false) { return; }
	_plane._max_blood += 700;
	_plane._gp -= 1200;
	_plane.me_have[2][1] = false;
	_plane.me_have[2][2] = true;
	_plane.me_this_eqp[2][1]--;
	_plane.me_this_eqp[2][2]++;
}
void HelloWorld::buyLiveCallBack4(cocos2d::Ref* pSender){
	if (_plane._gp < 1600 || _plane.me_have[2][2] == false) { return; }
	_plane._max_blood =_plane._max_blood*2;
	_plane._gp -= 1600;
	_plane.me_have[2][2] = false;
	_plane.me_have[2][3] = true;
	_plane.me_this_eqp[2][2]--;
	_plane.me_this_eqp[2][3]++;
}
bool have_shoe = false;
void HelloWorld::buyShoeCallBack1(cocos2d::Ref* pSender){
	if (_plane._gp < 250 || _plane.eqp_num == 6||have_shoe==true) { return; }
	_plane._speed+=1.5;
	_plane._gp -= 250;
	_plane.me_have[3][0] = true;
	_plane.me_this_eqp[3][0]++;
	_plane.eqp_num++;
	have_shoe = true;
}
void HelloWorld::buyShoeCallBack2(cocos2d::Ref* pSender){
	if (_plane._gp < 800 || _plane.me_have[3][0] == false) { return; }
	_plane._speed += 2.0;
	_plane._gp -= 800;
	_plane.me_have[3][0] = false;
	_plane.me_have[3][1] = true;
	_plane.me_this_eqp[3][0]--;
	_plane.me_this_eqp[3][1]++;
}
void HelloWorld::buyShoeCallBack3(cocos2d::Ref* pSender){
	if (_plane._gp < 1100 || _plane.me_have[3][0] == false) { return; }
	_plane._speed += 1.5;
	_plane._gp -= 1100;
	_plane._ad += 80;
	_plane.me_have[3][0] = false;
	_plane.me_have[3][2] = true;
	_plane.me_this_eqp[3][0]--;
	_plane.me_this_eqp[3][2]++;
}
void HelloWorld::buyShoeCallBack4(cocos2d::Ref* pSender){
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
	if (score_is_open == true|| shop_is_open == true) { return; }
	//Scoreboardbg
	_ScoreboardLayer = Layer::create();
	auto _Bg = Sprite::create("scoreboardbg.jpg");
	_Bg->setPosition(Vec2(
		visibleSize.width / 2,
		visibleSize.height / 2
	));
	//计分记录数据：
	std::string b = std::to_string((int)_plane._level);
	std::string c = std::to_string((int)_plane.get_gp());
	std::string d = std::to_string((int)_plane.get_ad());
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
	auto my = Label::createWithSystemFont("MY HERO:warrior Lv:"+b, "fonts/arial-unicode-26.fnt", 26);//间隔10字符位
	my->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 160));
	_ScoreboardLayer->addChild(my, 4);

	auto my_kill = Label::createWithSystemFont("KILL:" + f+"  KILL SOIDER : "+ e, "fonts/arial-unicode-26.fnt", 26);
	my_kill->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 130));
	_ScoreboardLayer->addChild(my_kill, 4);


	auto my_die = Label::createWithSystemFont("DIE:" + b, "fonts/arial-unicode-26.fnt", 26);
	my_die->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	_ScoreboardLayer->addChild(my_die, 4);

	//敌方战绩（包括英雄类型、击杀数、死亡数、金钱）
	auto other = Label::createWithSystemFont("OTHER HERO:mega", "fonts/arial-unicode-26.fnt", 26);//间隔10字符位
	other->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 70));
	_ScoreboardLayer->addChild(other, 4);

	auto other_kill = Label::createWithSystemFont("KILL:" + d, "fonts/arial-unicode-26.fnt", 26);
	other_kill->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
	_ScoreboardLayer->addChild(other_kill, 4);

	auto other_die = Label::createWithSystemFont("DIE:" + b, "fonts/arial-unicode-26.fnt", 26);
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


//判断精灵与精灵之间的碰撞
bool isCircleCollision(Point pos1, float radius1, Point pos2, float radius2)
{
	//运用勾股定理判断两圆是否相交
	if (sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2)) > pow(radius1 + radius2, 2))
	{
		return false;
	}
	return true;
}
//判断点击位置是否有精灵
bool isinbound(Vec2 position, Vec2 touchposition, Vec2 size) {
	if (touchposition.x <= position.x + size.x / 2 && touchposition.x >= position.x - size.x / 2 &&
		touchposition.y <= position.y + size.y / 2 && touchposition.y >= position.y - size.y / 2)
	{
		return true;
	}
	return false;
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



void HelloWorld::updatetime(float dt)
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->getChildByTag(TIMER)->removeFromParent();
	time++;


	int minutes = time / 60;
	int seconds = time - minutes * 60;
	_plane._gp += 1;
	if (time % 45 == 0||time==10)
	{
		auto enemy1 = Soider::createWithSoiderTypes(SoiderType1);
		enemy1->setVelocity(Vec2(50, 0));
		enemy1->setPosition(Vec2(400, 200));
		enemy1->setFlipX(true);
		maplayer->addChild(enemy1, 2, number_soider * 3 + 1);	
	


		auto enemy2 = Soider::createWithSoiderTypes(SoiderType1);
		enemy2->setVelocity(Vec2(50, 0));
		enemy2->setPosition(Vec2(300, 200));
		enemy2->setFlipX(true);
		maplayer->addChild(enemy2, 2, number_soider * 3 + 2);

		auto enemy3 = Soider::createWithSoiderTypes(SoiderType2);
		enemy3->setVelocity(Vec2(50, 0));
		enemy3->setPosition(Vec2(200, 200));
		enemy3->setFlipX(true);
		maplayer->addChild(enemy3, 2, number_soider * 3 + 3);

		auto enemy4 = Soider::createWithSoiderTypes(SoiderType1);
		enemy4->setVelocity(Vec2(-50, 0));
		enemy4->setPosition(Vec2(6100, 200));
		maplayer->addChild(enemy4, 2, number_soider * 3 + 1001);

		auto enemy5 = Soider::createWithSoiderTypes(SoiderType1);
		enemy5->setVelocity(Vec2(-50, 0));
		enemy5->setPosition(Vec2(6200, 200));
		maplayer->addChild(enemy5, 2, number_soider * 3 + 1002);

		auto enemy6 = Soider::createWithSoiderTypes(SoiderType2);
		enemy6->setVelocity(Vec2(-50, 0));
		enemy6->setPosition(Vec2(6300, 200));
		maplayer->addChild(enemy6, 2, number_soider * 3 + 1003);

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

}


//level_up
void level_up()
{
	_plane._ad += 9;
	_plane._hujia += 1;
	_plane._exp = 0;
	maxexp += exp_increase;
	exp_increase += 40;
}

//小兵互怼
void Soider::be_attacked(Soider* a, Soider* b) {
	

	int x151 = b->get_blood();
	int x152 = a->get_ad();
	int x99 = b->getHujia();
	b->setBlood(x151 - (x152-x99));
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



void HelloWorld::updatefriend(float dt)//实现友方AI
{
	for (int i1 = 4;i1 <= number_soider * 3;i1++)
	{
		Soider* friendsoider = (Soider*)maplayer->getChildByTag(i1);
		if (friendsoider == NULL)
			continue;
		for (int j1 = 1001;j1 <= number_soider * 3 + 1000;j1++)
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


void HelloWorld::updateenemy(float dt)//实现敌军AI
{
	for (int i2 = 1004;i2 <= number_soider * 3 + 1000;i2++)
	{
		Soider* enemysoider1 = (Soider*)maplayer->getChildByTag(i2);
		if (enemysoider1 == NULL)
			continue;
		for (int j2 = 1;j2 <= number_soider * 3;j2++)
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



void Tower::be_attacked1(Tower* a, Soider* b) {


	int x153 = b->get_blood();
	int x154 = a->get_ad1();
	int x100 = b->getHujia();
	b->setBlood(x153 - (x154-x100));

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

void HelloWorld::updatefriendtower(float dt)//友军防御塔AI
{
	for (int i3 = 2;i3 <= 3;i3++)
	{
		Tower* friendtower1 = (Tower*)maplayer->getChildByTag(i3);
		if (friendtower1 == NULL)
			continue;
		for (int j3 = 1004;j3 <= number_soider * 3 + 1000;j3++)
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

void HelloWorld::updateenemytower(float dt)//敌军防御塔AI
{
	for (int i4 = 1002;i4 <= 1003;i4++)
	{
		Tower* enemytower2 = (Tower*)maplayer->getChildByTag(i4);
		if (enemytower2 == NULL)
			continue;
		for (int j4 = 4;j4 <= number_soider * 3;j4++)
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


void hero::exp_up(hero me,Soider *other)

{
	me._exp = me._exp + other->getExp();
}






void be_attacked2(hero a, Soider* b) {


	int x155 = b->get_blood();
	int x156 = a.get_ad();
	int x157 = b->getHujia();
	
	b->setBlood(x155 -(x156-x157));
	int diaoxue = (x155 - (x156 - x157)) * 100 / b->getMaxblood();
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
		_plane._gp = _plane._gp + b->getVal()+10;
		budaoshu++;
		b->removeFromParent();

	}
}

bool HelloWorld::touchBegan(Touch *touch, Event* event)
{
	
	x_touch = touch->getLocation().x + countx * 2;
	y_touch = touch->getLocation().y;
	Vec2 touchposition = Vec2(x_touch, y_touch);
	Vec2 sprite2_position = sprite2->getPosition();

	Vec2 sprite2_size = sprite2->getContentSize();

	if (isinbound(sprite2_position, touchposition, sprite2_size)) {

		auto bullet1 = Sprite::create("CloseNormal.png");
		maplayer->addChild(bullet1, 2);

		bullet1->setPosition(ccp(sprite1_position_x, sprite1_position_y));


		CCPoint ptOutOfWorld1 = Vec2(x_touch, y_touch);
		float v = 300.000000;
		//传说中的定时器
		//this->scheduleUpdate();
		//this->myupdate(x_touch - sprite1_position_x, y_touch - sprite1_position_y, bullet1);
		/*this->schedule(schedule_selector(HelloWorld::myupdate));*/


		auto actionMove = CCMoveTo::create(flytime, ptOutOfWorld1);
		auto actionMovehide = CCHide::create();


		Sequence* sequence = Sequence::create(actionMove, actionMovehide, NULL);
		bullet1->runAction(sequence);//发射子弹

		/*//子弹与精灵碰撞消除子弹
		if (bullet1->boundingBox().intersectsRect(sprite2->boundingBox()))
		{
			bullet1->setScale(2.0);
		};*/
		_sprite2.be_attacked_by(_plane);
		m_pBloodView1->setCurrentBlood(_sprite2.get_blood());
	

		if (_sprite2.get_blood() <= 0) {
			sprite2->setVisible(false);
			jishashu++;

		}

	}

	for (int j5 = 1001; j5 <= number_soider * 3 + 1000; j5++)
	{
		Soider* enemy123 = (Soider*)maplayer->getChildByTag(j5);
		if (enemy123 == NULL)
			continue;
		if (ccpDistance(enemy123->getPosition(), hero1->getPosition()) <= 400)
		{
			
			auto bullet2 = Sprite::create("CloseSelected.png");
			maplayer->addChild(bullet2, 1);
			bullet2->setPosition(hero1->getPosition());
			CCPoint attck_point = Vec2(enemy123->getPosition().x, enemy123->getPosition().y);
			auto actionMove1 = CCMoveTo::create(flytime, attck_point);
			auto actionMovehide1 = CCHide::create();

			Sequence* sequence1 = Sequence::create(actionMove1, actionMovehide1, NULL);
			bullet2->runAction(sequence1);
			be_attacked2(_plane, enemy123);
			hero1->AttackAnimation("male_shooter/Male_shooter_attack_", 5, hero1->HeroDirecton);
			break;
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

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{

	switch (keyCode)
	{

	case cocos2d::EventKeyboard::KeyCode::KEY_J:
	{

		for (int j5 = 1001;j5 <= number_soider * 3 + 1000;j5++)
		{
			Soider* enemy123 = (Soider*)maplayer->getChildByTag(j5);
			if (enemy123 == NULL)
				continue;
			if (ccpDistance(enemy123->getPosition(), plane->getPosition()) <= 400)
			{
				auto bullet2 = Sprite::create("CloseSelected.png");
				maplayer->addChild(bullet2, 1);
				bullet2->setPosition(plane->getPosition());
				CCPoint attck_point = Vec2(enemy123->getPosition().x, enemy123->getPosition().y);
				auto actionMove1 = CCMoveTo::create(flytime, attck_point);
				auto actionMovehide1 = CCHide::create();

				Sequence* sequence1 = Sequence::create(actionMove1, actionMovehide1, NULL);
				bullet2->runAction(sequence1);
				break;
			}
		}
	}

	default:
		break;
	}
}




void HelloWorld::menuCloseCallback(Ref* pSender)

{

	Director::getInstance()->end();



#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	exit(0);

#endif

}


