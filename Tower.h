#pragma once

#include"cocos2d.h"
#include"Soider.h"
USING_NS_CC;

typedef enum {
	TowerType1,//防御塔
	TowerType2//水晶
}TowerTypes;

class Tower :
	public Sprite
{
	CC_SYNTHESIZE(TowerTypes, towerType, TowerType);//这个宏用来自动生成set/get方法，如 CC_SYNTHESIZE(int, hp, Hp)；soider *p = new soider;p->setHp(1);
	CC_SYNTHESIZE(int, maxblood, Maxblood);
	CC_SYNTHESIZE(int, ad, Ad);
	CC_SYNTHESIZE(int, blood, Blood);
	CC_SYNTHESIZE(int, hujia, Hujia);
	CC_SYNTHESIZE(int, val, Val);
	CC_SYNTHESIZE(int, exp, Exp);
	CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity);
	CC_SYNTHESIZE(ProgressTimer*, hpw, Hpw);//创建一个PT类然后可以调用gethps->setpercentage来改变血条
public:
	
	Tower();
	~Tower();
	Tower(TowerTypes towerTYpe);
	static Tower * createWithTowerTypes(TowerTypes towerType);
	void update(float dt);

	void be_attacked1(Tower* a, Soider* b);
	inline float get_blood() { return blood; }
	inline float get_maxblood() { return maxblood; }
	inline float get_ad1() { return ad; }

};

