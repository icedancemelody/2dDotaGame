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
	float  _ap, _mokang, _gongsu, _yisu;
	int _side, _attackdis;
public:
	int _exp; float _ad; int _gp; int _hujia;int _max_blood, _max_mp; float _speed; float _blood;
	char *hero_name[50];
	int attackrange;
	people();
	people(int a, float b, float c, float d, int e, float f, float g,float h, int i, int j,int k,int l,int m) {
		_max_blood = a; _max_mp=b; _ad = c; _ap = d; _hujia = e; _mokang = f;
		_gongsu = g; _speed = h; _side = i; _attackdis = j; _exp = k; _gp = l;
		attackrange = m;
	}
	~people();
	inline float get_maxblood() { return _max_blood; }
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
	int _mp;//����

	int _money = 0;
	int _value = 300;
	int _killnum = 0;//��ɱ����
	int _deadnum = 0;//��������
	int _lianshashu = 0;//��ɱ��
	int _liansishu = 0;//������
public:
	int _level=1;
	hero();
	hero(int a, float b, float c, float d, int e, float f, float g, float h, int i, int j,int k,int l,int m);
	void gain_eqp(equipment eqp);
	void sell_eqp(equipment eqp);
;
	void bonus();
	void disbonus();

	void be_attacked_by(hero other);
	int be_attacked_by_soider(hero a, Soider* b);
	int be_attacked_by_tower(hero a, Tower* b);
	int be_attacked_by_me(hero a, hero b);
	void hero::exp_up(hero me,Soider *other);
	inline float get_mp() { return _mp; }
	inline float get_attackdis(){ return _attackdis; }
	inline float get_exp() { return _exp; }
	inline float get_gp() { return _gp; }
	inline float get_level() { return _level; }
	//װ��
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
