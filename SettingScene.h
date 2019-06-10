#ifndef __SETTING_SCENE_H__
#define __SETTING_SCENE_H__

#include "cocos2d.h"

class SettingScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void menuMusicToggleCallback(cocos2d::Ref* pSender);
	void menuItem1Callback(cocos2d::Ref* pSender);
	CREATE_FUNC(SettingScene);
};

#endif

