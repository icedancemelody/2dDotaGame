#ifndef __GameMap_H__
#define __GameMap_H__

#include "cocos2d.h"
#include"bloodView.h"
#include"StartScene.h"
#include"Gamepause.h"
#include<string.h>
#include<stdlib.h>
class GameMap : public cocos2d::Layer
{
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::Layer* _shopLayer;
	cocos2d::Layer* _Timelabel;
	cocos2d::Layer* _HPLayer;
	cocos2d::Layer* _ScoreboardLayer;
	public:
	static cocos2d::Scene* createScene(std::string HeroName);
	virtual bool init();
	
	int time=0;
	std::string _heroname;
	
	void initWithName(std::string HeroName);

	bloodView *m_pBloodView;//血条类
	void createShopCallBack(cocos2d::Ref* pSender);
	void closeShopCallBack(cocos2d::Ref* pSender);
	void createScoreCallBack(cocos2d::Ref* pSender);
	void closeScoreCallBack(cocos2d::Ref* pSender);
	void updatetime(float dt);
	//装备购买16种函数
	void buyItemCallBack(cocos2d::Ref* pSender);
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
	// implement the "static create()" method manually

	void createSettingCallBack(cocos2d::Ref* pSender);
	CREATE_FUNC(GameMap);
};

#endif