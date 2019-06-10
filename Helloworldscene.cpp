
#include "HelloWorldScene.h"

#include "SimpleAudioEngine.h"
#include "people.h"
#include "tower.h"
#include "equipment.h"
#define TIMER 233

USING_NS_CC;


float sprite1_position_x;
float sprite1_position_y;
float x_touch;
float y_touch;
int countx, county;
int xiaobing_tag1=1000, xiaobing_tag2=1100, xiaobing_tag3=1210;


Scene* HelloWorld::createScene()

{

	Scene *sc = Scene::create();

	Layer *ly = HelloWorld::create();

	sc->addChild(ly);

	return sc;

}


//����һ���Լ����������ƶ��ĵ���
void enemytick(Sprite *enemy)
{
	int enemymovetick = 0;
	Point enemypoint = enemy->getPosition();
	if (enemymovetick >= 0 && enemymovetick <= 20) {
		enemymovetick++;
		enemypoint.x += 2;
	}
	else if (enemymovetick > 20 && enemymovetick <= 60)
	{
		enemymovetick++;
		enemypoint.x -= 2;

	}
	else if (enemymovetick > 60 && enemymovetick <= 80)
	{
		enemymovetick++;
		enemypoint.x += 2;

	}
	else if (enemymovetick > 80)
	{
		enemymovetick = 0;


	}
	enemy->setPosition(enemypoint);

}

//��ͼ�������ƶ�:��������ڵ�ͼ�����λ�ã������õ�ͼλ�á�
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


void HelloWorld::updatetime(float dt) {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->getChildByTag(TIMER)->removeFromParent();
	time++;
	
	int minutes = time / 60;
	int seconds = time - minutes * 60;
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
	_tileMap->addChild(plane, 2,103);
	plane->setPosition(Vec2(a+100, b+40));
	plane->setAnchorPoint(Vec2(1.0, 0.5));
	
	hero plane(100, 100, 100, 100, 100, 100, 100, 100, 100, 100,0,0);
	
	log("%f", plane.get_blood());
	
	sprite2 = Sprite::create("plane1.png");
	this->addChild(sprite2, 4);

	sprite2->setPosition(Vec2(a+1000, b+40));
	hero sprite2(10, 10, 10, 10, 10, 10, 10, 10, 10, 10,0,0);
	log("%f", sprite2.get_blood());

			   	
	
	//��ʼ������
	auto enemy = Sprite::create("CloseSelected.png");
	Size winSize = Director::getInstance()->getVisibleSize();
	int enemymovetick = 0;

	if (enemy == nullptr)

	{

		problemLoading("'CloseSelected.png'");

	}

	else

	{

		enemy->setPosition(Point(80,32));
		enemy->setAnchorPoint(Point(0.5f, 0));
		
		this->addChild(enemy, 0);
	
		

	}
	enemytick(enemy);//û�гɹ�ʵ��

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
	
	
	
	time = 0;
	auto timelabel = Label::createWithTTF("00:00", "fonts/Marker Felt.ttf", 30);
	timelabel->setPosition(Vec2(origin.x + visibleSize.width - timelabel->getContentSize().width,
		origin.y + visibleSize.height - timelabel->getContentSize().height));
	this->addChild(timelabel, 2, TIMER);
	
	this->schedule(schedule_selector(HelloWorld::updatetime), 1.0f);
	
	return true;


}



/*
//��ͼ��ײ���
void playermaphcollision(Sprite *gameplayer)
{
	Point playerpoint = gameplayer->getPosition();
	Size playersize = gameplayer->getContentSize();
	TMXTiledMap* map = (TMXTiledMap*)getChildByTag(kTagTileMap);//��ͼ����kTagTileMap
	int indexx, indexy;
	char mch[256];
	TMXLayer* layer = map->getLayer("logic");

	//����ͼ�ؿ飺for()
	

	//�������ұ߽磺

	uo

	//�����ײ ��������λ�ã�setPosition())



}
//��ֱ����
void playermaphcollision(Sprite *gameplayer)
{
}

//���º���update:
void update(float dt,Sprite *gameplayer)
{
playermaphcollision();
playermaphcollision();

//��������λ��
Point playerpoint1=gameplayer->getPosition();
playerpoint.y+=vmove;
playerpoint.x+=1*hmove;
enemytick();
gameplayer->setPosition(playerpoint);

��ͼ�������ƶ�:��������ڵ�ͼ�����λ�ã������õ�ͼλ�á�




*/





//�жϾ����뾫��֮�����ײ
bool isCircleCollision(Point pos1, float radius1, Point pos2, float radius2)
{
	//���ù��ɶ����ж���Բ�Ƿ��ཻ
	if (sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2)) > pow(radius1 + radius2, 2))
	{
		return false;
	}
	return true;
}
//�жϵ��λ���Ƿ��о���
bool isinbound(Vec2 position, Vec2 touchposition,Vec2 size) {
	if(touchposition.x<=position.x+size.x/2&& touchposition.x >= position.x - size.x / 2&&
		touchposition.y <= position.y + size.y / 2 && touchposition.y >= position.y - size.y / 2)
	{
		return true;
	}
	return false;
}

void HelloWorld::myupdate(float dt)
{
	CCSprite* sp1 = (CCSprite*)this->getChildByTag(xiaobing_tag1); 
	//��ȡ tag=101 �ľ���
	sp1->setPosition(sp1->getPosition() + ccp(1, 0));
	

	CCSprite* sp2 = (CCSprite*)this->getChildByTag(xiaobing_tag2);
	//��ȡ tag=101 �ľ���
	sp2->setPosition(sp2->getPosition() + ccp(1, 0)); 
	//ÿ֡�ƶ�1
	
	CCSprite* sp3 = (CCSprite*)this->getChildByTag(xiaobing_tag3); //��ȡ tag=101 �ľ���
	sp3->setPosition(sp3->getPosition() + ccp(1, 0));
	//ÿ֡�ƶ�1
	
}



Point calculate(float x1, float y1, float x2, float y2, float nXOutOfWorld, float nYOutOfWorld)
{
	float fK = 1.0;

	float fb = 0.0;

if (x1 != x2)

{

	fK = (float)(y2 - y1) / (x2 - x1);//���K

}

fb = y2 - x2 * fK;//���b

//���ֱ������Ļ��ĵ�

CCSize size = CCDirector::sharedDirector()->getWinSize();

float fY = y1 > y2 ? -nYOutOfWorld : size.height + nYOutOfWorld;

float fX = 1.0;

if (fK != 0)

{

	fX = (fY - fb) / fK;//���fX���ܷǳ��󣬻��߷ǳ�С

}

if (x1 == x2)//Ӧ����Y���˶�

{

	fX = x1;

	fY = y1 > y2 ? -nXOutOfWorld : size.height + nYOutOfWorld;

}

else if (y2 == y1)//Ӧ����X���˶�

{

	fX = x1 > x2 ? -nXOutOfWorld : size.width + nXOutOfWorld;

	fY = y1;

}

else if (fX > size.width + nXOutOfWorld)//���¼���fX��fY

{

	fX = size.width + nXOutOfWorld;

	fY = fK * fX + fb;

}

else if (fX < -nXOutOfWorld)//���¼���fX��fY

{

	fX = -nXOutOfWorld;

	fY = fK * fX + fb;

}

return ccp(fX, fY);
}


void hero::be_attacked_by(hero other) {
	_blood = _blood-(other.get_ad() - _hujia);
	log("%f,%f,%f", _blood, other.get_ad(), _hujia);
	
}

float hero::exp_up(hero other)
{
	_exp = _exp + other.get_exp();
	return _exp;
}



hero _plane(100, 100, 100, 100, 100, 100, 100, 100, 100, 100,0,0);
hero _sprite2(100, 10, 10, 10, 80, 10, 10, 10, 10, 10,1000,0);
// �����¼���update  ��ʱ����ûд��



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
		this->addChild(bullet1,0);
	    bullet1->setPosition(ccp(sprite1_position_x, sprite1_position_y));
		//����
		auto xiaobing1 = Sprite::create("boss.png");
		this->addChild(xiaobing1, 1, xiaobing_tag1);
		xiaobing1->setScale(0.3);

		auto xiaobing2 = Sprite::create("boss.png");
		this->addChild(xiaobing2, 1, xiaobing_tag2);
		xiaobing2->setScale(0.3);

		auto xiaobing3 = Sprite::create("boss.png");
		this->addChild(xiaobing3, 1, xiaobing_tag3);
		xiaobing3->setScale(0.3);

		xiaobing1->setPosition(ccp(300, 200));
		xiaobing2->setPosition(ccp(200, 200));
		xiaobing3->setPosition(ccp(100, 200));
		this->schedule(schedule_selector(HelloWorld::myupdate));
		



		CCPoint ptOutOfWorld1 = Vec2(x_touch, y_touch);
		float v = 3000.000000;
		//��˵�еĶ�ʱ��
		//this->scheduleUpdate();
		//this->myupdate(x_touch - sprite1_position_x, y_touch - sprite1_position_y, bullet1);
	
		
		float time = sqrt((x_touch - sprite1_position_x)*(x_touch - sprite1_position_x) + (y_touch - sprite1_position_y)*(y_touch - sprite1_position_y)) / v;
		auto actionMove = CCMoveTo::create(time, ptOutOfWorld1);
		auto actionMovehide = CCHide::create();

		
		Sequence* sequence = Sequence::create(actionMove, actionMovehide, NULL);
		bullet1->runAction(sequence);//�����ӵ�

		//�ӵ��뾫����ײ�����ӵ�
		if (bullet1->boundingBox().intersectsRect(sprite2->boundingBox()))
		{
			bullet1->setScale(2.0);
		};

	

		_sprite2.be_attacked_by(_plane);
	
		log("%f", _sprite2.get_blood());
		if (_sprite2.get_blood() <= 0) {
		

			sprite2->setVisible(false);
			int x = _plane.exp_up(_sprite2);
			_plane.judge_level_up(x);

		

		}

		

	}

	/*auto bullet = Sprite::create("CloseNormal.png");
	  CCSize size = CCDirector::sharedDirector()->getWinSize();

	this->addChild(bullet);

	bullet->setPosition(ccp(sprite1_position_x, sprite1_position_y));//�����ӵ��ķ���λ�� 

	const int OUT_OF_WORLD = 2000;

	CCPoint ptOutOfWorld = calculate(sprite1_position_x, sprite1_position_y, x_touch, y_touch, OUT_OF_WORLD, OUT_OF_WORLD);//��ȡ��Ļ���һ����

	CCAction*pAction = CCMoveTo::create(2.0f, ptOutOfWorld);

	bullet ->runAction(pAction);//�����ӵ�*/

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

	bullet->setPosition(ccp(sprite1_position_x, sprite1_position_y));//�����ӵ��ķ���λ�� 

	const int OUT_OF_WORLD = 6000;

	
	CCPoint ptOutOfWorld = calculate(sprite1_position_x, sprite1_position_y, x_touch, y_touch, OUT_OF_WORLD, OUT_OF_WORLD);//��ȡ��Ļ���һ����
	

	CCAction*pAction = CCMoveTo::create(2.0f, ptOutOfWorld);

	bullet->runAction(pAction);//�����ӵ�


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


