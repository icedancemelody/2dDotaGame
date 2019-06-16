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
		setExp(100);
	}
	case TowerType2: {
		setAd(0);
		setHujia(100);
		setVal(200);
		setMaxblood(500);
		setBlood(200);
		setExp(10);
	}
	case TowerType3: {
		setAd(150);
		setHujia(100);
		setVal(200);
		setMaxblood(500);
		setBlood(500);
		setExp(100);
	}
	case TowerType4: {
		setAd(0);
		setHujia(100);
		setVal(200);
		setMaxblood(500);
		setBlood(200);
		setExp(10);
	}
	}
}

/*void createAndSetHpBar()
{
	auto hpBgSprite = Sprite::createWithSpriteFrameName("xue_back.png");
	hpBgSprite->setPosition(Point(tower->getContentSize().width / 2, tower->getContentSize().height));
	tower->addChild(hpBgSprite);
	auto hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("xue_fore.png"));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point(0, 0.5f));
	hpBar->setBarChangeRate(Point(1, 0));
	hpBar->setPercentage(hpPercentage);
	hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2));
	hpBgSprite->addChild(hpBar);
}*/

Tower * Tower::createWithTowerTypes(TowerTypes towerType)
{
	Tower*tower = new Tower(towerType);
	const char*towerFramName;
	switch (towerType) 
	{
	case TowerType1:
		towerFramName = "tower3.png";  //此处可根据需求替换图片文件名
		tower->setMaxblood(3000);
		tower->setBlood(3000);
		tower->setAd(150);
		tower->setHujia(100);
		tower->setExp(100);
		tower->setVal(300);
		tower->setAttack_distance(600);
		break;
	case TowerType2:
		towerFramName = "camp2.png";
		tower->setMaxblood(9000);
		tower->setBlood(9000);
		tower->setAd(0);
		tower->setHujia(90);
		tower->setExp(10);
		tower->setVal(50);
		tower->setAttack_distance(600);
		break;
	case TowerType3:
		towerFramName = "tower2.png";  //此处可根据需求替换图片文件名
		tower->setMaxblood(3000);
		tower->setBlood(3000);
		tower->setAd(150);
		tower->setHujia(100);
		tower->setExp(100);
		tower->setVal(300);
		tower->setAttack_distance(600);
		break;
	case TowerType4:
		towerFramName = "camp1.png";
		tower->setMaxblood(9000);
		tower->setBlood(9000);
		tower->setAd(0);
		tower->setHujia(90);
		tower->setExp(10);
		tower->setVal(50);
		tower->setAttack_distance(600);
		break;
	}
	//soider->initWithSpriteFrameName(soiderFramName);
	
	/*tower_blood = new bloodView();
	tower_blood->setPosition(Vec2(130, 550));
	tower_blood->setScale(2.2f);
	tower_blood->setBackgroundTexture("xue_back.png");
	tower_blood->setForegroundTexture("xue_fore.png");
	tower_blood->setTotalBlood(100.0f);
	tower_blood->setCurrentBlood(100.0f);*/

	//创建精灵背景与血条进度条
	Sprite *hpBgSprite = Sprite::create("xue_back.png");
	hpBgSprite->setPosition(Point(tower->getContentSize().width / 2+70, tower->getContentSize().height+150));
	tower->addChild(hpBgSprite);
	ProgressTimer *Hpw = ProgressTimer::create(Sprite::create("xue_fore.png"));
	tower->setHpw(Hpw);
	Hpw->setType(ProgressTimer::Type::BAR);
	Hpw->setMidpoint(Point(0, 0.5f));
	Hpw->setBarChangeRate(Point(1, 0));
	tower->getHpw()->setPercentage(100);
	Hpw->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2));
	hpBgSprite->addChild(Hpw);
	tower->initWithFile(towerFramName);
	tower->autorelease();
	tower->unscheduleUpdate();
	tower->scheduleUpdate();
	return tower;


	//CC_SAFE_DELETE(soider);
	//return nullptr;
}

void Tower::update(float dt) 
{
	switch (towerType) 
	{
	case TowerType1:

		break;
	case TowerType2:
		break;
	case TowerType3:
		break;
	case TowerType4:
		break;
	}

}


