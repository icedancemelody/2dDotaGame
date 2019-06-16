#ifndef __WelcomeScene_H__

#define __WelcomeScene_H__



#include "cocos2d.h"



class WelcomeScene : public cocos2d::Scene

{

public:

	static cocos2d::Scene* createScene();



	virtual bool init();



	// a selector callback

	void menuCloseCallback(cocos2d::Ref* pSender);

	void menuEnter(cocos2d::Ref* pSender);

	void menuSetting(cocos2d::Ref* pSender);

	// implement the "static create()" method manually

	CREATE_FUNC(WelcomeScene);

};



#endif // __HELLOWORLD_SCENE_H__#pragma once
