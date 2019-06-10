#include "HelloWorldScene.h"

#include "SimpleAudioEngine.h"

#include "Soider.h"

#define TIMER 233
USING_NS_CC;

float sprite1_position_x;
float sprite1_position_y;
float x_touch;
float y_touch;
int countx, county;
float flytime = 1;//子弹飞行时间
int number_soider = 0;//第几波兵
int attack_distance;//攻击距离
Scene* HelloWorld::createScene()

{

	Scene *sc = Scene::create();

	Layer *ly = HelloWorld::create();

	sc->addChild(ly);

	return sc;

}


//地图随主角移动:获得主角在地图的相对位置，并设置地图位置。
Point scenemove(Sprite *plane, TMXTiledMap *_tileMap,Vec2 vPos )
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
		countx =-viewPos.x / 2;
	}
	log("%f,%f", viewPos.x, viewPos.y);
	log("%d", countx);
	return Vec2(viewPos);
}

static void problemLoading(const char* filename)

{

	printf("Error while loading: %s\n", filename);

	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
	
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
		this->addChild(enemy1, 2,number_soider*3+1);

		auto enemy2 = Soider::createWithSoiderTypes(SoiderType1);
		enemy2->setVelocity(Vec2(50, 0));
		enemy2->setPosition(Vec2(300, 200));
		enemy2->setFlipX(true);
		this->addChild(enemy2, 2, number_soider * 3 + 2);

		auto enemy3 = Soider::createWithSoiderTypes(SoiderType2);
		enemy3->setVelocity(Vec2(50, 0));
		enemy3->setPosition(Vec2(200, 200));
		enemy3->setFlipX(true);
		this->addChild(enemy3, 2, number_soider * 3 +3);

		auto enemy4 = Soider::createWithSoiderTypes(SoiderType1);
		enemy4->setVelocity(Vec2(-50, 0));
		enemy4->setPosition(Vec2(1400, 200));
		this->addChild(enemy4, 2, number_soider * 3 + 1001);

		auto enemy5 = Soider::createWithSoiderTypes(SoiderType1);
		enemy5->setVelocity(Vec2(-50, 0));
		enemy5->setPosition(Vec2(1500, 200));
		this->addChild(enemy5, 2, number_soider * 3 + 1002);

		auto enemy6 = Soider::createWithSoiderTypes(SoiderType2);
		enemy6->setVelocity(Vec2(-50, 0));
		enemy6->setPosition(Vec2(1600, 200));
		this->addChild(enemy6, 2, number_soider * 3 + 1003);

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


bool HelloWorld::init()

{


		if (!Layer::init())

		{

			return false;

		}



		

	auto visibleSize = Director::getInstance()->getVisibleSize();
   Vec2 origin = Director::getInstance()->getVisibleOrigin();

   
   this->schedule(schedule_selector(HelloWorld::updateenemy), (1.0f));
   this->schedule(schedule_selector(HelloWorld::updatefriend), (1.0f));

	_tileMap = TMXTiledMap::create("bg_tiledMap.tmx");
	_tileMap->setPosition(Vec2(origin.x,
		origin.y));
	_tileMap->setAnchorPoint(Vec2(0, 0));
	addChild(_tileMap, -1, 100);
	

	TMXObjectGroup *objG = _tileMap->getObjectGroup("Object1");
	auto object = objG->getObject("PlayerBorn");
	float a = object["x"].asFloat();
	float b = object["y"].asFloat();

	
	plane = Sprite::create("plane.png");
	this->addChild(plane, 2,131);
	plane->setPosition(Vec2(a+100, b+40));
	plane->setAnchorPoint(Vec2(1.0, 0.5));
	
     sprite2 = Sprite::create("plane1.png");
	this->addChild(sprite2, 2,133);
	sprite2->setPosition(Vec2(a+500, b+40));

	time = 0;
	auto timelabel = Label::createWithTTF("00:00", "fonts/Marker Felt.ttf", 30);
	timelabel->setPosition(Vec2(origin.x + visibleSize.width - timelabel->getContentSize().width,
		origin.y + visibleSize.height - timelabel->getContentSize().height));
	this->addChild(timelabel, 2, TIMER);

	this->schedule(schedule_selector(HelloWorld::updatetime), 1.0f);
	
	

	auto listenerkeyPad = EventListenerKeyboard::create();


	
	listenerkeyPad->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys[keyCode] = true;
		log("key pressed");
	};
	
	listenerkeyPad->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		keys[keyCode] = false;
		log("key released");
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);


	
	this->scheduleUpdate();


	auto myListener = EventListenerTouchOneByOne::create();
	myListener->setSwallowTouches(true);
	myListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::touchBegan, this);  
	myListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::touchMoved, this);
	myListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::touchEnded, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myListener, this);
	
	//scenemove(mapTild, plane, _tileMap);
	
		
	

	return true;

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
bool isinbound(Vec2 position, Vec2 touchposition,Vec2 size) {
	if(touchposition.x<=position.x+size.x/2&& touchposition.x >= position.x - size.x / 2&&
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


/*
void HelloWorld::myupdate(float dt)
{
	CCSprite* sp1 = (CCSprite*)this->getChildByTag(101); //获取 tag=101 的精灵
	sp1->setPosition(sp1->getPosition() + ccp(1, 0)); 
	CCSprite* sp2 = (CCSprite*)this->getChildByTag(102); //获取 tag=101 的精灵
	sp2->setPosition(sp2->getPosition() + ccp(1, 0));   //每帧移动1
	CCSprite* sp3 = (CCSprite*)this->getChildByTag(103); //获取 tag=101 的精灵
	sp3->setPosition(sp3->getPosition() + ccp(1, 0));   //每帧移动1
}*/



void HelloWorld::updatefriend(float dt)//实现友方AI
{
	for (int i1 = 1;i1 <= number_soider * 3;i1++)
	{
		Soider* friendsoider = (Soider*)this->getChildByTag(i1);
		for (int j1 = 1001;j1 <= number_soider * 3 + 1000;j1++)
		{
			Soider* enemysoider = (Soider*)this->getChildByTag(j1);
			if (i1 % 3)
				attack_distance = 200;
			else
				attack_distance = 500;
			if (ccpDistance(friendsoider->getPosition(), enemysoider->getPosition()) <= attack_distance)
			{
				friendsoider->setVelocity(Vec2(0, 0));
				auto bullet2 = Sprite::create("CloseSelected.png");
				this->addChild(bullet2, 2);
				bullet2->setPosition(friendsoider->getPosition());
				CCPoint attck_point = Vec2(enemysoider->getPosition().x, enemysoider->getPosition().y);
				auto actionMove1 = CCMoveTo::create(flytime, attck_point);
				auto actionMovehide1 = CCHide::create();

				Sequence* sequence1 = Sequence::create(actionMove1, actionMovehide1, NULL);
				bullet2->runAction(sequence1);
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
	for (int i2 = 1001;i2 <= number_soider * 3+1000;i2++)
	{
		Soider* enemysoider1 = (Soider*)this->getChildByTag(i2);
		for (int j2 = 1;j2 <= number_soider * 3 ;j2++)
		{
			Soider* friendsoider1 = (Soider*)this->getChildByTag(j2);
			if ((i2-1000) % 3)
				attack_distance = 200;
			else
				attack_distance = 500;
			if (ccpDistance(enemysoider1->getPosition(), friendsoider1->getPosition()) <= attack_distance)
			{
				enemysoider1->setVelocity(Vec2(0, 0));
				auto bullet3 = Sprite::create("CloseSelected.png");
				this->addChild(bullet3, 2);
				bullet3->setPosition(enemysoider1->getPosition());
				CCPoint attck_point = Vec2(friendsoider1->getPosition().x, friendsoider1->getPosition().y);
				auto actionMove2 = CCMoveTo::create(flytime, attck_point);
				auto actionMovehide2 = CCHide::create();

				Sequence* sequence2 = Sequence::create(actionMove2, actionMovehide2, NULL);
				bullet3->runAction(sequence2);
				break;
			}
			else
			{
				enemysoider1->setVelocity(Vec2(-50, 0));
			}
		}
	}
}
bool HelloWorld::touchBegan(Touch *touch, Event* event)
{
	x_touch = touch->getLocation().x + countx * 2;
	y_touch = touch->getLocation().y;
	Vec2 touchposition = Vec2(x_touch, y_touch);
	Vec2 sprite2_position = sprite2->getPosition();
	log("%f,%f", sprite2_position.x, sprite2_position.y);
	Vec2 sprite2_size = sprite2->getContentSize();
	log("%f,%f", touchposition.x, touchposition.y);
	log("%f,%f", sprite2_size.x, sprite2_size.y);
	if (isinbound(sprite2_position, touchposition, sprite2_size)) {
		log("6666");
		
		auto bullet1 = Sprite::create("CloseNormal.png");
		this->addChild(bullet1,2);

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


	}

	/*auto bullet = Sprite::create("CloseNormal.png");
	  CCSize size = CCDirector::sharedDirector()->getWinSize();

	this->addChild(bullet);

	bullet->setPosition(ccp(sprite1_position_x, sprite1_position_y));//设置子弹的发射位置 

	const int OUT_OF_WORLD = 2000;

	CCPoint ptOutOfWorld = calculate(sprite1_position_x, sprite1_position_y, x_touch, y_touch, OUT_OF_WORLD, OUT_OF_WORLD);//获取屏幕外的一个点

	CCAction*pAction = CCMoveTo::create(2.0f, ptOutOfWorld);

	bullet ->runAction(pAction);//发射子弹*/

	return true;

};









void HelloWorld::touchMoved(Touch *touch, Event* event)
{
	 x_touch = touch->getLocation().x + countx * 2;
	 y_touch = touch->getLocation().y;
	 log("%f,%f", x_touch, y_touch);

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

	this->addChild(bullet);

	bullet->setPosition(ccp(sprite1_position_x, sprite1_position_y));//设置子弹的发射位置 

	const int OUT_OF_WORLD = 6000;

	
	CCPoint ptOutOfWorld = calculate(sprite1_position_x, sprite1_position_y, x_touch, y_touch, OUT_OF_WORLD, OUT_OF_WORLD);//获取屏幕外的一个点
	

	CCAction*pAction = CCMoveTo::create(2.0f, ptOutOfWorld);

	bullet->runAction(pAction);//发射子弹


	if (isCircleCollision(bullet->getPosition(), bullet->getContentSize().width / 2, enemy->getPosition(), enemy->getContentSize().width / 2))
	{
		log("666");
		
	}
	
	else
		log("No 666");

	
};


void HelloWorld::touchEnded(Touch *touch, Event* event)
{
	log("2");
	
};


 /*void HelloWorld::update(float dt)
{
	
	CCMoveBy *moveby = CCMoveBy::create(0.1f, ccp(2, 0));

	CCActionInterval *SineOUt = CCEaseSineInOut::create(moveby);
	sprite1_position_x = plane->getPositionX() + 20;
	sprite1_position_y = plane->getPositionY();
	plane->runAction(moveby);
	Vec2 sprite1_position = plane->getPosition();
	Vec2 move = scenemove(plane, _tileMap, sprite1_position);
	this->setPosition(move);
}*/

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
		this->setPosition(move);
	}

	if (isKeyPressed(A_key)) {
		MoveBy *moveby = MoveBy::create(0.1f, ccp(-2, 0));

		ActionInterval *SineOUt = EaseSineInOut::create(moveby);

		plane->runAction(moveby);

		sprite1_position_x = plane->getPositionX() - 2;
		sprite1_position_y = plane->getPositionY();
		Vec2 sprite1_position = plane->getPosition();
		Vec2 move = scenemove(plane, _tileMap, sprite1_position);
		this->setPosition(move);
	}

	if (isKeyPressed(S_key)) {
		MoveBy *moveby = MoveBy::create(0.1f, ccp(0, -2));

		ActionInterval *SineOUt = EaseSineInOut::create(moveby);

		plane->runAction(moveby);

		sprite1_position_x = plane->getPositionX();
		sprite1_position_y = plane->getPositionY() - 2;
		Vec2 sprite1_position = plane->getPosition();
		Vec2 move = scenemove(plane, _tileMap, sprite1_position);
		this->setPosition(move);
	}

	if (isKeyPressed(D_key)) {
		MoveBy *moveby = MoveBy::create(0.1f, ccp(2, 0));

		ActionInterval *SineOUt = EaseSineInOut::create(moveby);

		plane->runAction(moveby);
		sprite1_position_x = plane->getPositionX() + 2;
		sprite1_position_y = plane->getPositionY();
		Vec2 sprite1_position = plane->getPosition();
		Vec2 move = scenemove(plane, _tileMap, sprite1_position);
		this->setPosition(move);
	}

	//log("update");
}

/*void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {

	switch (keyCode) {

	case cocos2d::EventKeyboard::KeyCode::KEY_W: {

		this->scheduleUpdate();
	
		CCMoveBy *moveby = CCMoveBy::create(0.1f, ccp(0, 20));

		CCActionInterval *SineOUt = CCEaseSineInOut::create(moveby);
	
		plane->runAction(moveby);
		sprite1_position_x = plane->getPositionX();
		sprite1_position_y = plane->getPositionY()+20;
		Vec2 sprite1_position = plane->getPosition();
		log("%f,%f", sprite1_position_x, sprite1_position_y);
		Vec2 move=scenemove(plane, _tileMap, sprite1_position);
		this->setPosition(move);
		break;

	}

	case cocos2d::EventKeyboard::KeyCode::KEY_S: {
		
		CCMoveBy *moveby = CCMoveBy::create(0.1f, ccp(0, -20));

		CCActionInterval *SineOUt = CCEaseSineInOut::create(moveby);
		
		plane->runAction(moveby);
		sprite1_position_x = plane->getPositionX();
		sprite1_position_y = plane->getPositionY()-20;
	
		Vec2 sprite1_position = plane->getPosition();
		log("%f,%f", sprite1_position_x, sprite1_position_y);
		Vec2 move = scenemove(plane, _tileMap, sprite1_position);
		this->setPosition(move);
		break;

	}

	case cocos2d::EventKeyboard::KeyCode::KEY_A: {
		
		CCMoveBy *moveby = CCMoveBy::create(0.1f, ccp(-20, 0));

		CCActionInterval *SineOUt = CCEaseSineInOut::create(moveby);
		sprite1_position_x = plane->getPositionX()-20;
		sprite1_position_y = plane->getPositionY();
		plane->runAction(moveby);

	
		Vec2 sprite1_position = plane->getPosition();
		Vec2 move = scenemove(plane, _tileMap, sprite1_position);
		this->setPosition(move);
	

		break;

	}

	case cocos2d::EventKeyboard::KeyCode::KEY_D: {
		
		
			this->scheduleUpdate();
		
		CCMoveBy *moveby = CCMoveBy::create(0.1f, ccp(20, 0));

		CCActionInterval *SineOUt = CCEaseSineInOut::create(moveby);
		sprite1_position_x = plane->getPositionX()+20;
		sprite1_position_y = plane->getPositionY();
		plane->runAction(moveby);
		 
		
		 Vec2 sprite1_position = plane->getPosition();
		 Vec2 move = scenemove(plane, _tileMap, sprite1_position);
		 this->setPosition(move);
		
		break;

	}
	default:
		break;

	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
	switch (keyCode) {
	case cocos2d::EventKeyboard::KeyCode::KEY_D: {
		
		
	}
	}
}*/




void HelloWorld::menuCloseCallback(Ref* pSender)

{

	Director::getInstance()->end();



#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

	exit(0);

#endif

}


