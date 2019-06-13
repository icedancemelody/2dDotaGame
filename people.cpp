#include "people.h"


people::people()
{
}


people::~people()
{
}

hero::hero(float a, float b, float c, float d, float e, float f, float g, float h, int i, int j,int k,int l)
	:people::people(a, b, c, d, e, f, g, h, i, j, k, l) {
	_blood = _max_blood;
	_mp = _max_mp;
}





 void hero::gain_eqp(equipment eqp){
	 _money -= eqp._price;
	 _ad += eqp._ad;
	 _ap += eqp._ap;
	 _hujia += eqp._hujia;
	 _mokang += eqp._mokang;
	 _gongsu += _gongsu * eqp._gongsu;
	 _yisu += eqp._yisu;
 }


 void hero::sell_eqp(equipment eqp){
	 _money += eqp._soldprice;
	 _ad -= eqp._ad;
	 _ap -= eqp._ap;
	 _hujia -= eqp._hujia;
	 _mokang -= eqp._mokang;
	 _gongsu -= _gongsu * eqp._gongsu;
	 _yisu -= eqp._yisu;
 }

 void hero::level_up(hero me) {

	 me._level=me._level+1;
	 me._ad = me._ad + 10;
 };

 void hero::judge_level_up(float x,hero me)
 {
	 if (me._exp>=280&&me._exp<=340) {
		 level_up(me);
	 }
	 if (_exp >= 280 && _exp < 340 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
	 }
	 if (_exp >= 340 && _exp < 460 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
	 }
	 if (_exp >= 460 && _exp < 640 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
	 }
	 if (_exp >= 640 && _exp < 880 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
	 }
	 if (_exp >= 880 && _exp < 1180 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
	 }
	 if (_exp >= 1180 && _exp < 1270 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
	 }
	 if (_exp >= 1270 && _exp < 1350 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
	 }
	 if (_exp >= 1350 && _exp < 1425 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
	 }
	 if (_exp >= 1425 && _exp < 1495 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
	 }
	 if (_exp >= 1495 && _exp < 1565 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
	 }
	 if (_exp >= 0 && _exp < 280 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
	 }
	 if (_exp >= 0 && _exp < 280 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
	 }
	 if (_exp >= 0 && _exp < 280 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
	 }
	 if (_exp >= 0 && _exp < 280 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
	 }
	 if (_exp >= 0 && _exp < 280 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
	 }
	 if (_exp >= 0 && _exp < 280 && _exp + x >= 280 && _exp + x < 340) {
		 level_up(me);
		
	 }
	 
 }

 /*void hero::judge_level_up(int x) {
	 //x为此次获得经验
	 if (_exp >= 0 && _exp < 280 && _exp + x >= 280 && _exp + x < 340) {
		 level_up
	 }
	 if (_exp >= 280 && _exp < 340 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }
	 if (_exp >= 340 && _exp < 460 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }
	 if (_exp >= 460 && _exp < 640 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }
	 if (_exp >=640 && _exp < 880 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }
	 if (_exp >= 880 && _exp < 1180 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }
	 if (_exp >= 1180 && _exp < 1270 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }
	 if (_exp >= 1270 && _exp < 1350 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }
	 if (_exp >= 1350 && _exp < 1425 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }
	 if (_exp >= 1425 && _exp < 1495 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }
	 if (_exp >= 1495 && _exp < 1565 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }
	 if (_exp >= 0 && _exp < 280 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }
	 if (_exp >= 0 && _exp < 280 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }
	 if (_exp >= 0 && _exp < 280 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }
	 if (_exp >= 0 && _exp < 280 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }
	 if (_exp >= 0 && _exp < 280 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }
	 if (_exp >= 0 && _exp < 280 && _exp + x >= 280 && _exp + x < 340) {
		 level_up;
	 }


	 return;
 }*/

 

 void hero::bonus() {
	 switch (_lianshashu) {
	 case 1:_value = 300;
	 case 2:_value += 75;
	 case 3:_value += 75;
	 case 4:_value += 75;
	 case 5:_value += 100;
	 case 6:_value += 100;
	 case 7:_value += 150;
	 case 8:_value += 150;
	 }
	 return;
 }

 void hero::disbonus() {
	 switch (_liansishu) {
	 case 1:_value -= 20;
	 case 2:_value -= 20;
	 case 3:_value -= 30;
	 case 4:_value -= 30;
	 case 5:_value -= 40;
	 case 6:_value -= 40;
	 case 7:_value -= 50;
	 case 8:_value -= 50;
	 }
	 return;
 }


 void hero::kill_hero(hero me, hero other) {
	 _money += other._value;
	 me._liansishu = 0;
	 me._lianshashu++;
	 me._killnum++;
	 me.bonus();
	 me._exp += 100;
	 me.judge_level_up(100,me);
	 other._liansishu++;
	 other._deadnum++;
	 other.disbonus();
 }

 void hero::kill_tower(hero me) {
	 me._money += 200;
 }

 void hero::kill_soiderA(soiderA x,hero me) {
	 _money += x._value;
	 _exp += 20;
	 judge_level_up(x._value,me);
 }
 void hero::kill_soiderB(soiderB x,hero me) {
	 _money += x._value;
	 _exp += 18;
	 judge_level_up(x._value,me);
 }

 void hero::kill_soiderC(soiderC x, hero me) {
	 _money += x._value;
	 _exp += 50;
	 judge_level_up(x._value,me);
 }

 void hero::kill_soiderD(soiderD x, hero me) {
	 _money += x._value;
	 _exp += 70;
	 judge_level_up(x._value,me);
 }



 soiderA::soiderA() :people::people(_max_blood,_max_mp, _ad, _ap, _hujia, _mokang, _gongsu, _yisu, _side, _attackdis,_exp,_gp) {
	 _value = 23;
	 _attackdis = 150;
	 _max_blood = 500;
 }
 
 soiderB::soiderB()
 {
	 _value = 19;
	 _attackdis = 500;
	 _max_blood = 400;
 }

 soiderC::soiderC()
 {
	 _value = 53;
	 _attackdis = 500;
	 _max_blood = 1000;
 }

 soiderD::soiderD()
 {
	 _value = 90;
	 _attackdis = 150;
	 _max_blood = 2000;
 }
