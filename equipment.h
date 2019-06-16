#pragma once
#include<string>
using namespace std;
class equipment{
private:
	string _name;
	float _blood, _ad, _ap, _hujia, _mokang, _gongsu, _yisu;
	int _price,_soldprice;
public:
	friend class hero;
	equipment();
	equipment(float a, float b, float c, float d, float e, float f, float g, int h);
	~equipment();
};

