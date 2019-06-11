#pragma once
#include "C:\Users\yj151\~\MyCompany\MyGame1\cocos2d\cocos\2d\CCSprite.h"
#include"cocos2d.h"
USING_NS_CC;

typedef enum {
	TowerType1,//防御塔
	TowerType2//水晶
}TowerTypes;

class Tower :
	public Sprite
{
	CC_SYNTHESIZE(TowerTypes, towerType, TowerType);//这个宏用来自动生成set/get方法，如 CC_SYNTHESIZE(int, hp, Hp)；plane *p = new plane;p->setHp(1);
	CC_SYNTHESIZE(int, maxblood, Maxblood);
	CC_SYNTHESIZE(int, ad, Ad);
	CC_SYNTHESIZE(int, blood, Blood);
	CC_SYNTHESIZE(int, hujia, Hujia);
	CC_SYNTHESIZE(int, val, Val);
	CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity);
public:
	Tower();
	~Tower();
	Tower(TowerTypes towerTYpe);
	Tower * createWithTowerTypes(TowerTypes towerType);
	void update(float dt);
};

