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
	case SoiderType2:
		setAd(60);
		setHujia(50);
		setVal(15);
	case SoiderType3:
		setAd(80);
		setHujia(50);
		setVal(40);
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
		soider->maxblood=200;
		break;
	case SoiderType2:
		soiderFramName = "soilder2_1_run.png";
		soider->maxblood = 150;
		break;
	case SoiderType3:
		soiderFramName = "soilder2_1_run.png";
		soider->maxblood = 400;
		break;
	}
	//soider->initWithSpriteFrameName(soiderFramName);
	soider->initWithFile(soiderFramName);
		soider->autorelease();
		soider->unscheduleUpdate();
		soider->scheduleUpdate();

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
