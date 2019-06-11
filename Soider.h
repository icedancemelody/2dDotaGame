#pragma once
#include "C:\Users\yj151\~\MyCompany\MyGame1\cocos2d\cocos\2d\CCSprite.h"
#include"cocos2d.h"
USING_NS_CC;

typedef enum {
	SoiderType1,//近战
	SoiderType2,//远程
	SoiderType3,//炮兵
}SoiderTypes;


class Soider :
	public Sprite
{
	CC_SYNTHESIZE(SoiderTypes, soiderType, SoiderType);//这个宏用来自动生成set/get方法，如 CC_SYNTHESIZE(int, hp, Hp)；plane *p = new plane;p->setHp(1);
	CC_SYNTHESIZE(int, maxblood, Maxblood);
	CC_SYNTHESIZE(int, ad, Ad);
	CC_SYNTHESIZE(int, blood, Blood);
	CC_SYNTHESIZE(int, hujia, Hujia);
	CC_SYNTHESIZE(int, val, Val);//val即value，指小兵价值
	CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity);
public:
	Soider();
	Soider(SoiderTypes soiderType);
	~Soider();
	static Soider*Soider::createWithSoiderTypes(SoiderTypes soiderType);
	static Soider * create(const char * filename);
	void update(float dt);
};


