/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include"bloodView.h"  
#include "cocos2d.h"
#include"Hero.h"
#include"StartScene.h"
#include"Gamepause.h"
#include"people.h"

typedef enum
{
	kBoxA_Tag = 102, kBoxB_Tag, kBoxC_Tag
} SpriteTags;




class HelloWorld : public cocos2d::Layer

{
	cocos2d::TMXTiledMap* _tileMap;
public:
	Hero*hero1;
	Hero*hero2;
	CREATE_FUNC(HelloWorld);
	static cocos2d::Scene* createScene(std::string HeroName);

	cocos2d::Sprite *plane;
	cocos2d::Sprite *sprite2;
	cocos2d::Layer* Timerlabel;
	cocos2d::Layer* _ScoreboardLayer;
	cocos2d::Layer* _setLayer;
	cocos2d::Layer* maplayer;
	cocos2d::Layer* _shopLayer;

	int offsetX = 0;
	int time = 0;
	int offsetY = 100;
	
	virtual bool init();
	void initWithName(std::string HeroName);
	
	std::string heroname;
	std::string otherheroname;
	std::string string1;
	std::string string2;
	std::string string3;
	std::string skill1, skill2, skill3;
	//行走帧的图片数
	int run_num = 0;
	//攻击帧的图片数
	int att_num = 0;
	//敌方英雄攻击帧的图片数
	int att_num1 = 0;
	//行走帧的图片名
	const char* run_name;
	//攻击帧的图片名
	const char* att_name;
	//敌方英雄攻击帧的图片名
	const char* att_name1;
	
	
	//技能冷却图片
	const char* skill_name[3];
	cocos2d::ProgressTimer* mProgressTimer[3];
	void BeginSkill(int i,int cd);
	void EndSkill1();
	void EndSkill2();
	void EndSkill3();

	bloodView *m_pBloodView;
	bloodView *m_pBloodView1;

	virtual void updatetime(float dt);
	virtual void updateenemy(float dt);
	virtual void updatefriend(float dt);
	virtual void updatefriendtower(float dt);
	virtual void updateenemytower(float dt);
	virtual void update(float dt);
	virtual void updateattacked(float dt);
	virtual void updateattackedenemy(float dt);
	virtual void updateattacked1(float dt);
	virtual void updateattacked1enemy(float dt);
	virtual void updateenemyheromove(float dt);
	virtual void updateenemyheroattack(float dt);
	virtual void updateenemyheroattackhero(float dt);
	virtual void updatequanshui(float dt);
	
	/*virtual void myupdate(float dt);*/

	// a selector callback

	void menuCloseCallback(cocos2d::Ref* pSender);

	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	bool touchBegan(cocos2d::Touch *touch, cocos2d::Event* event);

	void touchEnded(cocos2d::Touch *touch, cocos2d::Event *event);


	void createScoreCallBack(cocos2d::Ref* pSender);
	void closeScoreCallBack(cocos2d::Ref* pSender);
	void createShopCallBack(cocos2d::Ref* pSender);
	void closeShopCallBack(cocos2d::Ref* pSender);
	bool shop_is_open = false;
	bool score_is_open = false;
	void buySwordCallBack1(cocos2d::Ref* pSender);
	void buySwordCallBack2(cocos2d::Ref* pSender);
	void buySwordCallBack3(cocos2d::Ref* pSender);
	void buySwordCallBack4(cocos2d::Ref* pSender);
	void buyClothCallBack1(cocos2d::Ref* pSender);
	void buyClothCallBack2(cocos2d::Ref* pSender);
	void buyClothCallBack3(cocos2d::Ref* pSender);
	void buyClothCallBack4(cocos2d::Ref* pSender);
	void buyLiveCallBack1(cocos2d::Ref* pSender);
	void buyLiveCallBack2(cocos2d::Ref* pSender);
	void buyLiveCallBack3(cocos2d::Ref* pSender);
	void buyLiveCallBack4(cocos2d::Ref* pSender);
	void buyShoeCallBack1(cocos2d::Ref* pSender);
	void buyShoeCallBack2(cocos2d::Ref* pSender);
	void buyShoeCallBack3(cocos2d::Ref* pSender);
	void buyShoeCallBack4(cocos2d::Ref* pSender);

	void menuLoginCallback(cocos2d::Ref* pSender);
	void be_attacked2(hero a, Soider* b);
	bool I_win=false;
	bool I_lose=false;

	//设置菜单
	void createSettingCallBack(cocos2d::Ref* pSender);
	//技能
	int hero1_cd1 = 1;
	int hero1_cd2 = 1;
	int hero1_cd3 = 1;
	int hero2_cd1 = 1;
	int hero2_cd2 = 1;
	int hero2_cd3 = 1;
	int hero3_cd1 = 1;
	int hero3_cd2 = 1;
	int hero3_cd3 = 1;

	void skill_1_cd(float dt);
	void skill_2_cd(float dt);
	void skill_2_over(float dt);
	void skill_3_cd(float dt);
	void skill_4_cd(float dt);
	void skill_5_cd(float dt);
	void skill_5_over(float dt);
	void skill_6_cd(float dt);
	void skill_7_cd(float dt);
	void skill_7_over(float dt);
	void skill_8_cd(float dt);
	void skill_8_over(float dt);
	void skill_9_cd(float dt);
	//攻速
	int gongsu = 1;
	void gongsu1(float dt);
private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

	//添加了这个事件

	// implement the "static create()" method manually

};

#endif // __HELLOWORLD_SCENE_H__

