#pragma once

#ifndef __Gamepause__H__

#define __Gamepause__H__

#include "cocos2d.h"

#include"WelcomeScene.h"

USING_NS_CC;

class Gamepause : public cocos2d::Layer

{

public:

	virtual bool init();

	static cocos2d::Scene* scene(RenderTexture* sqr);

	CREATE_FUNC(Gamepause);

	//¼ÌÐøÓÎÏ·

	void menuContinueCallback(cocos2d::Ref* pSender);

	void menuLoginCallback(cocos2d::Ref* pSender);

private:



};



#endif // __Gamepause_H__