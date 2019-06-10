#ifndef __bloodView_H__
#define __bloodView_H__

#include "cocos2d.h"

class bloodView : public cocos2d::Node
{
public:
	bloodView();

public:
	//设置血条背景
	void setBackgroundTexture(const char *pName);
	//设置血条前景
	void setForegroundTexture(const char *pName);
	//设置总血量
	void setTotalBlood(float total);
	//设置当前血量
	void setCurrentBlood(float progress);
	//得到当前血量
	float getCurrentBlood() const;
	//得到总血量
	float getTotalBlood() const;

private:
	//设置前景血条显示的长度
	void setForegroundTextureRect(const cocos2d::Rect &rect);

private:
	cocos2d::Sprite *m_bloodBackground;//背景血条
	cocos2d::Sprite *m_bloodForeground;//前景血条
	float m_totalBlood;//总血量
	float m_currentBlood;//当前血量
	float m_scale;//放大倍数
};
#endif