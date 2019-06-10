#ifndef __GameMap_H__
#define __GameMap_H__

#include "cocos2d.h"
#include"bloodView.h"
class GameMap : public cocos2d::Layer
{
	cocos2d::TMXTiledMap* _tileMap;
	cocos2d::Layer* _shopLayer;
	public:
	static cocos2d::Scene* createScene();

	int time=0;
	virtual bool init();
	bloodView *m_pBloodView;//ÑªÌõÀà
	/*void initBG();
	void onExit();
	void onEnter();
	void menuPauseCallBack(cocos2d::Ref* pSender);*/
	void createShopCallBack(cocos2d::Ref* pSender);
	void closeShopCallBack(cocos2d::Ref* pSender);
	void buyItemCallBack(cocos2d::Ref* pSender);
	void updatetime(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(GameMap);
};

#endif