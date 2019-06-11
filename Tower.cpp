#include "Tower.h"



Tower::Tower()
{
}


Tower::~Tower()
{
}

Tower::Tower(TowerTypes towerTYpe) {
	this->towerType = towerType;
	this->velocity = Vec2::ZERO;
	switch (towerType) {
	case TowerType1: {
		setAd(150);
		setHujia(100);
		setVal(200);
		setMaxblood(500);
		setBlood(500);
	}
	case TowerType2: {
		setAd(0);
		setHujia(100);
		setVal(200);
		setMaxblood(500);
		setBlood(500);
	}
	}
}

Tower * Tower::createWithTowerTypes(TowerTypes towerType)
{
	Tower*tower = new Tower(towerType);
	const char*towerFramName;
	switch (towerType) {
	case TowerType1:
		towerFramName = "tower1.png";//此处可根据需求替换图片文件名
		break;
	case TowerType2:
		towerFramName = "camp1.png";
		break;
	}
	//soider->initWithSpriteFrameName(soiderFramName);
	tower->initWithFile(towerFramName);
	tower->autorelease();
	tower->unscheduleUpdate();
	tower->scheduleUpdate();
	return tower;
	//CC_SAFE_DELETE(soider);
	//return nullptr;
}

void Tower::update(float dt) {
	switch (towerType) {
	case TowerType1:
		//this->setRotation(this->getRotation() - 0.5);
		break;
	case TowerType2:
		//this->setRotation(this->getRotation() + 1);
		break;
	}
	//Vec2 moveLen = velocity * dt;

	//this->setPosition(this->getPosition() + moveLen);

}


