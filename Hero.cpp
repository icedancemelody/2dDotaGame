#include "Hero.h"



Hero::Hero() :
	IsRunning(false),
	IsAttack(false),
	Hero_name(NULL),
	HeroDirecton(false)
{
}

Hero::Hero(HeroTypes heroType) {
	this->heroType = heroType;
}


Hero::~Hero()
{
}

void Hero::InitHeroSprite(char * hero_name) {
	Hero_name = hero_name;
	this->m_HeroSprite = CCSprite::create(hero_name);
	//this->m_HeroSprite->initWithFile(hero_name);
	this->addChild(m_HeroSprite);

}

void Hero::SetAnimation(const char * name_each, const unsigned int num, bool run_directon) {
	if (HeroDirecton != run_directon)
	{
		HeroDirecton = run_directon;
		m_HeroSprite->setFlipX(run_directon);
	}
	if (IsRunning) return;
	CCAnimation* animation = CCAnimation::create();

	for (int i = 1; i <= num; i++) {
		char szName[100] = { 0 };
		sprintf(szName, "%s%d.png", name_each, i);
		animation->addSpriteFrameWithFileName(szName); //加载动画的帧  
	}
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1); //动画循环
	if (HeroDirecton != run_directon) {
		HeroDirecton = run_directon;
	}
	//将动画包装成一个动作
	CCAnimate* act = CCAnimate::create(animation);
	m_HeroSprite->runAction(act);
	IsRunning = false;
}

void Hero::StopAnimation() {
	//if (!IsRunning) return;
	m_HeroSprite->stopAllActions();//当前精灵停止所有动画

	//恢复精灵原来的初始化贴图 
	this->removeChild(m_HeroSprite, TRUE);//把原来的精灵删除掉
	m_HeroSprite = CCSprite::create(Hero_name);//恢复精灵原来的贴图样子
	m_HeroSprite->setFlipX(HeroDirecton);

	this->addChild(m_HeroSprite);
	//IsRunning = false;
}

void Hero::AttackAnimation(const char * name_each, const unsigned int num, bool run_directon) {
	if (IsAttack) return;
	IsAttack = true;
	CCAnimation* animation = CCAnimation::create();
	for (int i = 1; i <= num; i++) {
		char szName[100] = { 0 };
		sprintf(szName, "%s%d.png", name_each, i);
		animation->addSpriteFrameWithFileName(szName); //加载动画的帧  
	}
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1); //动画循环1次
	if (HeroDirecton != run_directon) {
		HeroDirecton = run_directon;
	}
	//将动画包装成一个动作
	CCAnimate* act = CCAnimate::create(animation);
	// 创建回调动作，攻击结束后调用AttackEnd()
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Hero::AttackEnd));
	//创建连续动作
	CCActionInterval* attackact = CCSequence::create(act, callFunc, NULL);
	m_HeroSprite->runAction(attackact);
}

void Hero::AttackEnd() {
	//恢复精灵原来的初始化贴图 
	this->removeChild(m_HeroSprite, TRUE);//把原来的精灵删除掉
	m_HeroSprite = CCSprite::create(Hero_name);//恢复精灵原来的贴图样子
	if (m_HeroSprite == nullptr) {
		log("创建失败");
		return;
	}
	m_HeroSprite->setFlipX(HeroDirecton);
	this->addChild(m_HeroSprite);
	IsAttack = false;
}




Hero * Hero::createWithHeroTypes(HeroTypes heroType)
{
	Hero*hero = new Hero(heroType);
	char*heroFramName;
	switch (heroType) {
	case HeroType1:
		heroFramName = "Male_shooter_stand_1.png";
		hero->maxblood = 1000;
		break;
	case HeroType2:
		heroFramName = "boss.png";
		hero->maxblood = 1000;
		break;
	case HeroType3:
		heroFramName = "boss.png";
		hero->maxblood = 1000;
		break;
	}
	//soider->initWithSpriteFrameName(soiderFramName);
	hero->InitHeroSprite(heroFramName);
	hero->autorelease();
	hero->unscheduleUpdate();
	hero->scheduleUpdate();

	return hero;
}

Hero * Hero::create(const char * filename)
{
	return nullptr;
}

void Hero::update(float dt) {
	switch (heroType) {
	case HeroType1:
		//this->setRotation(this->getRotation() - 0.5);
		break;
	case HeroType2:
		//this->setRotation(this->getRotation() + 1);
		break;
	case HeroType3:
		break;
	}
	//Vec2 moveLen = velocity * dt;

	//this->setPosition(this->getPosition() + moveLen);

}




void Hero::skill_1(Hero *hero1, Layer *maplayer)
{

	auto spr_1 = Sprite::create("1224.png");
	spr_1->setScale(1.5f);
	maplayer->addChild(spr_1, 2);
	spr_1->setPosition(Vec2(hero1->getPosition()));
	auto actionMove1 = CCMoveBy::create(2000.0f, Vec2(hero1->getPositionX() + 100, 0) * 1000);
	spr_1->runAction(actionMove1);
}


void Hero::skill_2(Hero *hero1, Layer *maplayer) {
	auto spr_2 = Sprite::create("skill2.png");
	hero1->addChild(spr_2, 4,2000);
	spr_2->setPosition(Vec2(hero1->getContentSize().width / 2, hero1->getContentSize().height));

}

void Hero::skill_3(Hero *hero1, Layer *maplayer) {

	auto spr_3 = Sprite::create("skill3.png");
	hero1->addChild(spr_3, 4, 1999);
	spr_3->setPosition(Vec2(hero1->getContentSize().width / 2, hero1->getContentSize().height));
}

void Hero::skill_4(Hero *hero1, Layer *maplayer)
{

	auto spr_1 = Sprite::create("1224.png");
	maplayer->addChild(spr_1, 2);
	spr_1->setPosition(Vec2(hero1->getPosition()));
	auto actionMove1 = CCMoveBy::create(2000.0f, Vec2(hero1->getPositionX() + 100, 0) * 1000);
	spr_1->runAction(actionMove1);
}


void Hero::skill_5(Hero *hero1, Layer *maplayer) {
	auto spr_2 = Sprite::create("skill5.png");
	hero1->addChild(spr_2, 4, 2001);
	spr_2->setPosition(Vec2(hero1->getContentSize().width / 2, hero1->getContentSize().height));

}

void Hero::skill_6(Hero *hero1, Layer *maplayer) {
	auto spr_1 = Sprite::create("skill6.png");
	spr_1->setScale(3.0f);
	maplayer->addChild(spr_1, 2);
	spr_1->setPosition(Vec2(hero1->getPosition()));
	auto actionMove1 = CCMoveBy::create(2000.0f, Vec2(hero1->getPositionX() + 100, 0) * 1000);
	spr_1->runAction(actionMove1);

}
void Hero::skill_7(Hero *hero1, Layer *maplayer)
{

	auto spr_7 = Sprite::create("1021.png");
	auto spr_72 = Sprite::create("1021.png");
	hero1->addChild(spr_7, 2, 2003);
	hero1->addChild(spr_72, 2, 2004);
	spr_7->setPosition(Vec2(hero1->getContentSize().width / 2, hero1->getContentSize().height));
	spr_72->setPosition(Vec2(hero1->getContentSize().width / 2, hero1->getContentSize().height));
	auto actionMove1 = CCMoveBy::create(1.0f, Vec2(200, 0));
	auto actionMove2 = CCMoveBy::create(1.0f, Vec2(-200, 0));
	CCAnimation* animation = CCAnimation::create();

	for (int i = 1; i <= 2; i++) {
		char szName[100] = { 0 };
		sprintf(szName, "Female_mage_%d_skill.png", i);
		animation->addSpriteFrameWithFileName(szName); //加载动画的帧  
	}
	animation->setDelayPerUnit(0.2f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1); //动画循环
	//将动画包装成一个动作
	CCAnimate* act = CCAnimate::create(animation);
	m_HeroSprite->runAction(act);
	spr_7->runAction(actionMove1);
	spr_72->runAction(actionMove2);
}


void Hero::skill_8(Hero *hero1, Layer *maplayer) {
	auto spr_2 = Sprite::create("1004.png");
	hero1->addChild(spr_2, 4, 2005);
	spr_2->setPosition(Vec2(hero1->getContentSize().width / 2, hero1->getContentSize().height));

}

void Hero::skill_9(Hero *hero1, Layer *maplayer) {

	auto spr_9 = Sprite::create();
	maplayer->addChild(spr_9, 2);
	spr_9->setScale(8.0f);
	spr_9->setPosition(Vec2(hero1->getPosition()));
	CCAnimation* animation = CCAnimation::create();
	for (int i = 1; i <= 4; i++) {
		char szName[100] = { 0 };
		sprintf(szName, "%s%d.png", "skill_9_", i);
		animation->addSpriteFrameWithFile(szName); //加载动画的帧  
	}
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1);

	//将动画包装成一个动作
	CCAnimate* act = CCAnimate::create(animation);
	CCAnimation* animation1 = CCAnimation::create();

	for (int i = 1; i <= 2; i++) {
		char szName[100] = { 0 };
		sprintf(szName, "Female_mage_%d_skill.png", i);
		animation1->addSpriteFrameWithFileName(szName); //加载动画的帧  
	}
	animation1->setDelayPerUnit(0.4f);
	animation1->setRestoreOriginalFrame(true);
	animation1->setLoops(1); //动画循环
	//将动画包装成一个动作
	CCAnimate* act1 = CCAnimate::create(animation1);
	m_HeroSprite->runAction(act1);
	spr_9->runAction(act);
}
