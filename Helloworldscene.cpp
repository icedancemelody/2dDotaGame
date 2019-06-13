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

hero _plane(100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 0, 0);

hero _sprite2(100, 10, 10, 10, 80, 10, 10, 10, 10, 10, 300, 30);

Scene* HelloWorld::createScene()

{

	Scene *sc = Scene::create();

	Layer *ly = HelloWorld::create();

	sc->addChild(ly);

	return sc;

}


//地图随主角移动:获得主角在地图的相对位置，并设置地图位置。
Point scenemove(Sprite *plane, TMXTiledMap *_tileMap, Vec2 vPos)
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


	plane = Sprite::create("plane.png");
	_tileMap->addChild(plane, 1, 131);
	plane->setPosition(Vec2(a + 100, b + 40));
	plane->setAnchorPoint(Vec2(1.0, 0.5));
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
	_tileMap->addChild(hero1, 2);



	auto tower1 = Tower::createWithTowerTypes(TowerType1);
	tower1->setPosition(Vec2(300, 200));
	maplayer->addChild(tower1, 2, 2);


	auto tower2 = Tower::createWithTowerTypes(TowerType1);
	tower2->setPosition(Vec2(800, 200));
	maplayer->addChild(tower2, 2, 3);


	auto tower3 = Tower::createWithTowerTypes(TowerType1);
	tower3->setPosition(Vec2(1500, 200));
	maplayer->addChild(tower3, 2, 1002);


	auto tower4 = Tower::createWithTowerTypes(TowerType1);
	tower4->setPosition(Vec2(2000, 200));
	maplayer->addChild(tower4, 2, 1003);


	auto home1 = Tower::createWithTowerTypes(TowerType2);
	home1->setPosition(Vec2(100, 200));
	maplayer->addChild(home1, 2, 1);


	auto home2 = Tower::createWithTowerTypes(TowerType2);
	home2->setPosition(Vec2(2200, 200));
	maplayer->addChild(home2, 2, 1001);

	this->schedule(schedule_selector(HelloWorld::updatefriend), (1.5f));
	this->schedule(schedule_selector(HelloWorld::updatefriendtower), (3.0f));
	this->schedule(schedule_selector(HelloWorld::updateenemy), (1.5f));
	this->schedule(schedule_selector(HelloWorld::updateenemytower), (3.0f));

	auto listenerkeyPad = EventListenerKeyboard::create();


	    listenerkeyPad->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys[keyCode] = true;
		/*auto W_key = cocos2d::EventKeyboard::KeyCode::KEY_W;
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
		}*/
	};
	
	listenerkeyPad->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys[keyCode] = false;
		//hero1->StopAnimation();
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
	//记分板
	auto ScoreItem = MenuItemImage::create(
		"scoreboard.png",
		"scoreboard.png",
		CC_CALLBACK_1(HelloWorld::createScoreCallBack, this)
	);
	float board_x = origin.x + ScoreItem->getContentSize().width / 2 + 10;
	float board_y = origin.y + visibleSize.height / 2 - ScoreItem->getContentSize().height / 2 - 60;
	ScoreItem->setPosition(Vec2(board_x, board_y));

	auto menu = Menu::create(ScoreItem, NULL);
	menu->setPosition(Vec2::ZERO);
	_setLayer->addChild(menu, 1);
	this->addChild(_setLayer, 5, 636);


	return true;

}


void HelloWorld::createScoreCallBack(cocos2d::Ref* pSender) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//Scoreboardbg
	_ScoreboardLayer = Layer::create();
	auto _Bg = Sprite::create("scoreboardbg.jpg");
	_Bg->setPosition(Vec2(
		visibleSize.width / 2,
		visibleSize.height / 2
	));
	//计分记录数据：
	std::string b = std::to_string((int)_plane.get_exp());
	std::string c = std::to_string((int)_plane.get_gp());
	std::string d = std::to_string((int)_plane.get_ad());

	//closebutton
	auto closeScoreButton = MenuItemImage::create(
		"closescore.png",
		"closescore.png",
		CC_CALLBACK_1(HelloWorld::closeScoreCallBack, this)
	);
	closeScoreButton->setPosition(_Bg->getPosition() + Vec2(260, 195));

	//我方战绩（包括英雄类型、击杀数、死亡数、金钱）
	auto my = Label::createWithSystemFont("MY HERO:warrior", "fonts/arial-unicode-26.fnt", 26);//间隔10字符位
	my->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 180));
	_ScoreboardLayer->addChild(my, 4);

	auto my_kill = Label::createWithSystemFont("KILL:" + b, "fonts/arial-unicode-26.fnt", 26);
	my_kill->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 150));
	_ScoreboardLayer->addChild(my_kill, 4);

	auto my_die = Label::createWithSystemFont("DIE:" + b, "fonts/arial-unicode-26.fnt", 26);
	my_die->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 120));
	_ScoreboardLayer->addChild(my_die, 4);

	auto my_money = Label::createWithSystemFont("MONEY:" + c, "fonts/arial-unicode-26.fnt", 26);
	my_money->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 90));
	_ScoreboardLayer->addChild(my_money, 4);

	auto my_ad = Label::createWithSystemFont("AD:" + d, "fonts/arial-unicode-26.fnt", 26);
	my_ad->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 60));
	_ScoreboardLayer->addChild(my_ad, 4);

	//敌方战绩（包括英雄类型、击杀数、死亡数、金钱）
	auto other = Label::createWithSystemFont("OTHER HERO:mega", "fonts/arial-unicode-26.fnt", 26);//间隔10字符位
	other->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 90));
	_ScoreboardLayer->addChild(other, 4);

	auto other_kill = Label::createWithSystemFont("KILL:" + d, "fonts/arial-unicode-26.fnt", 26);
	other_kill->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 120));
	_ScoreboardLayer->addChild(other_kill, 4);

	auto other_die = Label::createWithSystemFont("DIE:" + b, "fonts/arial-unicode-26.fnt", 26);
	other_die->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 150));
	_ScoreboardLayer->addChild(other_die, 4);

	auto other_money = Label::createWithSystemFont("MONEY:" + b, "fonts/arial-unicode-26.fnt", 26);
	other_money->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 180));
	_ScoreboardLayer->addChild(other_money, 4);


	auto mn = Menu::create(closeScoreButton, NULL);
	mn->setPosition(Vec2::ZERO);
	_ScoreboardLayer->addChild(mn, 6);
	_ScoreboardLayer->addChild(_Bg);
	_setLayer->addChild(_ScoreboardLayer, 1);
}

void HelloWorld::closeScoreCallBack(cocos2d::Ref* pSender) {
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

	if (seconds % 10 == 0)
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
		enemy4->setPosition(Vec2(1400, 200));
		maplayer->addChild(enemy4, 2, number_soider * 3 + 1001);

		auto enemy5 = Soider::createWithSoiderTypes(SoiderType1);
		enemy5->setVelocity(Vec2(-50, 0));
		enemy5->setPosition(Vec2(1500, 200));
		maplayer->addChild(enemy5, 2, number_soider * 3 + 1002);

		auto enemy6 = Soider::createWithSoiderTypes(SoiderType2);
		enemy6->setVelocity(Vec2(-50, 0));
		enemy6->setPosition(Vec2(1600, 200));
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
	exp_increase += 20;
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

		}

	}

	for (int j5 = 1001; j5 <= number_soider * 3 + 1000; j5++)
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
			be_attacked2(_plane, enemy123);
		
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
		MoveBy *moveby = MoveBy::create(0.1f, ccp(0, 2));

		ActionInterval *SineOUt = EaseSineInOut::create(moveby);

		plane->runAction(moveby);

		sprite1_position_x = plane->getPositionX();
		sprite1_position_y = plane->getPositionY() + 2;
		Vec2 sprite1_position = plane->getPosition();
		Vec2 move = scenemove(plane, _tileMap, sprite1_position);
		maplayer->setPosition(move);

	}

	if (isKeyPressed(A_key)) {
		MoveBy *moveby = MoveBy::create(0.1f, ccp(-2, 0));

		ActionInterval *SineOUt = EaseSineInOut::create(moveby);

		plane->runAction(moveby);

		sprite1_position_x = plane->getPositionX() - 2;
		sprite1_position_y = plane->getPositionY();
		Vec2 sprite1_position = plane->getPosition();
		Vec2 move = scenemove(plane, _tileMap, sprite1_position);
		maplayer->setPosition(move);

	}

	if (isKeyPressed(S_key)) {
		MoveBy *moveby = MoveBy::create(0.1f, ccp(0, -2));

		ActionInterval *SineOUt = EaseSineInOut::create(moveby);

		plane->runAction(moveby);

		sprite1_position_x = plane->getPositionX();
		sprite1_position_y = plane->getPositionY() - 2;
		Vec2 sprite1_position = plane->getPosition();
		Vec2 move = scenemove(plane, _tileMap, sprite1_position);
		maplayer->setPosition(move);
		

	}

	if (isKeyPressed(D_key)) {
		MoveBy *moveby = MoveBy::create(0.1f, ccp(2, 0));

		ActionInterval *SineOUt = EaseSineInOut::create(moveby);

		plane->runAction(moveby);
		sprite1_position_x = plane->getPositionX() + 2;
		sprite1_position_y = plane->getPositionY();
		Vec2 sprite1_position = plane->getPosition();
		Vec2 move = scenemove(plane, _tileMap, sprite1_position);
		maplayer->setPosition(move);


	}

	//log("update");
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


