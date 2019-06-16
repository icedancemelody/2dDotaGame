#include "Soider.h"

Soider::Soider() {

}


Soider::Soider(SoiderTypes soiderType)
{
	this->soiderType = soiderType;
	this->velocity = Vec2(2, 2);//设置小兵x方向和y方向速度
	switch (soiderType) {
	case SoiderType1:
		setAd(60);
		setHujia(50);
		setVal(20);
		setExp(40);
	case SoiderType2:
		setAd(60);
		setHujia(50);
		setVal(15);
		setExp(50);
	case SoiderType3:
		setAd(80);
		setHujia(50);
		setVal(40);
		setExp(30);
	}
}


Soider::~Soider()
{
}
//createWithSoiderTypes
Soider * Soider::createWithSoiderTypes(SoiderTypes soiderType)
{	
	Soider*soider = new Soider(soiderType);
	const char*soiderFramName;
	switch (soiderType) {
	case SoiderType1:
		soiderFramName = "soilder_1_run.png";
		soider->setMaxblood(400);
		soider->setBlood(400);
		soider->setExp(30);
		soider->setVal(100);
		soider->setAttack_distance(100);
		soider->setAd(50);
		break;
	   
	case SoiderType2:
		soiderFramName = "soilder2_1_run.png";
		soider->setMaxblood(350);
		soider->setBlood(350);
		soider->setExp(20);
		soider->setVal(90);
		soider->setAttack_distance(300);
		soider->setAd(80);
		break;
	case SoiderType3:
		soiderFramName = "soilder3_1_run.png";
		soider->setMaxblood(800);
		soider->setBlood(800);
		soider->setExp(50);
		soider->setVal(200);
		soider->setAttack_distance(500);
		soider->setAd(150);
		break;
	}
	//soider->initWithSpriteFrameName(soiderFramName);
	  soider->initWithFile(soiderFramName);
		soider->autorelease();
		soider->unscheduleUpdate();
		soider->scheduleUpdate();

		/*m_pBloodView = new bloodView();
		m_pBloodView->setPosition(Vec2(130, 550));
		m_pBloodView->setScale(2.2f);
		m_pBloodView->setBackgroundTexture("xue_back.png");
		m_pBloodView->setForegroundTexture("xue_fore.png");
		m_pBloodView->setTotalBlood(100.0f);
		m_pBloodView->setCurrentBlood(100.0f);*/

		//创建精灵背景与血条进度条
		Sprite *hpBgSprite = Sprite::create("xue_back.png");
		hpBgSprite->setPosition(Point(soider->getContentSize().width / 2 , soider->getContentSize().height ));
		soider->addChild(hpBgSprite);
		ProgressTimer *Hps = ProgressTimer::create(Sprite::create("xue_fore.png"));
		soider->setHps(Hps);
		Hps->setType(ProgressTimer::Type::BAR);
		Hps->setMidpoint(Point(0, 0.5f));
		Hps->setBarChangeRate(Point(1, 0));
		Hps->setPercentage(50);
		soider->getHps()->setPercentage(100);
		Hps->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2));
		hpBgSprite->addChild(Hps);

		return soider;
	//CC_SAFE_DELETE(soider);
	//return nullptr;
}

Soider * Soider::create(const char *filename)
{
	Soider *sprite = new Soider();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease(); 
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Soider::update(float dt) {
	switch (soiderType) {
	case SoiderType1:
		//this->setRotation(this->getRotation() - 0.5);
		break;
	case SoiderType2:
		//this->setRotation(this->getRotation() + 1);
		break;
	}
	Vec2 moveLen = velocity * dt;

	this->setPosition(this->getPosition() + moveLen);
	
}
