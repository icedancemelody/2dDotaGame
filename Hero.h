#pragma once
#include "C:\Users\yj151\~\MyCompany\MyGame1\cocos2d\cocos\2d\CCSprite.h"
#include"cocos2d.h"
USING_NS_CC;

#define CC_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

/*#define CREATE_FUNC(__TYPE__) \
static__TYPE__* create() \
{ \
	__TYPE__ *pRet = new __TYPE__(); \
	if (pRet && pRet->init()) \
	{ \
		pRet->autorelease(); \
		return pRet; \
	} \
	else \
	{ \
		delete pRet; \
		pRet = NULL; \
		return NULL; \
	} \
}*/


typedef enum {
	HeroType1,
	HeroType2,
	HeroType3
}HeroTypes;

class Hero :
	public CCNode
{
private:
	CC_SYNTHESIZE(HeroTypes, heroType, HeroType);//这个宏用来自动生成set/get方法，如 CC_SYNTHESIZE(int, hp, Hp)；plane *p = new plane;p->setHp(1);
	CC_SYNTHESIZE(int, maxblood, Maxblood);
	CC_SYNTHESIZE(int, ad, Ad);
	CC_SYNTHESIZE(int, ap, Ap);
	CC_SYNTHESIZE(int, blood, Blood);
	CC_SYNTHESIZE(int, hujia, Hujia);
	CC_SYNTHESIZE(int, mokang, Mokang);
	CC_SYNTHESIZE(int, val, Val);
	CC_SYNTHESIZE(int, money, Money);
	CC_SYNTHESIZE(int, exp, Exp);
	CC_SYNTHESIZE(int, level, Level);
	CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity);
	CCSprite* m_HeroSprite;//精灵
	char *Hero_name;//用来保存初始状态的精灵图片名称
public:
	Hero();
	Hero(HeroTypes heroType);
	~Hero();
	void InitHeroSprite(char *hero_name);
	// 设置动画, num为图片数目，run_directon为精灵脸朝向，false朝右, name_each为name_png中每一小张图片的公共名称部分
	void SetAnimation(const char *name_each, const unsigned int num, bool run_directon);
	//停止动画
	void StopAnimation();
	//攻击动画
	void AttackAnimation(const char *name_each, const unsigned int num, bool run_directon);
	//攻击动画结束
	void AttackEnd();
	//判断英雄是否运动到了窗口的中间位置,visibleSize为当前窗口的大小  
	bool JudgePositona(CCSize visibleSize);
	//判断是否在跑动画
	bool IsRunning;
	//判断是否在攻击动画
	bool IsAttack;
	//英雄运动的方向
	bool HeroDirecton;

	CREATE_FUNC(Hero);

	static Hero*createWithHeroTypes(HeroTypes heroType);
	static Hero* create(const char * filename);
	void update(float dt);

};