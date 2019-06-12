#include "Hero.h"



Hero::Hero(){
}

Hero::Hero(HeroTypes heroType){
	this->heroType = heroType;
}


Hero::~Hero()
{
}

 void Hero::InitHeroSprite(char * hero_name){
	Hero_name = hero_name;
	this->m_HeroSprite = CCSprite::create(hero_name);
	this->addChild(m_HeroSprite);
	
}

void Hero::SetAnimation(const char * name_each, const unsigned int num, bool run_directon){
	if (HeroDirecton != run_directon)
	{
		HeroDirecton = run_directon;
		m_HeroSprite->setFlipX(run_directon);
	}
	if (IsRunning) return;
	CCAnimation* animation = CCAnimation::create();

	for (int i = 1; i <= num; i++){
		char szName[100] = { 0 };
		sprintf(szName, "%s%d.png", name_each, i);
		animation->addSpriteFrameWithFileName(szName); //加载动画的帧  
	}
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1); //动画循环
	if (HeroDirecton != run_directon){
		HeroDirecton = run_directon;
	}
	//将动画包装成一个动作
	CCAnimate* act = CCAnimate::create(animation);
	m_HeroSprite->runAction(act);
	IsRunning = true;
}

void Hero::StopAnimation(){
	if(!IsRunning) return;
	m_HeroSprite->stopAllActions();//当前精灵停止所有动画

	//恢复精灵原来的初始化贴图 
	this->removeChild(m_HeroSprite, TRUE);//把原来的精灵删除掉
	m_HeroSprite = CCSprite::create(Hero_name);//恢复精灵原来的贴图样子
	m_HeroSprite->setFlipX(HeroDirecton);

	this->addChild(m_HeroSprite);
	IsRunning = false;
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
	animation->setDelayPerUnit(0.05f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1); //动画循环1次
	if (HeroDirecton != run_directon){
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

void Hero::AttackEnd(){
	//恢复精灵原来的初始化贴图 
	this->removeChild(m_HeroSprite, TRUE);//把原来的精灵删除掉
	m_HeroSprite = CCSprite::create(Hero_name);//恢复精灵原来的贴图样子
	m_HeroSprite->setFlipX(HeroDirecton);
	this->addChild(m_HeroSprite);
	IsAttack = false;
}




Hero * Hero::createWithHeroTypes(HeroTypes heroType)
{
	Hero*hero = new Hero(heroType);
	const char*heroFramName;
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
	//hero->initWithFile(heroFramName);
	hero->autorelease();
	hero->unscheduleUpdate();
	hero->scheduleUpdate();

	return hero;
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
