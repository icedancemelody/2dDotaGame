#include"GameMap.h"

USING_NS_CC;

#define JCHM 133
#define TIMER 233

Scene* GameMap::createScene(std::string HeroName)
{
	auto scene = Scene::create();
	auto layer = GameMap::create();
	layer->initWithName(HeroName);
	scene->addChild(layer);
	return scene;
}

void GameMap::initWithName(std::string HeroName) {
	
	_heroname = HeroName;

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();


	_tileMap = TMXTiledMap::create("Map/bg_tiledMap.tmx");
	_tileMap->setPosition(Vec2(origin.x,
		origin.y));
	_tileMap->setAnchorPoint(Vec2(0, 0));
	this->addChild(_tileMap, -1, JCHM);

	TMXObjectGroup *objG = _tileMap->getObjectGroup("Object1");
	auto object = objG->getObject("PlayerBorn");
	float x = object["x"].asFloat();
	float y = object["y"].asFloat();


	if (_heroname == std::string("warrior")) {
		Sprite* sprite = Sprite::create("/Hero/warrior_stand.png");
		//设置精灵的位置
		sprite->setPosition(Vec2(x, y));

		//设置精灵的描点为左下角
		sprite->setAnchorPoint(Vec2(0, 0));
		_tileMap->addChild(sprite, 3);

	}
	if (_heroname == std::string("shooter")) {
		Sprite* sprite = Sprite::create("/Hero/shooter_stand.png");
		//设置精灵的位置
		sprite->setPosition(Vec2(x, y));

		//设置精灵的描点为左下角
		sprite->setAnchorPoint(Vec2(0, 0));
		_tileMap->addChild(sprite, 3);
	}
	if (_heroname == std::string("mage")) {
		Sprite* sprite = Sprite::create("/Hero/mage_stand.png");
		//设置精灵的位置
		sprite->setPosition(Vec2(x, y));

		//设置精灵的描点为左下角
		sprite->setAnchorPoint(Vec2(0, 0));
		_tileMap->addChild(sprite, 3);
	}


	/*Animation* animation = Animation::create();
	for (int i = 1; i < 7; i++) {
		char file_name[50] = { 0 };
		sprintf(file_name, "Hero/Male_warrior_%d_run.png", i);
		animation->addSpriteFrameWithFile(file_name);
	}
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(2.0f / 20.0f);
	animation->setLoops(-1);
	Animate* animate = Animate::create(animation);
	sprite->runAction(animate);*/

	//设置人物血条(血条层)

	_HPLayer = Layer::create();
	m_pBloodView = new bloodView();
	m_pBloodView->setPosition(Vec2(130, 550));//位置（可自己调整）
	m_pBloodView->setScale(2.2f);//缩放比例
	m_pBloodView->setBackgroundTexture("/sprite/xue_back.png");//灰条
	m_pBloodView->setForegroundTexture("/sprite/xue_fore.png");//红条
	m_pBloodView->setTotalBlood(100.0f);//从满血开始
	m_pBloodView->setCurrentBlood(100.0f);//从满血开始
	Sprite *xuekuang = Sprite::create("/sprite/kuang.png");//血量框
	xuekuang->setPosition(Vec2(m_pBloodView->getPositionX(), m_pBloodView->getPositionY()));
	_HPLayer->addChild(xuekuang, 2);
	_HPLayer->addChild(m_pBloodView, 2);
	this->addChild(_HPLayer, 2, JCHM);

	//设置进入记分板按钮
	auto ScoreItem = MenuItemImage::create(
		"/Button/scoreboard.png",
		"/Button/scoreboard.png",
		CC_CALLBACK_1(GameMap::createScoreCallBack, this)
	);
	float board_x = origin.x + ScoreItem->getContentSize().width / 2 + 10;
	float board_y = origin.y + visibleSize.height / 2 - ScoreItem->getContentSize().height / 2 - 60;
	ScoreItem->setPosition(Vec2(board_x, board_y));


	//设置进入商店按钮
	auto shopItem = MenuItemImage::create(
		"/Button/shopButton666.png",
		"/Button/shopButton666.png",
		CC_CALLBACK_1(GameMap::createShopCallBack, this));
	float spmn_x = origin.x + shopItem->getContentSize().width / 2;
	float spmn_y = origin.y + visibleSize.height / 2 - shopItem->getContentSize().height / 2 + 30;
	shopItem->setPosition(Vec2(spmn_x, spmn_y));

	//暂停按钮
	auto SettingItem = MenuItemImage::create(
		"/Button/setting.png",
		"/Button/setting.png",
		CC_CALLBACK_1(GameMap::createSettingCallBack, this));

	SettingItem->setPosition(Vec2(
		visibleSize.width - SettingItem->getContentSize().width / 2 + 30,
		SettingItem->getContentSize().height / 2 - 40
	));
	SettingItem->setScale(0.3f);
	auto menu = Menu::create(shopItem, ScoreItem, SettingItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 5, 333);

	time = 0;
	_Timelabel = Layer::create();
	auto timelabel = Label::createWithTTF("00:00", "fonts/Marker Felt.ttf", 30);
	timelabel->setPosition(Vec2(origin.x + visibleSize.width - timelabel->getContentSize().width,
		origin.y + visibleSize.height - timelabel->getContentSize().height));
	_Timelabel->addChild(timelabel, 2, TIMER);
	this->scheduleUpdate();
	this->schedule(schedule_selector(GameMap::updatetime), 1.0f);
	this->addChild(_Timelabel, 2, JCHM);
}
bool GameMap::init() {
	if (!Layer::init()) {
		return false;
	}
	
	return true;
}

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
	closeShopButton->setPosition(_shopBg->getPosition() + Vec2(375, -180));
	
	//item
	MenuItemImage* ItemSword[4];
	MenuItemImage* ItemCloth[4];
	MenuItemImage* ItemLive[4];
	MenuItemImage* ItemShoe[4];
	for (int i = 1; i < 5; i++) {
		char fileName[50] = {0};
		char callbackname[50] = {0};
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
		ItemSword[i-1] = MenuItemImage::create(
			fileName,
			fileName,
			CC_CALLBACK_1(GameMap::buyItemCallBack, this)
		);
		ItemSword[i - 1]->setScale(0.8f);
		ItemSword[i-1]->setPosition(_shopBg->getPosition() + Vec2(-300, 220 - (80 * i)));
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
		ItemCloth[i - 1] = MenuItemImage::create(
			fileName,
			fileName,
			CC_CALLBACK_1(GameMap::buyItemCallBack, this)
		);
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
		ItemLive[i - 1] = MenuItemImage::create(
			fileName,
			fileName,
			CC_CALLBACK_1(GameMap::buyItemCallBack, this)
		);
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
		ItemShoe[i - 1] = MenuItemImage::create(
			fileName,
			fileName,
			CC_CALLBACK_1(GameMap::buyItemCallBack, this)
		);
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
	};


	
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
	this->addChild(_shopLayer, 5,JCHM);
}

//商店的关闭
void GameMap::closeShopCallBack(cocos2d::Ref* pSender) {
	_shopLayer->removeFromParent();
}
//由此开始是16种装备购买的回调函数
void GameMap::buyItemCallBack(cocos2d::Ref* pSender){}
void GameMap::buySwordCallBack1(cocos2d::Ref* pSender){
	//if(hero->money()<300||eqp_num==6||hero->havesword[0]==true){return;}            不能买条件：钱不够、装备满、已经1
	//hero->get.ad()+=10;                加攻击
	//bool 函数类
	//hero->havesword[0]=true;     设定英雄已有此装备
	//hero->eqp_num++;              装备栏数量+1
}
void GameMap::buySwordCallBack2(cocos2d::Ref* pSender){
	//if(hero->money()<700||hero->havesword[0]==false||hero->havesword[1]==true){return;}                  不能买条件：钱不够、没有1、已有2
	//hero->havesword[0]=false;         设定英雄没有此装备了
	//hero->get.ad()+=（50-10）;                    加攻击
	//hero->havesword[1]=true;          设定英雄已有此装备
}
void GameMap::buySwordCallBack3(cocos2d::Ref* pSender){
	//if(hero->money()<1300||hero->havesword[1]==false||hero->havesword[2]==true){return;}                  不能买条件：钱不够、没有2、已有3
	//hero->havesword[1]=false;         设定英雄没有此装备了
	//hero->get.ad()+=（100-50）;                    加攻击
	//hero->havesword[2]=true;          设定英雄已有此装备
}
void GameMap::buySwordCallBack4(cocos2d::Ref* pSender){
	//if(hero->money()<2000||hero->havesword[2]==false||hero->havesword[3]==true){return;}                  不能买条件：钱不够、没有3、已有4
	//hero->havesword[2]=false;         设定英雄没有此装备了
	//hero->get.ad()+=（150-100）;                    加攻击
	//hero->havesword[3]=true;          设定英雄已有此装备
}
void GameMap::buyClothCallBack1(cocos2d::Ref* pSender){}
void GameMap::buyClothCallBack2(cocos2d::Ref* pSender){}
void GameMap::buyClothCallBack3(cocos2d::Ref* pSender){}
void GameMap::buyClothCallBack4(cocos2d::Ref* pSender){}
void GameMap::buyLiveCallBack1(cocos2d::Ref* pSender){}
void GameMap::buyLiveCallBack2(cocos2d::Ref* pSender){}
void GameMap::buyLiveCallBack3(cocos2d::Ref* pSender){}
void GameMap::buyLiveCallBack4(cocos2d::Ref* pSender){}
void GameMap::buyShoeCallBack1(cocos2d::Ref* pSender){}
void GameMap::buyShoeCallBack2(cocos2d::Ref* pSender){}
void GameMap::buyShoeCallBack3(cocos2d::Ref* pSender){}
void GameMap::buyShoeCallBack4(cocos2d::Ref* pSender){}



//由此结束装备购买函数
void GameMap::updatetime(float dt) {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_Timelabel->getChildByTag(TIMER)->removeFromParent();
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
	_Timelabel->addChild(timelabel, 2,TIMER);
	m_pBloodView->setCurrentBlood(m_pBloodView->getCurrentBlood() - 1);
}

void GameMap::createScoreCallBack(cocos2d::Ref* pSender){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//Scoreboardbg
	_ScoreboardLayer = Layer::create();
	auto _Bg = Sprite::create("/BG/scoreboardbg.jpg");
	_Bg->setPosition(Vec2(
		visibleSize.width / 2,
		visibleSize.height / 2
	));

	std::string a = std::to_string(time);

	
	//closebutton
	auto closeScoreButton = MenuItemImage::create(
		"/Button/closescore.png",
		"/Button/closescore.png",
		CC_CALLBACK_1(GameMap::closeScoreCallBack, this)
	);
	closeScoreButton->setPosition(_Bg->getPosition() + Vec2(260, 195));

	//我方战绩（包括英雄类型、击杀数、死亡数、金钱）
	auto my = Label::createWithSystemFont("MY HERO:warrior  LV:"+a,"fonts/arial-unicode-26.fnt",26);//间隔10字符位
	my->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2+180));
	_ScoreboardLayer->addChild(my, 4);

	auto my_kill = Label::createWithSystemFont("KILL:"+a, "fonts/arial-unicode-26.fnt", 26);
	my_kill->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));
	_ScoreboardLayer->addChild(my_kill, 4);

	auto my_die = Label::createWithSystemFont("DIE:"+a, "fonts/arial-unicode-26.fnt", 26);
	my_die->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 120));
	_ScoreboardLayer->addChild(my_die, 4);

	auto my_money = Label::createWithSystemFont("MONEY:"+a, "fonts/arial-unicode-26.fnt", 26);
	my_money->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 90));
	_ScoreboardLayer->addChild(my_money, 4);

	//敌方战绩（包括英雄类型、击杀数、死亡数、金钱）
	auto other = Label::createWithSystemFont("OTHER HERO:mega  LV:"+a, "fonts/arial-unicode-26.fnt", 26);//间隔10字符位
	other->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 -90));
	_ScoreboardLayer->addChild(other, 4);

	auto other_kill = Label::createWithSystemFont("KILL:" + a, "fonts/arial-unicode-26.fnt", 26);
	other_kill->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 -120));
	_ScoreboardLayer->addChild(other_kill, 4);

	auto other_die = Label::createWithSystemFont("DIE:" + a, "fonts/arial-unicode-26.fnt", 26);
	other_die->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 -150));
	_ScoreboardLayer->addChild(other_die, 4);

	auto other_money = Label::createWithSystemFont("MONEY:" + a, "fonts/arial-unicode-26.fnt", 26);
	other_money->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 -180));
	_ScoreboardLayer->addChild(other_money, 4);

	//装备显示
	int my_eqp = 0;
	int other_eqp = 0;
	bool me_have[4][4];
	bool other_have[4][4];

	int my_this_eqp[4][4] = {0};
	int other_this_eqp[4][4] = { 0 };

	me_have[0][3] = true;
	me_have[1][3] = true;
	me_have[2][3] = true;
	me_have[3][3] = true;
	my_this_eqp[0][3] = 2;
	my_this_eqp[1][3] = 2;
	my_this_eqp[2][3] = 1;
	my_this_eqp[3][3] = 1;
	other_have[1][3] = true;
	other_this_eqp[1][3] = 6;
	//我方装备
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if(i==0){
				if (my_eqp >= 6) { break; }//装备数大于6不再显示
				else {
					if (me_have[i][j] == true) {
						for (int k = 0; k < my_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/sword%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (my_eqp * 80), visibleSize.height / 2 + 40));
							eqp_show->setScale(0.75f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							my_eqp++;
						}
					}
				}
			}
			if (i == 1) {
				if (my_eqp >= 6) { break; }//装备数大于6不再显示
				else {
					if (me_have[i][j] == true) {
						for (int k = 0; k < my_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/cloth%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (my_eqp * 80), visibleSize.height / 2 + 40));
							eqp_show->setScale(0.75f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							my_eqp++;
						}
					}
				}
			}
			if (i == 2) {
				if (my_eqp >= 6) { break; }//装备数大于6不再显示
				else {
					if (me_have[i][j] == true) {
						for (int k = 0; k < my_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/live%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (my_eqp * 80), visibleSize.height / 2 + 40));
							eqp_show->setScale(0.75f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							my_eqp++;
							}
						}
					}
				}
			if (i == 3) {
				if (my_eqp >= 6) { break; }//装备数大于6不再显示
				else {
					if (me_have[i][j] == true) {
						for (int k = 0; k < my_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/shoe%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (my_eqp * 80), visibleSize.height / 2 + 40));
							eqp_show->setScale(0.6f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							my_eqp++;
						}
					}
				}
			}
		}
	}

	//敌方装备展示
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == 0) {
				if (other_eqp >= 6) { break; }//装备数大于6不再显示
				else {
					if (other_have[i][j] == true) {
						for (int k = 0; k < other_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/sword%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (other_eqp * 80), visibleSize.height / 2 - 40));
							eqp_show->setScale(0.75f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							other_eqp++;
						}
					}
				}
			}
			if (i == 1) {
				if (other_eqp >= 6) { break; }//装备数大于6不再显示
				else {
					if (other_have[i][j] == true) {
						for (int k = 0; k < other_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/cloth%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (other_eqp * 80), visibleSize.height / 2 - 40));
							eqp_show->setScale(0.75f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							other_eqp++;
						}
					}
				}
			}
			if (i == 2) {
				if (other_eqp >= 6) { break; }//装备数大于6不再显示
				else {
					if (other_have[i][j] == true) {
						for (int k = 0; k < other_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/live%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (other_eqp * 80), visibleSize.height / 2 - 40));
							eqp_show->setScale(0.75f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							other_eqp++;
						}
					}
				}
			}
			if (i == 3) {
				if (other_eqp >= 6) { break; }//装备数大于6不再显示
				else {
					if (other_have[i][j] == true) {
						for (int k = 0; k < other_this_eqp[i][j]; k++) {
							char file_name[50] = { 0 };
							sprintf(file_name, "equipment/shoe%d.png", j + 1);
							Sprite* eqp_show = Sprite::create(file_name);
							eqp_show->setPosition(Vec2(visibleSize.width / 2 - 200 + (other_eqp * 80), visibleSize.height / 2 - 40));
							eqp_show->setScale(0.6f);
							_ScoreboardLayer->addChild(eqp_show, 4);
							other_eqp++;
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
	this->addChild(_ScoreboardLayer, 5, JCHM);
}

void GameMap::closeScoreCallBack (cocos2d::Ref* pSender) {
	_ScoreboardLayer->removeFromParent();
}

//暂停画面
void GameMap::createSettingCallBack(cocos2d::Ref* pSender) {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	RenderTexture *renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	Director::getInstance()->pushScene(Gamepause::scene(renderTexture));
}