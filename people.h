#pragma once
using namespace std;
#include"equipment.h"
#include"Tower.h"
#include"cocos2d.h"
USING_NS_CC;
class equipment;
class soiderA;
class soiderB;
class soiderC;
class soiderD;
class people
{
protected:
	float _blood, _ap, _mokang, _gongsu, _yisu;
	int _side, _attackdis;
public:
	int _exp; float _ad; int _gp; int _hujia;	float _max_blood,_max_mp; float _speed;
	char *hero_name[50];
	people();
	people(float a, float b, float c, float d, float e, float f, float g,float h, int i, int j,int k,int l) {
		_max_blood = a; _max_mp=b; _ad = c; _ap = d; _hujia = e; _mokang = f;
		_gongsu = g; _speed = h; _side = i; _attackdis = j; _exp = k; _gp = l;
	}
	~people();
	inline float get_blood() {return _blood;}
	inline float get_ad() {return _ad;}
	inline float get_ap() {return _ap;}
	inline float get_hujia() {return _hujia;}
	inline float get_mokang() { return _mokang; }
	inline float get_gongsu() { return _gongsu; }
	inline float get_yisu() { return _yisu; }
	inline float get_exp() { return _exp; }
	inline float get_gp() { return _gp; }
	inline int get_side() { return _side; }
	inline void set_side(int x) { _side = x; }
};

class hero :public people {
protected:
	int _mp;//蓝量

	int _money = 0;
	int _value = 300;
	int _killnum = 0;//击杀总数
	int _deadnum = 0;//死亡总数
	int _lianshashu = 0;//连杀数
	int _liansishu = 0;//连死数
public:
	int _level=1;
	hero();
	hero(float a, float b, float c, float d, float e, float f, float g, float h, int i, int j,int k,int l);
	void gain_eqp(equipment eqp);
	void sell_eqp(equipment eqp);
	void judge_level_up(float x,hero me);
	void level_up(hero me) ;
	void bonus();
	void disbonus();
	void kill_hero(hero me, hero other);
	void kill_tower(hero me);
	
	void hero::kill_soiderA(soiderA x, hero me);

	void hero::kill_soiderB(soiderB x, hero me);

	void hero::kill_soiderC(soiderC x, hero me);

	void hero::kill_soiderD(soiderD x, hero me);
	void be_attacked_by(hero other);
	void hero::exp_up(hero me,Soider *other);
	inline float get_mp() { return _mp; }
	inline float get_attackdis(){ return _attackdis; }
	inline float get_exp() { return _exp; }
	inline float get_gp() { return _gp; }
	inline float get_level() { return _level; }
	//装备
	int eqp_num=0;
	bool me_have[4][4] = { 0 };
	int me_this_eqp[4][4] = { 0 };
};

class soiderA :public people {
protected:
	int _value = 23;
public:
	friend class hero;
	soiderA();

};

class soiderB :public people {
protected:
	int _value = 19;
public:
	friend class hero;
	soiderB();

};

class soiderC :public people {
protected:
	int _value = 56;
public:
	friend class hero;
	soiderC();

};

class soiderD :public people {
protected:
	int _value = 93;
public:
	friend class hero;
	soiderD();

};
