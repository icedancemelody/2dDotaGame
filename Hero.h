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
	CC_SYNTHESIZE(HeroTypes, heroType, HeroType);//����������Զ�����set/get�������� CC_SYNTHESIZE(int, hp, Hp)��plane *p = new plane;p->setHp(1);
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
	CCSprite* m_HeroSprite;//����
	char *Hero_name;//���������ʼ״̬�ľ���ͼƬ����
public:
	Hero();
	Hero(HeroTypes heroType);
	~Hero();
	void InitHeroSprite(char *hero_name);
	// ���ö���, numΪͼƬ��Ŀ��run_directonΪ����������false����, name_eachΪname_png��ÿһС��ͼƬ�Ĺ������Ʋ���
	void SetAnimation(const char *name_each, const unsigned int num, bool run_directon);
	//ֹͣ����
	void StopAnimation();
	//��������
	void AttackAnimation(const char *name_each, const unsigned int num, bool run_directon);
	//������������
	void AttackEnd();
	//�ж�Ӣ���Ƿ��˶����˴��ڵ��м�λ��,visibleSizeΪ��ǰ���ڵĴ�С  
	bool JudgePositona(CCSize visibleSize);
	//�ж��Ƿ����ܶ���
	bool IsRunning;
	//�ж��Ƿ��ڹ�������
	bool IsAttack;
	//Ӣ���˶��ķ���
	bool HeroDirecton;

	CREATE_FUNC(Hero);

	static Hero*createWithHeroTypes(HeroTypes heroType);
	static Hero* create(const char * filename);
	void update(float dt);

};