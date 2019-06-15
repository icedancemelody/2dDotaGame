#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void menuItem1Callback(cocos2d::Ref* pSender);
	void menuEnterWarrior(cocos2d::Ref* pSender);
	void menuEnterShooter(cocos2d::Ref* pSender); 
	void menuEnterMega(cocos2d::Ref* pSender);
	CREATE_FUNC(StartScene);
};

#endif

