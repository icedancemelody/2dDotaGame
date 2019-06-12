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
		animation->addSpriteFrameWithFileName(szName); //���ض�����֡  
	}
	animation->setDelayPerUnit(0.1f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(-1); //����ѭ��
	if (HeroDirecton != run_directon){
		HeroDirecton = run_directon;
	}
	//��������װ��һ������
	CCAnimate* act = CCAnimate::create(animation);
	m_HeroSprite->runAction(act);
	IsRunning = true;
}

void Hero::StopAnimation(){
	if(!IsRunning) return;
	m_HeroSprite->stopAllActions();//��ǰ����ֹͣ���ж���

	//�ָ�����ԭ���ĳ�ʼ����ͼ 
	this->removeChild(m_HeroSprite, TRUE);//��ԭ���ľ���ɾ����
	m_HeroSprite = CCSprite::create(Hero_name);//�ָ�����ԭ������ͼ����
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
		animation->addSpriteFrameWithFileName(szName); //���ض�����֡  
	}
	animation->setDelayPerUnit(0.05f);
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(1); //����ѭ��1��
	if (HeroDirecton != run_directon){
		HeroDirecton = run_directon;
	}
	//��������װ��һ������
	CCAnimate* act = CCAnimate::create(animation);
	// �����ص��������������������AttackEnd()
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Hero::AttackEnd));
	//������������
	CCActionInterval* attackact = CCSequence::create(act, callFunc, NULL);
	m_HeroSprite->runAction(attackact);
}

void Hero::AttackEnd(){
	//�ָ�����ԭ���ĳ�ʼ����ͼ 
	this->removeChild(m_HeroSprite, TRUE);//��ԭ���ľ���ɾ����
	m_HeroSprite = CCSprite::create(Hero_name);//�ָ�����ԭ������ͼ����
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
