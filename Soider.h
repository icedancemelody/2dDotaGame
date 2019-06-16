#define CC_SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

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
	CC_SYNTHESIZE(int, exp, Exp);
	CC_SYNTHESIZE(int,attack_distance, Attack_distance);
	CC_SYNTHESIZE(int, val, Val);//val即value，指小兵价值
	CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity);
	CC_SYNTHESIZE(ProgressTimer*, hps, Hps);//创建一个PT类然后可以调用gethps->setpercentage来改变血条
public:
	Soider();
	Soider(SoiderTypes soiderType);
	~Soider();
	static Soider*Soider::createWithSoiderTypes(SoiderTypes soiderType);
	static Soider * create(const char * filename);
	void update(float dt);
	void be_attacked(Soider* a, Soider* b);
	
	
	inline float get_blood() { return blood; }
	inline float get_maxblood() { return maxblood; }
	inline float get_ad() { return ad; }
};


